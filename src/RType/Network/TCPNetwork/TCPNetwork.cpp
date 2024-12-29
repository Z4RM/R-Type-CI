/*
** EPITECH PROJECT, 2024
** RType
** File description:
** TODO: add description
*/

#include "spdlog/spdlog.h"
#include "TCPNetwork.hpp"
#include "RType/ModeManager/ModeManager.hpp"


namespace rtype::network {

    //TODO: numThread should be configurable in .ini

    TCPNetwork::TCPNetwork(unsigned short port) : _port(port) {
        this->_ioContext.restart();

        if (IS_SERVER) {
            this->_acceptor = asio::ip::tcp::acceptor(this->_ioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port));
        } else {
            asio::ip::tcp::resolver resolver(this->_ioContext);
            std::string portStr = fmt::to_string(port);
            auto endpoints = resolver.resolve("127.0.0.1", portStr);
            this->_serverSocket.emplace(this->_ioContext);

            try {
                auto connectedEndpoint = asio::connect(this->_serverSocket.value(), endpoints);
                spdlog::info("Successfully connected to the server tcp network: 127.0.0.1:{}", port);
            } catch (std::exception &e) {
                spdlog::error("Error while connecting to the server tcp network: 127.0.0.1:{}", port);
            }
        }
    }


    void TCPNetwork::start() {
        int numThreads = 2;
        this->_threadPool.emplace(numThreads);

        if (IS_SERVER) {
            this->startAccept();

            spdlog::info("Server tcp network started on port: {}", this->_port);
        } else {
            std::string message = "CONNECT";

            //TODO: make this async with a list of message
            asio::write(this->_serverSocket.value(), asio::buffer(message));
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

    TCPNetwork::~TCPNetwork() = default;


    void TCPNetwork::startAccept() {
        auto socket = std::make_shared<asio::ip::tcp::socket>(this->_ioContext);
        this->_acceptor->async_accept((*socket), [this, socket](const asio::error_code &error) {
            if (!error) {
                std::string address = socket->remote_endpoint().address().to_string();
                int port = socket->remote_endpoint().port();

                spdlog::info("New client connected: {}:{}", address, port);
                handleClient(socket);
            } else {
                spdlog::error("Accept error: {}", error.message());
            }
            this->startAccept();
        });
    }

    //TODO: try new method to have dynamic buffer size
    void TCPNetwork::handleClient(std::shared_ptr<asio::ip::tcp::socket> socket) {
        auto buffer = std::make_shared<std::vector<char>>(1024);

        socket->async_read_some(asio::buffer(*buffer),
    [this, socket, buffer](const asio::error_code& error, std::size_t bytes_transferred) {
            if (!error) {
                //TODO: make packet struct based on the packet type
                std::string message(buffer->data(), bytes_transferred);
                spdlog::info("New message received: {}", message);
                //handleMessage(socket, message);
                handleClient(socket);
            } else {
                spdlog::error("Receive error while reading client: {}", error.message());
            }
        });
    }

}
