/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Enemy.cpp
*/


#include "Enemy.hpp"

#ifdef RTYPE_IS_CLIENT

rtype::components::Enemy::Enemy(
    rtype::ecs::EntityManager &entityManager,
    rtype::ecs::ComponentManager &componentManager,
    Position pos,
    Velocity vel,
    Size size,
    Sprite &sprite,
    const Animation &animation
) {
    _id = entityManager.createEntity();
    sprite.texture = new sf::Texture();
    sprite.sprite = new sf::Sprite();
    const int width = static_cast<int>(sprite.size.width);
    const int height = static_cast<int>(sprite.size.height);
    const sf::IntRect rect(0, 0, width, height);
    sprite.texture->loadFromFile(sprite.path, rect);
    sprite.sprite->setTexture(*sprite.texture);
    sprite.sprite->setPosition({pos.x, pos.y});
    sprite.sprite->setScale(2, 2);
    componentManager.addComponent<Sprite>(_id, sprite);
    componentManager.addComponent<Animation>(_id, animation);
    componentManager.addComponent<Position>(_id, pos);
    componentManager.addComponent<Velocity>(_id, vel);
    componentManager.addComponent<Size>(_id, size);
    componentManager.addComponent<Hitbox>(_id, {pos, size});


    std::unordered_map<float, Velocity> move;
    move.insert({
        0,
        {-0.5, 0, 0}
    });
    componentManager.addComponent<IA>(_id, {move});
}

#else

rtype::components::Enemy::Enemy(
    rtype::ecs::EntityManager &entityManager,
    rtype::ecs::ComponentManager &componentManager,
    Position pos,
    Velocity vel,
    Size size
) {
    _id = entityManager.createEntity();
    componentManager.addComponent<Position>(_id, pos);
    componentManager.addComponent<Velocity>(_id, vel);
    componentManager.addComponent<Size>(_id, size);
    componentManager.addComponent<Hitbox>(_id, {pos, size});
}

#endif
