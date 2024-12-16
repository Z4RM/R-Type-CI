/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Client.cpp
*/

#include <iostream>
#include "spdlog/spdlog.h"
#include "RType/RType.hpp"
#include "Client.hpp"

rtype::Client::Client(RType *rType)
        : _running(true),
          _actions({
                           {Action::Connect,     std::bind(&Client::_connect, this)},
                           {Action::Disconnect,  std::bind(&Client::_disconnect, this)},
                           {Action::StartServer, std::bind(&RType::startServer, rType)},
                           {Action::StopServer,  std::bind(&RType::stopServer, rType)},
                           {Action::Ping,        std::bind(&Client::_ping, this)},
                           {Action::Quit,        std::bind(&Client::_quit, this)}
                   }) {
    spdlog::info("Client started");
}

bool rtype::Client::running() const {
    return _running;
}

// TODO: replace this with GUI interactions
void rtype::Client::iteration() {
    std::string input;

    std::cout << "> ";

    if (!std::getline(std::cin, input)) {
        std::cout << std::endl;
        _quit();
        return;
    }

    if (input.empty())
        return;

    if (input == "connect")
        _actions.at(Action::Connect)();
    else if (input == "disconnect")
        _actions.at(Action::Disconnect)();
    else if (input == "start")
        _actions.at(Action::StartServer)();
    else if (input == "stop")
        _actions.at(Action::StopServer)();
    else if (input == "quit")
        _actions.at(Action::Quit)();
    else
        _actions.at(Action::Ping)();
}

void rtype::Client::_connect() {
    // TODO
}

void rtype::Client::_disconnect() {
    // TODO
}

void rtype::Client::_ping() {
    // TODO
}

void rtype::Client::_quit() {
    _running = false;
    spdlog::info("Client stopped");
}
