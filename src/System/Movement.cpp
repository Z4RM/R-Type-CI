/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Movement.cpp
*/

#include "Movement.hpp"
#include "Structures.hpp"

void rtype::system::Movement::move(const rtype::ecs::EntityManager& entityManager, rtype::ecs::ComponentManager& componentManager)
{
    for (auto& entity : entityManager.getEntities()) {
        const auto pos = componentManager.getComponent<Position>(entity);
        const auto vel = componentManager.getComponent<Velocity>(entity);
        if (pos && vel)
        {
            pos->x += vel->x;
            pos->y += vel->y;
            pos->z += vel->z;
        }
    }
}
