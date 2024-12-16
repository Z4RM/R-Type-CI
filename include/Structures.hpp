/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Structure.hpp
*/

#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#pragma once
#include <string>
#ifdef RTYPE_IS_CLIENT
#include <SFML/Graphics.hpp>
#endif

struct Position
{
    float x;
    float y;
    float z;
};

struct Size
{
    float width;
    float height;
};

struct Velocity
{
    float x;
    float y;
    float z;
};

struct Hitbox
{
    Position pos;
    Size size;
};

struct Created
{
    bool isCreate = false;
};

struct ZIndex
{
    int value;
};

struct Animation
{
    std::string path;
    int nbFrames;
    int frameRate;
};

struct String
{
    std::string s;
};

#ifdef RTYPE_IS_CLIENT
struct Sprite
{
    Position pos;
    Size size;
    std::string path;
    ZIndex priority;
    sf::Texture* texture;
    sf::Sprite* sprite;
    Created created;
};
#endif

#endif //STRUCTURE_HPP
