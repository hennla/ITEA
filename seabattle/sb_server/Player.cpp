//
// Created by Hennadii on 05.09.2021.
//

#include "Player.h"

void Player::set_state(PlayerState state) {
    state_ = state;
}

PlayerState Player::get_state() {
    return state_;
}
