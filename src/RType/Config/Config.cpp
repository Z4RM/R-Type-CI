/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Config.cpp
*/

#include "Config.hpp"

const rtype::Config::LogLevels rtype::Config::_logLevels = {
        {"trace",    spdlog::level::trace},
        {"debug",    spdlog::level::debug},
        {"info",     spdlog::level::info},
        {"warn",     spdlog::level::warn},
        {"err",      spdlog::level::err},
        {"critical", spdlog::level::critical},
        {"off",      spdlog::level::off}
};

rtype::Config::Config(const std::string &filename) {
    INIReader reader(filename);

    _setLogLevel(reader);
}

void rtype::Config::_setLogLevel(const INIReader &reader) {
    auto logLevel = reader.Get("log", "level", "");

    if (!logLevel.empty()) {
        if (_logLevels.find(logLevel) == _logLevels.end())
            spdlog::warn("\"\33[3m" + logLevel + "\33[0m\" is not a valid log level");
        else
            spdlog::set_level(_logLevels.at(logLevel));
    }
}
