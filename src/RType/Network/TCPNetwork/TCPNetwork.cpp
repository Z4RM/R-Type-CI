/*
** EPITECH PROJECT, 2024
** RType
** File description:
** TODO: add description
*/

#include "TCPNetwork.hpp"

#include <spdlog/spdlog.h>

#include "RType/ModeManager/ModeManager.hpp"

namespace rtype::network {

    //TODO: numThread should be configurable in .ini

    TCPNetwork::TCPNetwork(unsigned short port) : _port(port) {
        this->_ioContext.restart();

        this->_acceptor = asio::ip::tcp::acceptor(this->_ioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port));

    }


    void TCPNetwork::start() {
        int numThreads = 2;

        if (IS_SERVER) {
            this->startAccept();
            this->_threadPool.emplace(numThreads);
        }

        for (int i = 0; i < numThreads; i++) {
            this->_threadPool->addTask([this] {
                try {
                    this->_ioContext.run();
                } catch (std::exception &e) {
                    spdlog::error("Exception in a TCP IO Thread: {}", e.what());
                }
            });
        }
    }

    void TCPNetwork::startAccept() {
        auto socket = std::make_shared<asio::ip::tcp::socket>(this->_ioContext);

        this->_acceptor->async_accept((*socket), [this, socket](const asio::error_code &error) {
            if (!error) {
                spdlog::info("New client connected: {}", socket->remote_endpoint());
            } else {
                spdlog::error("Accept error: {}", error.message());
            }
        });
    }
}
