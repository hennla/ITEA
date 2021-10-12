//
// Created by Hennadii on 05.09.2021.
//

#include <iostream>
#include "PlayerManager.h"

unsigned int PlayerManager::join(const player_ptr& player) {
    max_player_id_++;
    players_mutex.lock();
    players_.emplace(std::make_pair(max_player_id_, player));
    players_mutex.unlock();
    return max_player_id_;
}

void PlayerManager::leave(unsigned int player_id) {
    players_mutex.lock();
    auto find_player = players_.find(player_id);
    if (find_player != players_.end()) {
        players_.erase(player_id);
    }
    players_mutex.unlock();
}

player_ptr PlayerManager::get_player(unsigned int player_id) {
    players_mutex.lock();
    auto find_player = players_.find(player_id);
    players_mutex.unlock();
    if (find_player == players_.end()) {
        return nullptr;
    }
    return find_player->second;
}

unsigned int PlayerManager::search_enemy(unsigned int player_id) {
    unsigned int found_player = 0;
    players_mutex.lock();
    for (const auto &pair_: players_) {
        if (pair_.second->get_state() == WAITING_GAME) {
            if (pair_.first == player_id) {
                continue;
            }
            found_player = pair_.first;
            pair_.second->set_state(GAMING);
            break;
        }
    }
    players_mutex.unlock();
    return found_player;
}
