//
// Created by Hennadii on 05.09.2021.
//

#ifndef SBT_SERVER_PLAYERSESSION_H
#define SBT_SERVER_PLAYERSESSION_H

#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/algorithm/string.hpp>
#include "PlayerManager.h"
#include "Player.h"

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::placeholders;


#define MEM_FN2(x, y, z)  boost::bind(&PlayerSession::x, shared_from_this(),y,z)

const std::string SEPARATOR = "::";
const std::string END = "END";
const std::string LOGIN = "LOGIN";
const std::string DISCONNECT = "DISCONNECT";
const std::string USERID = "USERID";
const std::string ENEMY_USERID = "ENEMY_USERID";
const std::string GET_ENEMY = "GET_ENEMY";
const std::string ERROR_MESSAGE = "ERROR_MESSAGE";

class PlayerSession : public Player, public std::enable_shared_from_this<PlayerSession> {
public:
    typedef boost::system::error_code error_code;
    typedef std::vector<std::string> parsed_message;

    PlayerSession(tcp::socket socket, PlayerManager &player_manager)
            : socket_(std::move(socket)),
              player_manager_(player_manager) {
        set_state(WAITING_GAME);
    }

    void start();

    void stop();

    bool is_started() const;

    unsigned int get_player_id() override;

    const std::string &get_player_name() override ;

    void set_player_name(const std::string &playerName);

    void send_message(const std::string & message) override;

private:

    parsed_message split(const std::string & message);

    void on_read(const error_code &err, size_t bytes);

    void on_write(const error_code &err, size_t bytes);

    void do_read();

    void do_write(const std::string & message);

    size_t read_complete(const boost::system::error_code &err, size_t bytes);

    void on_login(parsed_message &message);

    void on_enemy(parsed_message &message);

    void on_to_player(parsed_message &message, std::string original_message);

private:
    tcp::socket socket_;
    enum {
        max_msg = 1024
    };
    char read_buffer_[max_msg]{};
    char write_buffer_[max_msg]{};

    PlayerManager &player_manager_;

    bool started_ = false;
    unsigned int player_id_ = 0;
    std::string player_name_{};

};


#endif //SBT_SERVER_PLAYERSESSION_H
