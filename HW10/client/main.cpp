#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

#define MAX_LEN 200


std::atomic<bool> exit_flag = false;
std::thread t_send, t_recv;


// Erase text from terminal
void eraseText(int cnt) {
    char back_space = 8;
    for (int i = 0; i < cnt; i++) {
        std::cout << back_space;
    }
}

// Send message to everyone
void send_message(SOCKET client_socket) {
    while (true) {
        if (exit_flag)
            break;
        std::cout << "You : ";
        char str[MAX_LEN];
        std::cin.getline(str, MAX_LEN);
        send(client_socket, str, sizeof(str), 0);
        if (strcmp(str, "#exit") == 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            exit_flag = true;
            t_recv.detach();
            closesocket(client_socket);
            break;
        }
    }
}

// Receive message
void recv_message(SOCKET client_socket) {
    char name[MAX_LEN], str[MAX_LEN];
    while (true) {
        if (exit_flag)
            break;

        int bytes_received = recv(client_socket, name, sizeof(name), 0);

        if (bytes_received <= 0)
            continue;

        recv(client_socket, str, sizeof(str), 0);

        eraseText(6);
        if (strcmp(str, "#exit") == 0) {
            std::cout << "Server stopped! press enter to exit!" << std::endl;
            exit_flag = true;
            t_send.detach();
            closesocket(client_socket);
            continue;
        } else if (strcmp(name, "#NULL") != 0)
            std::cout << name << " : " << str << std::endl;
        else
            std::cout << str << std::endl;
        std::cout << "You : ";
        fflush(stdout);
    }
}

int main() {
    SOCKET client_socket;
    WSAData data;
    WORD version = MAKEWORD(2, 2);
    if (WSAStartup(version, &data) != 0) {
        std::cerr << "create socket error" << std::endl;
        return -1;
    }

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "create socket error" << std::endl;
        return -1;
    }

    struct sockaddr_in client{};
    client.sin_family = AF_INET;
    client.sin_port = htons(1234); // Port no. of server
    //client.sin_addr.s_addr = INADDR_ANY;

    client.sin_addr.s_addr = inet_addr("127.0.0.1");

    //https://silviocesare.wordpress.com/2007/10/22/setting-sin_zero-to-0-in-struct-sockaddr_in/
    ZeroMemory(&client.sin_zero, sizeof(client.sin_zero));

    if ((connect(client_socket, (struct sockaddr *) &client, sizeof(struct sockaddr_in))) == SOCKET_ERROR) {
        std::cerr << "create socket error" << std::endl;
        return -1;
    }

    std::cout << "  ====== Welcome to the chat-room ======   " << std::endl;

    char name[MAX_LEN];
    std::cout << "Enter your name : ";
    std::cin.getline(name, MAX_LEN);
    std::string message("MY_NAME::");
    message.append(name);
    send(client_socket, message.c_str(), message.size(), 0);

    std::thread t1(send_message, client_socket);
    std::thread t2(recv_message, client_socket);

    t_send = std::move(t1);
    t_recv = std::move(t2);

    if (t_send.joinable())
        t_send.join();
    if (t_recv.joinable())
        t_recv.join();

    return 0;
}