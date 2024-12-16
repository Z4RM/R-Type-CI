/*
** EPITECH PROJECT, 2024
** RType
** File description:
** RType.cpp
*/

#include "ModeManager/ModeManager.hpp"
#include "Config/Config.hpp"
#include "ECS.hpp"
#include "Components/Player.hpp"
#include "Systems.hpp"
#include "RType.hpp"
#include "./Server/Network/UDPServer/UDPServer.hpp"

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
rtype::RType::RType(ushort port) : _port(port), _server(_port) {
};
#else
rtype::RType::RType(ushort port) : _port(port), _server(_port), _client(this) {

}
#endif

int rtype::RType::_run() {
    ecs::EntityManager entityManager;
    ecs::ComponentManager componentManager;
    ecs::SystemManager systemManager(entityManager, componentManager);

    size_t rtype = entityManager.createEntity();
#ifdef RTYPE_IS_CLIENT
    systemManager.addSystem(rtype::systems::RenderWindowSys::createWindow);
    String title;
    title.s = "RType";
    rtype::components::RWindow renderWindow{};
    rtype::components::Mode mode;
    mode.style.style = sf::Style::Default;
    Sprite sprite1 = {{0, 0, 0}, {800, 600}, "sprites/background.jpg", {-1}};
    rtype::components::Window window(
            entityManager,
            componentManager,
            {800, 600},
            {"RType"},
            renderWindow,
            mode,
            sprite1
    );
    systemManager.addSystem(rtype::systems::RenderWindowSys::render);
#endif

#ifdef RTYPE_IS_CLIENT
    Sprite sprite2 = {{100, 100, 0}, {33, 17}, "sprites/players.gif", {0}};
    rtype::components::Player player(
            entityManager,
            componentManager,
            {0, 0, 0},
            {0, 0, 0},
            {64, 64},
            sprite2,
            {"", 0, 0}
    );
#else
    rtype::components::Player player(
        entityManager,
        componentManager,
        {0, 0, 0},
        {0, 0, 0},
        {64, 64}
        );
#endif


#ifdef RTYPE_IS_SERVER
    try {
        rtype::server::network::UDPServer::initialize(_port);
        rtype::server::network::UDPServer::getInstance().start();
    } catch (std::exception &e) {
       //TODO: stop everything
    }
#else
    try {
        server::network::UDPServer::initialize(_port);
        std::string ip = "127.0.0.1";
        rtype::server::network::UDPServer::getInstance().start();
    } catch (std::exception &e) {
        //TODO: stop everything
    }
#endif



    while (_running()) {
        systemManager.updateSystems();
#ifdef RTYPE_IS_CLIENT
        _client.iteration();
#else

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
