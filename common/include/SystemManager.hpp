/*
** EPITECH PROJECT, 2024
** R_Type
** File description:
** SystemManager.hpp
*/

#ifndef SYSTEMMANAGER_HPP
#define SYSTEMMANAGER_HPP

#include <vector>
#include <functional>

class SystemManager {
public:
    void addSystem(const std::function<void()>& system) {
        systems.push_back(system);
    }

    void updateSystems() {
        for (auto& system : systems) {
            system();
        }
    }
private:
    std::vector<std::function<void()>> systems;
};

#endif //SYSTEMMANAGER_HPP
