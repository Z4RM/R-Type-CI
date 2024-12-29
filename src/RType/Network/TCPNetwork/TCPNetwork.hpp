/*
** EPITECH PROJECT, 2024
** RType
** File description:
** TCP Network connection
*/

#pragma once

#include <optional>
#include <RType/ThreadPool/ThreadPool.hpp>
#include "asio.hpp"

namespace rtype::network {

    class TCPNetwork {
        public:
            explicit TCPNetwork(unsigned short port = 0);
            ~TCPNetwork();

            void start();

            //SERVER
            void startAccept();
            void handleClient(std::shared_ptr<asio::ip::tcp::socket> socket);

            //CLIENT //TODO: make some of theses private
            void connect(const asio::ip::tcp::endpoint& endpoint);
            void sendMessage(std::string &message);
            void sendNextMessage();
            void handleSend(const asio::error_code& ec);

        private:
            unsigned short _port; ///< port of the self connection (0 for any)
            std::optional<asio::ip::tcp::acceptor> _acceptor;
            std::optional<ThreadPool> _threadPool;
            std::optional<asio::ip::tcp::socket> _socket;
            asio::io_context _ioContext;

           std::queue<std::string> _toSendQueue;
           std::mutex _toSendMutex;

          bool _isSending = false;
    };

}