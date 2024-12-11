/*
** EPITECH PROJECT, 2024
** RType
** File description:
** RType.cpp
*/

#include "ModeManager/ModeManager.hpp"
#include "Config/Config.hpp"
#include "ECS.hpp"
#include "RType.hpp"

int rtype::RType::run() {
    if (!Config::initialize())
        return 84;

    RType rtype(Config::getInstance().getNetwork().server.port);

    return rtype._run();
}

#ifdef RTYPE_IS_CLIENT
void rtype::RType::startServer() {
    if (IS_SERVER) {
        spdlog::warn("Server seems to be already started, do nothing");
        return;
    }
    ENABLE_SERVER();
    // TODO
}

void rtype::RType::stopServer() {
    if (!IS_SERVER) {
        spdlog::warn("Server seems to be already stopped, do nothing");
        return;
    }
    DISABLE_SERVER();
    // TODO
}
#endif

#ifndef RTYPE_IS_CLIENT
rtype::RType::RType(ushort port) : _port(port), _server(_port) {}
#else
rtype::RType::RType(ushort port) : _port(port), _server(_port), _client(this) {}
#endif

int rtype::RType::_run() {
    ecs::EntityManager entityManager;
    ecs::ComponentManager componentManager;
    ecs::SystemManager systemManager(entityManager, componentManager);

    while (_running()) {
#ifdef RTYPE_IS_CLIENT
        _client.iteration();
#endif
    }
    return 0;
}

bool rtype::RType::_running() {
#ifdef RTYPE_IS_SERVER
    return true; // TODO
#endif
#ifdef RTYPE_IS_CLIENT
    return _client.running();
#endif
}
