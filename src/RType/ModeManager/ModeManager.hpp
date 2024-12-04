/*
** EPITECH PROJECT, 2024
** RType
** File description:
** ModeManager.hpp
*/

#ifndef RTYPE_MODEMANAGER_HPP_
#define RTYPE_MODEMANAGER_HPP_

#include <mutex>

namespace rtype {
    /**
     * @class ModeManager
     *
     * @brief Manages the program mode (server, client, client with server).
     * It allows to get the current state of the server (enabled or disabled) and to enable or disable it.
     *
     * @warning This class doesn't have client state management, because it's not supposed to change.
     * To add only-client code, use preprocessor directives, so the server binary doesn't have useless client code.
     * Example of code conditionally compiled using preprocessor directives (you can also refer to `ModeManager.cpp`):
     * ```cpp
     * #ifdef RTYPE_IS_CLIENT
     * // Some code only included in client binary here...
     * #endif
     * ```
     */
    class ModeManager {
    public:
        /**
         * @brief Enables the server part (intended to be used only by client).
         */
        static void enableServer();

        /**
         * @brief Disables the server part (intended to be used only by client).
         */
        static void disableServer();

        /**
         * @brief Switches the server part state (intended to be used only by client).
         * If it was enabled, it's disabled.
         * Otherwise, if it was disabled, it's enabled.
         */
        static void switchServer();

        /**
         * @return Whether the current program is a server (or a client with a server) or not.
         */
        static bool isServer();

    private:
        /**
         * @brief Current state of the server (enabled or disabled).
         * Always `true` on server, unless `disableServer` is called (not supposed to happen).
         * By default `false` on client, can be switch to `true` if `enableServer` is called.
         */
        static bool _isServer;

        /**
         * @brief Mutex to keep same state on all threads, so the usage of this class is thread-safe.
         */
        static std::mutex _modeMutex;
    };
}

/**
 * @brief Macro to get the current state of the server.
 *
 * @see rtype::ModeManager::isServer
 */
#define IS_SERVER rtype::ModeManager::isServer()

/**
 * @brief Macro to enable the server.
 *
 * @see rtype::ModeManager::enableServer
 */
#define ENABLE_SERVER() rtype::ModeManager::enableServer()

/**
 * @brief Macro to disable the server.
 *
 * @see rtype::ModeManager:disableServer
 */
#define DISABLE_SERVER() rtype::ModeManager::disableServer()

/**
 * @brief Macro to switch the state of the server.
 *
 * @see rtype::ModeManager::switchServer
 */
#define SWITCH_SERVER() rtype::ModeManager::switchServer()

#endif /* !RTYPE_MODEMANAGER_HPP_ */
