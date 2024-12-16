/*
** EPITECH PROJECT, 2024
** RType
** File description:
** InputSystem.cpp
*/

#include "InputSystem.hpp"

void rtype::systems::InputSystem::handleInput(ecs::EntityManager &entityManager, ecs::ComponentManager &componentManager, const sf::Event &event) {
    if (event.type != sf::Event::KeyPressed)
        return;

    const auto entities = entityManager.getEntities();
    for (const auto &entity : entities) {
        auto inputHandler = componentManager.getComponent<rtype::components::InputHandler>(entity);
        if (!inputHandler)
            continue;

        auto action = inputHandler->keyActions.find(event.key.code);
        if (action != inputHandler->keyActions.end())
            action->second();
    }
}
