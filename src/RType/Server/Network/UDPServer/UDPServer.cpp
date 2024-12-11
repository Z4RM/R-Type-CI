/*
** EPITECH PROJECT, 2024
** RType
** File description:
** UDPServer.cpp
*/

#include "spdlog/spdlog.h"
#include "UDPServer.hpp"

rtype::server::network::UDPServer::StartException::StartException() {}

rtype::server::network::UDPServer::UDPServer(ushort port) : _port(port) {}

void rtype::server::network::UDPServer::start() {
    if (_running)
        throw StartException();

    _ioContext.restart();
    _socket = asio::ip::udp::socket(_ioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), _port));
    _endpoint = asio::ip::udp::endpoint();
    _thread = std::thread([this] { _ioContext.run(); });
    _running = true;

    _receive();

    spdlog::info("Server started and running on port {}", _port);
}

void rtype::server::network::UDPServer::stop() {
    _running = false;

    _socket->close();
    _socket.reset();
    _endpoint.reset();
    _ioContext.stop();

    if (_thread.joinable())
        _thread.join();

    spdlog::info("Server stopped");
}

void rtype::server::network::UDPServer::_receive() {
    _socket->async_receive_from(
            asio::buffer(_buffer),
            *_endpoint,
            [this](std::error_code errorCode, std::size_t bytesReceived) {
                if (!_running)
                    return;

                if (!errorCode && bytesReceived > 0)
                    _send();
                if (errorCode)
                    spdlog::error("Cannot receive data via UDP server: {}", errorCode.message());
                if (bytesReceived <= 0)
                    spdlog::warn("UDP server received an invalid number of bytes ({})", bytesReceived);
                _receive();
            }
    );
}

void rtype::server::network::UDPServer::_send() {
    auto message = "Server Response: " + std::string(_buffer.begin(), _buffer.end());

    _socket->async_send_to(
            asio::buffer(message),
            *_endpoint,
            [](std::error_code, std::size_t) {}
    );
}
