/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Client.hpp
*/

#ifndef RTYPE_CLIENT_HPP_
#define RTYPE_CLIENT_HPP_

#include <string>
#include <array>
#include <vector>
#include <functional>

namespace rtype {
    class RType;
}

namespace rtype {
    /**
     * @class Client
     */
    class Client {
        /**
         * @enum List of possibles client action.
         */
        enum class Action {
            Connect,
            Disconnect,
            StartServer,
            StopServer,
            Ping,
            Quit
        };

        /**
         * @typedef An (unordered) map of client actions.
         */
        using Actions = std::unordered_map<Action, std::function<void()>>;

    public:
        // TODO: documentation
        Client(RType *rType);

        // TODO: documentation
        bool running() const;

        // TODO: replace this with GUI interactions
        void iteration();

    private:
        // TODO: documentation
        void _connect();

        // TODO: documentation
        void _disconnect();

        // TODO: documentation
        void _ping();

        // TODO: documentation
        void _quit();

        // TODO: documentation
        Actions _actions;

        // TODO: documentation
        bool _running;
    };
}

#endif /* !RTYPE_CLIENT_HPP_ */
