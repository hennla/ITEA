//
// Created by Hennadii on 05.09.2021.
//

#ifndef SBT_SERVER_PLAYER_H
#define SBT_SERVER_PLAYER_H

#include <memory>

enum PlayerState {
    WAITING_GAME,
    GAMING
};

class Player {
public:
    virtual ~Player() = default;
    virtual void send_message(const std::string & message) = 0;
    virtual unsigned int get_player_id() = 0;
    virtual const std::string &get_player_name() = 0;
    void set_state(PlayerState state);
    PlayerState get_state();
private:
    PlayerState state_;
};

typedef std::shared_ptr<Player> player_ptr;

#endif //SBT_SERVER_PLAYER_H
