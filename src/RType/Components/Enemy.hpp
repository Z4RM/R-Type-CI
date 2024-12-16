/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Enemy.hpp
*/


#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Structures.hpp"
#include "ECS.hpp"

namespace rtype::components {
    class Enemy {
    public:
#ifdef RTYPE_IS_CLIENT
        Enemy(
              rtype::ecs::EntityManager &entityManager,
              rtype::ecs::ComponentManager &componentManager,
              Position pos,
              Velocity vel,
              Size size,
              Sprite &sprite,
              const Animation &animation
        );
#else
        Enemy(
              rtype::ecs::EntityManager &entityManager,
              rtype::ecs::ComponentManager &componentManager,
              Position pos,
              Velocity vel,
              Size size
        );
#endif

        ~Enemy() = default;

    private:
        size_t _id;
    };
}


#endif //ENEMY_HPP
