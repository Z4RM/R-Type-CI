/*
** EPITECH PROJECT, 2024
** RType
** File description:
** UDPServer.hpp
*/

#ifndef RTYPE_UDPSERVER_HPP_
#define RTYPE_UDPSERVER_HPP_

#include <list>
#include <optional>
#include <queue>
#include "asio.hpp"

// TODO: documentation
#define BUFFER_SIZE 1024

namespace rtype::server::network {


    struct ClientInfo {
        asio::ip::udp::endpoint endpoint;
    };

    // TODO: documentation
    class UDPServer {

    public:
        // TODO: documentation
        class StartException : public std::exception {
        public:
            // TODO: documentation
            StartException();
        };

        static UDPServer &getInstance(ushort port = 4242);

        static void initialize(ushort port) { getInstance(port); };

        // TODO: documentation
        explicit UDPServer(unsigned short port);

        // TODO: documentation
        /**
         * @throw StartException If the server is already started.
         */
        void start();

        // TODO: documentation
        void stop();

    private:
        // TODO: refactor
        void _receive();

        void _newPacket(std::size_t bytesReceived);

        // TODO: refactor
        void _send();

        void _removeClient(asio::ip::udp::endpoint);

        // TODO: documentation
        unsigned short _port;

        void _connect(std::string &ip, ushort port);

        // TODO: documentation
        std::atomic<bool> _running = false;

        // TODO: documentation
        asio::io_context _ioContext;

        // TODO: documentation
        std::optional<asio::ip::udp::socket> _socket;

        // TODO: documentation
        std::optional<asio::ip::udp::endpoint> _endpoint;

        // TODO: documentation
        std::thread _thread;

        // TODO: documentation
        std::array<char, BUFFER_SIZE> _buffer;

        std::queue<std::pair<std::shared_ptr<ClientInfo>, std::string>> _packetsToSend{};

        std::queue<std::pair<std::shared_ptr<ClientInfo>, std::string>> _packetsToHandle{};

        std::list<ClientInfo> _clients;

        bool _isConnected = false;

    };
}

#endif /* !RTYPE_UDPSERVER_HPP_ */
