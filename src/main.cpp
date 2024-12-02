/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main.cpp
*/

// TODO: this is a sample code, remove it

#include "spdlog/spdlog.h"

int main() {
    #ifdef RTYPE_IS_CLIENT
        spdlog::info("R-Type client launched");
    #endif
    #ifdef RTYPE_IS_SERVER
        spdlog::info("R-Type server launched on port 4242")
    #endif
    spdlog::info("R-Type launched");
    return 0;
}
