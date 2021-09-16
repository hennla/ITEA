#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>

#define MAX_LEN 200

struct chat_client {
    unsigned int id;
    std::string name;
    SOCKET socket;
    std::thread th;
};

std::vector<chat_client> clients;
unsigned int clients_count = 0;
std::mutex console_mtx, clients_mtx;
std::atomic<bool> stop_flag = false;

bool set_name(int id, std::string name) {
    bool return_val = true;
    for (auto &client: clients) {
        if (client.id != id && client.name == name) {
            return_val = false;
            break;
        }
    }
    if (return_val) {
        for (auto &client: clients) {
            if (client.id == id) {
                client.name = name;
                break;
            }
        }
    }
    return return_val;
}


void shared_print(const std::string str, bool endLine = true) {
    std::lock_guard<std::mutex> guard(console_mtx);
    std::cout << str;
    if (endLine)
        std::cout << std::endl;
}

// Broadcast message to all clients except the sender
void broadcast_message(const std::string message, int sender_id) {
    char temp[MAX_LEN];
    strcpy(temp, message.c_str());
    for (auto &client: clients) {
        if (client.id != sender_id) {
            send(client.socket, temp, sizeof(temp), 0);
        }
    }
}

void end_connection(int id) {
    for (int i = 0; i < clients.size(); i++) {
        if (clients[i].id == id) {
            std::lock_guard<std::mutex> guard(clients_mtx);
            clients[i].th.detach();
            closesocket(clients[i].socket);
            clients.erase(clients.begin() + i);
            break;
        }
    }
}

void handle_client(SOCKET client_socket, int id) {
    char str[MAX_LEN];
    std::string name{};
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        int bytes_received = recv(client_socket, str, sizeof(str), 0);
        if (bytes_received <= 0)
            continue;
        std::string in_message{str};
        if (in_message == "#exit") {
            std::string message = name + " has left";
            broadcast_message("#NULL", id);
            broadcast_message(message, id);
            shared_print(message);
            end_connection(id);
            break;
        } else if (in_message.substr(0, 9) == "MY_NAME::") {
            name = in_message.substr(9);
            if (set_name(id, name)) {
                std::string welcome_message = name + " has joined";
                broadcast_message("#NULL", id);
                broadcast_message(welcome_message, id);
                shared_print(welcome_message);
                std::string error_message = "#SET_NAME_OK::";
                send(client_socket, error_message.c_str(), 15, 0);
            } else {
                std::string error_message = "#SET_NAME_ERROR::";
                send(client_socket, error_message.c_str(), 18, 0);
            }
            continue;
        }
        broadcast_message(name, id);
        broadcast_message(in_message, id);
        std::string message = name;
        message += ":" + in_message;
        shared_print(message);
    }
}

void handle_accept() {
    SOCKET server_socket;
    WSAData data{};
    WORD version = MAKEWORD(2, 2);
    if (WSAStartup(version, &data) != 0) {
        std::cerr << "create socket error" << std::endl;
        return;
    }
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "create socket error" << std::endl;
        return;
    }


    struct sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(1234); //port
    server.sin_addr.s_addr = INADDR_ANY;

    ZeroMemory(&server.sin_zero, sizeof(server.sin_zero));

    if (bind(server_socket, (struct sockaddr *) &server, sizeof(server)) == SOCKET_ERROR) {
        std::cerr << "create socket error" << std::endl;
        return;
    }

    if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "create socket error" << std::endl;
        return;
    }
    DWORD dw = true;
    ioctlsocket(server_socket, FIONBIO, &dw);

    struct sockaddr_in client{};
    SOCKET client_socket;
    int size = sizeof(sockaddr_in);


    std::cout << "   ====== Welcome to the chat-room ======   " << std::endl;

    while (!stop_flag) {
        if ((client_socket = accept(server_socket, (struct sockaddr *) &client, &size)) != INVALID_SOCKET) {
            clients_count++;
            std::thread t(handle_client, client_socket, clients_count);
            std::lock_guard<std::mutex> guard(clients_mtx);
            clients.push_back({clients_count, std::string("Anonymous"), client_socket, (std::move(t))});
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    broadcast_message("Server", 0);
    broadcast_message("#exit", 0);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    for (auto &_client: clients) {
        closesocket(_client.socket);
        _client.th.detach();
    }

    closesocket(server_socket);
}

int main() {
    std::thread accept_trh(handle_accept);

    std::cin.get();
    stop_flag = true;
    accept_trh.join();

    return 0;
}