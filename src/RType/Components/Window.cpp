/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Window.cpp
*/

#include "Window.hpp"

rtype::components::Window::Window(
    rtype::ecs::EntityManager& entityManager,
    rtype::ecs::ComponentManager& componentManager,
    const Size size,
    const String& title,
    RenderWindow renderWindow,
    Mode mode,
    const FrameLimit frameLimit,
    const Sprite& backgroundSprite
    )
{
    _id = entityManager.createEntity();
    const uint32_t style = mode.style.none * sf::Style::None
        + mode.style.titleBar * sf::Style::Titlebar
        + mode.style.resize * sf::Style::Resize
        + mode.style.close * sf::Style::Close
        + mode.style.fullScreen * sf::Style::Fullscreen
        + mode.style.defaults * sf::Style::Default;
    mode.style.style = style;
    componentManager.addComponent<Size>(_id, size);
    componentManager.addComponent<String>(_id, title);
    componentManager.addComponent<RenderWindow>(_id, renderWindow);
    componentManager.addComponent<Mode>(_id, mode);
    componentManager.addComponent<FrameLimit>(_id, frameLimit);
    componentManager.addComponent<Sprite>(_id, backgroundSprite);
}
