//
// Created by Hennadii on 05.09.2021.
//

#include "GameServer.h"

void GameServer::do_accept() {
    acceptor_.async_accept(
            [this](boost::system::error_code ec, tcp::socket socket) {
                if (!ec) {
                    std::make_shared<PlayerSession>(std::move(socket), player_manager_)->start();
                }

                do_accept();
            });
}