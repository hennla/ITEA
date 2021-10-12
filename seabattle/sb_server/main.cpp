#include <iostream>
#include <cstdlib>
#include "GameServer.h"

int main(int argc, char *argv[]) {
    try {
        if (argc < 2) {
            std::cerr << "Usage: sb_server <port>" << std::endl;
            return 1;
        }
        boost::asio::io_context io_context;
        tcp::endpoint endpoint{tcp::v4(), static_cast<unsigned short>(std::atoi(argv[1]))};

        GameServer game_server{io_context, endpoint};

        io_context.run();

    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
