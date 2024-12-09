/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Movement.hpp
*/

#pragma once
#include "ECS.hpp"

namespace rtype::system
{
    class Movement {
    public:
        Movement() = delete;
        ~Movement() = delete;

        static void move(const ecs::EntityManager& entityManager, ecs::ComponentManager& componentManager);
    };
}
