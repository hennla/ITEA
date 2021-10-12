//
// Created by Hennadii on 05.09.2021.
//

#include "PlayerSession.h"

void PlayerSession::start() {
    if (started_) return;
    player_id_ = player_manager_.join(shared_from_this());
    started_ = true;
    do_read();
}

void PlayerSession::stop() {
    if (!started_) return;
    std::cout<<"Stop player: " << player_id_<<std::endl;
    player_manager_.leave(player_id_);
    started_ = false;
}

bool PlayerSession::is_started() const {
    return started_;
}

unsigned int PlayerSession::get_player_id() {
    return player_id_;
}

const std::string &PlayerSession::get_player_name()  {
    return player_name_;
}

void PlayerSession::set_player_name(const std::string &playerName) {
    player_name_ = playerName;
}

size_t PlayerSession::read_complete(const boost::system::error_code &err, size_t bytes) {
    if (err) {
        stop();
        return 0;
    }
    bool found = std::search(read_buffer_, read_buffer_ + bytes, END.begin(), END.end()) != read_buffer_ + bytes;
    return found ? 0 : 1;
}

void PlayerSession::do_read() {
    async_read(socket_, buffer(read_buffer_),
               MEM_FN2(read_complete, _1, _2), MEM_FN2(on_read, _1, _2));
}

void PlayerSession::do_write(const std::string & message) {
    if (!is_started()) return;
    std::copy(message.begin(), message.end(), write_buffer_);
    socket_.async_write_some(buffer(write_buffer_, message.size()),
                             MEM_FN2(on_write, _1, _2));
    std::cout << "Sending message: " << message << std::endl;
}

void PlayerSession::on_read(const PlayerSession::error_code &err, size_t bytes) {
    if (err) stop();
    if (!is_started()) return;
    do_read();
    std::string message{read_buffer_, bytes};

    std::cout << "Reading message: " << message << std::endl;
    parsed_message msg = split(message);
    if (msg[0] == LOGIN) on_login(msg);
    else if (msg[0] == GET_ENEMY) on_enemy(msg);
    else if (msg[1] != "0") on_to_player(msg, message);
    else {
        std::string response_message = ERROR_MESSAGE + SEPARATOR + "0" + SEPARATOR + std::to_string(player_id_) +
                SEPARATOR + "PROTOCOL_ERROR" + SEPARATOR + message + SEPARATOR + END;
        send_message(response_message);
    }
}

void PlayerSession::on_write(const PlayerSession::error_code &err, size_t bytes) {
    if (!is_started()) return;
    if (err) stop();
}

void PlayerSession::on_login(parsed_message &message) {
    set_player_name(message[3]);
    std::cout << "Setting player name : " << player_name_ << std::endl;
    std::string response_message = USERID + SEPARATOR + std::to_string(player_id_) + SEPARATOR + "0" + SEPARATOR +
          std::to_string(player_id_) + SEPARATOR + END;
    send_message(response_message);
}

void PlayerSession::on_enemy(parsed_message &message) {
    unsigned int enemy_player_id_ = player_manager_.search_enemy(player_id_);

    if (enemy_player_id_ > 0) {
        const auto enemy_player_ = player_manager_.get_player(enemy_player_id_);

        std::string response_message = ENEMY_USERID + SEPARATOR + std::to_string(enemy_player_id_) + SEPARATOR  + "0" + SEPARATOR +
                           std::to_string(player_id_) + SEPARATOR + player_name_ + SEPARATOR + "GO" + SEPARATOR +  END;
        enemy_player_->send_message(response_message);

        response_message = ENEMY_USERID + SEPARATOR + std::to_string(player_id_) + SEPARATOR  + "0" + SEPARATOR +
                           std::to_string(enemy_player_id_) + SEPARATOR + enemy_player_->get_player_name() + SEPARATOR + "WAIT" + SEPARATOR +  END;
        send_message(response_message);
        set_state(GAMING);
        enemy_player_->set_state(GAMING);
    }
}

void PlayerSession::on_to_player(parsed_message &message, std::string original_message) {
    auto resp_player = player_manager_.get_player(static_cast<unsigned int>(std::stoi(message[1])));
    std::string response_message;
    if (resp_player != nullptr) {
        response_message = std::move(original_message);
        resp_player->send_message(response_message);
    } else {
        response_message = ERROR_MESSAGE + SEPARATOR + "Send error to " + message[1] + SEPARATOR + END;
        send_message(response_message);
    }
}

void PlayerSession::send_message(const std::string & message)  {
    do_write(message);
}

PlayerSession::parsed_message PlayerSession::split(const std::string & message) {
    std::vector<std::string> split_vector;
    boost::split(split_vector, message, boost::is_any_of(SEPARATOR), boost::token_compress_on);
    return split_vector;
}


