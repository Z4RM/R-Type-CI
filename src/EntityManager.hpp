/*
** EPITECH PROJECT, 2024
** R_Type
** File description:
** EntityManager.hpp
*/

#ifndef ENTITY_MANAGER_HPP_
#define ENTITY_MANAGER_HPP_
#include <unordered_set>
#include <queue>

class EntityManager {
public:
    unsigned int createEntity() {
        unsigned int entity;
        if (!_available_ids.empty()) {
            entity = _available_ids.front();
            _available_ids.pop();
        } else {
            entity = _next_id++;
        }
        _active_entities.insert(entity);
        return entity;
    }

    void destroyEntity(unsigned int entity) {
        if (_active_entities.find(entity) != _active_entities.end()) {
            _active_entities.erase(entity);
            _available_ids.push(entity);
        }
    }

    bool isEntityActive(unsigned int entity) const {
        return _active_entities.find(entity) != _active_entities.end();
    }
private:
    unsigned int _next_id = 0;
    std::unordered_set<unsigned int> _active_entities;
    std::queue<unsigned int> _available_ids;
};

#endif /* !ENTITY_MANAGER_HPP_ */
