/*
** EPITECH PROJECT, 2024
** RType
** File description:
** InputHandler.hpp
*/

#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <functional>
#include <unordered_map>
#include <SFML/Window/Keyboard.hpp>

namespace rtype::components {
    struct InputHandler {
        std::unordered_map<sf::Keyboard::Key, std::function<void()>> keyActions;
    };
}

#endif //INPUTHANDLER_HPP
