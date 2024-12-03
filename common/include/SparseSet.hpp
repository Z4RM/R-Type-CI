/*
** EPITECH PROJECT, 2024
** R_Type
** File description:
** SparseSet.hpp
*/

#ifndef SPARSESET_HPP
#define SPARSESET_HPP

#include <vector>
#include <unordered_map>

template <typename T>
class SparseSet {
public:
    void addComponent(unsigned int entity, const T& component) {
        if (sparse.find(entity) == sparse.end()) {
            sparse[entity] = dense.size();
            dense.push_back(entity);
            components.push_back(component);
        }
    }

    void removeComponent(unsigned int entity) {
        if (sparse.find(entity) != sparse.end()) {
            size_t index = sparse[entity];
            unsigned int last_entity = dense.back();

            dense[index] = last_entity;
            sparse[last_entity] = index;

            dense.pop_back();
            components[index] = components.back();
            components.pop_back();

            sparse.erase(entity);
        }
    }

    T* getComponent(unsigned int entity) {
        if (sparse.find(entity) != sparse.end()) {
            return &components[sparse[entity]];
        }
        return nullptr;
    }

    const std::vector<unsigned int>& getEntities() const {
        return dense;
    }

private:
    std::unordered_map<unsigned int, size_t> sparse;
    std::vector<unsigned int> dense;
    std::vector<T> components;
};

#endif //SPARSESET_HPP
