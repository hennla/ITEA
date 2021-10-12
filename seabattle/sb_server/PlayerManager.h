//
// Created by Hennadii on 05.09.2021.
//

#ifndef SBT_SERVER_PLAYERMANAGER_H
#define SBT_SERVER_PLAYERMANAGER_H

#include <map>
#include <vector>
#include <mutex>

#include "Player.h"

class PlayerManager {
public:
    PlayerManager() : max_player_id_(0){};

    unsigned int join(const player_ptr& player);

    void leave(unsigned int player_id);

    player_ptr get_player(unsigned int player_id);

    unsigned int search_enemy(unsigned int player_id);

private:
    unsigned int max_player_id_;
    std::map<unsigned int, player_ptr> players_;
    std::mutex players_mutex;
};


#endif //SBT_SERVER_PLAYERMANAGER_H
