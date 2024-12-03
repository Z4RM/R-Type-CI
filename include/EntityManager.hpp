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
        if (!available_ids.empty()) {
            entity = available_ids.front();
            available_ids.pop();
        } else {
            entity = next_id++;
        }
        active_entities.insert(entity);
        return entity;
    }

    void destroyEntity(unsigned int entity) {
        if (active_entities.find(entity) != active_entities.end()) {
            active_entities.erase(entity);
            available_ids.push(entity);
        }
    }

    bool isEntityActive(unsigned int entity) const {
        return active_entities.find(entity) != active_entities.end();
    }
private:
    unsigned int next_id = 0;
    std::unordered_set<unsigned int> active_entities;
    std::queue<unsigned int> available_ids;
};

#endif /* !ENTITY_MANAGER_HPP_ */
