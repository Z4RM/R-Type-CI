/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game.cpp
*/

#include "Game.hpp"
#include <iostream>

rtype::Game::Game(int width, int height, const std::string &title) : _window(sf::VideoMode(width, height), title)
{
    _window.setFramerateLimit(60);
    if (!_backgroundTexture.loadFromFile("../../../sprites/background.jpg")) {
        std::cerr << "Error : Impossible to load 'background.jpg'." << std::endl;
        throw std::runtime_error("Texture not found");
    }
    _backgroundSprite.setTexture(_backgroundTexture);
}

rtype::Game::~Game() {}

