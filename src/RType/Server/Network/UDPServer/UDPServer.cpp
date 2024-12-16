/*
** EPITECH PROJECT, 2024
** RType
** File description:
** UDPServer.cpp
*/

#include "spdlog/spdlog.h"
#include "UDPServer.hpp"

namespace rtype::server::network {
    UDPServer::StartException::StartException() {}

    UDPServer::UDPServer(ushort port) : _port(port) {

    }

    void UDPServer::start() {
        if (_running)
            throw StartException();

        try {
            _ioContext.restart();
            _socket = asio::ip::udp::socket(_ioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), _port));
            _running = true;
            _receive();

            _thread = std::thread([this] {
                try {
                    _ioContext.run();
                } catch (const std::exception& e) {
                    spdlog::error("Exception in IO thread: {}", e.what());
                }
            });

            spdlog::info("Server started and running on port {}", _port);

            #ifdef RTYPE_IS_CLIENT
                std::string serverIp = "127.0.0.1";
                this->_connect(serverIp, 4343);
            #endif

        } catch (const std::exception& e) {
            spdlog::error("Failed to start UDP server: {}", e.what());
            throw StartException();
        }
    }

    void UDPServer::stop() {
        _running = false;

        _socket->close();
        _socket.reset();
        _endpoint.reset();
        _ioContext.stop();

        if (_thread.joinable())
            _thread.join();

        spdlog::info("Server stopped");
    }

    void UDPServer::_receive() {
        _socket->async_receive_from(
            asio::buffer(_buffer),
            *_endpoint,
            [this](std::error_code errorCode, std::size_t bytesReceived) {
                if (!_running)
                    return;

                if (!errorCode && bytesReceived > 0) {

                    asio::ip::udp::endpoint senderEndpoint = *_endpoint;
                    std::string received(_buffer.data(), bytesReceived);

                    if (_clients.find(senderEndpoint) == _clients.end()) {
                        _clients[senderEndpoint] = ClientInfo();
                    }
                    _packetsToHandle.emplace(received);
                    _send();
                }

                if (errorCode) {
                    spdlog::error("Cannot receive data via UDP server: {}", errorCode.message());
                }

                if (bytesReceived <= 0) {
                    spdlog::warn("UDP server received an invalid number of bytes ({})", bytesReceived);
                }

                _receive();
            }
        );
    }

    void UDPServer::_send() {
        if (_packetsToHandle.empty())
            return;
        std::string received = _packetsToHandle.front();
        spdlog::info(" Message received: {}", received);
        std::string message = "Error: Bad request";

        if (received == "CONNECT") {
            message = "OK";

            for (auto it = _clients.begin(); it != _clients.end(); ) {
                asio::error_code ec;
                _socket->async_send_to(
                    asio::buffer(message),
                    it->first,
                    [&](std::error_code, std::size_t) {}
                );

                if (ec) {
                    spdlog::warn("Client is no longer available and will be removed.");
                    it = _clients.erase(it);
                } else {
                    ++it;
                }
            }
        }
        _packetsToHandle.pop();
    }

    UDPServer &UDPServer::getInstance(ushort port) {
        static UDPServer server(port);

        return server;
    }

    //TODO: add timeout for connection
    void UDPServer::_connect(std::string &ip, ushort port) {
        try {
            if (!_socket.has_value() || !_socket->is_open()) {
                throw std::runtime_error("Server socket is not initialized or is closed.");
            }

            asio::ip::udp::endpoint serverEndpoint(asio::ip::address::from_string(ip), port);

            std::string message = "CONNECT";
            asio::error_code ec;

            _socket->send_to(asio::buffer(message), serverEndpoint, 0, ec);

            if (ec) {
                spdlog::error("Error on send: {}", ec.message());
                return;
            }

            char reply[1024];
            size_t reply_length = _socket->receive_from(asio::buffer(reply), serverEndpoint, 0, ec);

            if (ec) {
                spdlog::error("Error on receive: {}", ec.message());
                return;
            }

            std::string replyMessage(reply, reply_length);
            spdlog::info("Received reply from server: {}", replyMessage);

            if (replyMessage == "OK") {
                spdlog::info("Connected to the server successfully.");
            } else {
                spdlog::warn("Failed to connect to the server.");
            }

        } catch (const std::exception& e) {
            spdlog::error("Exception occurred: {}", e.what());
        }
    }
}
