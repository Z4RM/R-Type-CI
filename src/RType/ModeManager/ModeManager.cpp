/*
** EPITECH PROJECT, 2024
** RType
** File description:
** ModeManager.cpp
*/

#include "spdlog/spdlog.h"
#include "ModeManager.hpp"

void rtype::ModeManager::enableServer() {
    std::lock_guard<std::mutex> lock(_modeMutex);
    _isServer = true;
    spdlog::debug("Server mode enabled");
}

void rtype::ModeManager::disableServer() {
    std::lock_guard<std::mutex> lock(_modeMutex);
    _isServer = false;
    spdlog::debug("Server mode disabled");
}

void rtype::ModeManager::switchServer() {
    if (_isServer)
        disableServer();
    else
        enableServer();
}

bool rtype::ModeManager::isServer() {
    return _isServer;
}

#ifdef RTYPE_IS_SERVER
bool rtype::ModeManager::_isServer = true;
#else
bool rtype::ModeManager::_isServer = false;
#endif

std::mutex rtype::ModeManager::_modeMutex;