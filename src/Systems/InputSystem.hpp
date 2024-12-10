/*
** EPITECH PROJECT, 2024
** RType
** File description:
** InputSystem.hpp
*/

#ifndef INPUTSYSTEM_HPP
#define INPUTSYSTEM_HPP

#include "ECS.hpp"
#include "RType/Components/InputHandler.hpp"
#include <SFML/Window/Event.hpp>

namespace rtype::systems {
    class InputSystem {
    public:
        static void handleInput(ecs::EntityManager &entityManager, ecs::ComponentManager &componentManager, const sf::Event &event);
    };
}

#endif //INPUTSYSTEM_HPP
