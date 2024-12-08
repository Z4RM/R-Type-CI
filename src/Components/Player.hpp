/*
** EPITECH PROJECT, 2024
** R_Type
** File description:
** Player.hpp
*/

#pragma once
#include "Structure.hpp"
#include "../include/ECS.hpp"

class Player {
public:
    Player(
        rtype::ecs::EntityManager& entityManager,
        rtype::ecs::ComponentManager& componentManager,
        Position pos,
        Velocity vel,
        Size size,
        const Sprite& sprite,
        const Animation& animation);
    ~Player() = default;

    size_t _id;
};
