//
// Created by Hennadii on 05.09.2021.
//

#ifndef SBT_SERVER_GAMESERVER_H
#define SBT_SERVER_GAMESERVER_H

#include "PlayerManager.h"
#include "PlayerSession.h"

class GameServer {

public:
    GameServer(boost::asio::io_context &io_context,
               const tcp::endpoint &endpoint)
            : acceptor_(io_context, endpoint) {
        do_accept();
    }

private:
    void do_accept();

    tcp::acceptor acceptor_;
    PlayerManager player_manager_;
};


#endif //SBT_SERVER_GAMESERVER_H
