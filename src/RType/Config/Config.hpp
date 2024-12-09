/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Config.hpp
*/

#ifndef RTYPE_CONFIG_HPP_
#define RTYPE_CONFIG_HPP_

#include "spdlog/spdlog.h"

namespace rtype {
    /**
     * @class Config
     *
     * @brief Initialize all that is needed from the configuration file (e.g. log level).
     * For configuration keys that it can't do anything with, it stores them, and they are accessible from getters.
     */
    class Config {
        /**
         * @typedef An (unordered) map of spdlog log levels.
         */
        using LogLevels = std::unordered_map<std::string, spdlog::level::level_enum>;

    public:
        /**
         * @brief Config's constructor.
         * It reads and parses the config and initialize all that is needed.
         *
         * @param filename The file from which the config should be read.
         */
        explicit Config(const std::string &filename = "config.ini");

    private:
        /**
         * @brief Set the spdlog log level, depending on the log level defined in the configuration file (if applicable).
         *
         * @param reader The INIReader where to get the configuration value from.
         */
        static void _setLogLevel(const INIReader &reader);

        /**
         * @brief Map containing the log levels.
         * It permits to get the spdlog level value from its name (as string).
         */
        static LogLevels _logLevels;
    };
}

#endif /* !RTYPE_CONFIG_HPP_ */
