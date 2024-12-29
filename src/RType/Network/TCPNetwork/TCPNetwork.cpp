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
            this->_socket.emplace(this->_ioContext);
            try {
                asio::ip::tcp::endpoint serverEndpoint(asio::ip::make_address("127.0.0.1"), port);
                this->connect(serverEndpoint);
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

            this->sendMessage(message);
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

    //TODO: clients should have a list of message to send foreah client and a way to send them message
    // (reuse code of client part)
    //TODO: try new method to have dynamic buffer size
    void TCPNetwork::handleClient(std::shared_ptr<asio::ip::tcp::socket> socket) {
        auto buffer = std::make_shared<std::vector<char>>(1024);

        socket->async_read_some(asio::buffer(*buffer),
    [this, socket, buffer](const asio::error_code& error, std::size_t bytes_transferred) {
            if (!error) {
                std::string message(buffer->data(), bytes_transferred);
                spdlog::info("New message received: {}", message);
                //handleMessage(socket, message);
                handleClient(socket);
            } else {
                spdlog::error("Receive error while reading client: {}", error.message());
            }
        });
    }

    void TCPNetwork::connect(const asio::ip::tcp::endpoint& endpoint) {
        this->_socket->async_connect(endpoint, [this](const asio::error_code& ec) {
            if (!ec) {
                spdlog::info("Connected to server");
                sendNextMessage();
            } else {
                spdlog::error("Connection failed: {}", ec.message());
            }
        });
    }

    void TCPNetwork::sendMessage(std::string &message) {
        {
            std::lock_guard lock(this->_toSendMutex);
            this->_toSendQueue.push(message);
        }
        sendNextMessage();
    }

    void TCPNetwork::sendNextMessage() {
        std::lock_guard lock(this->_toSendMutex);

        if (this->_toSendQueue.empty())
            return;

        _isSending = true;

        const std::string& message = this->_toSendQueue.front();

        async_write(_socket.value(), asio::buffer(message), [this](const asio::error_code& ec, std::size_t) {
            handleSend(ec);
        });
    }


    void TCPNetwork::handleSend(const asio::error_code &ec) {
        {
            std::lock_guard lock(this->_toSendMutex);

            if (!ec) {
                spdlog::info("Message sent successfully");
                this->_toSendQueue.pop();
            } else {
                spdlog::error("Failed to send message: {}", ec.message());
            }

            _isSending = false;
        }

        sendNextMessage();
    }
}
