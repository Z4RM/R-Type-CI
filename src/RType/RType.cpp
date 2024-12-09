/*
** EPITECH PROJECT, 2024
** RType
** File description:
** RType.cpp
*/

#include "RType/Config/Config.hpp"
#include "RType.hpp"
#include "ECS.hpp"
#include "Systems.hpp"
#include "Components/Player.hpp"

int rtype::RType::run() {
    Config::initialize();

    ecs::EntityManager entityManager;
    ecs::ComponentManager componentManager;
    ecs::SystemManager systemManager(entityManager, componentManager);
    return 0;
}
