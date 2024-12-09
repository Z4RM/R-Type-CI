/*
** EPITECH PROJECT, 2024
** RType
** File description:
** RType.hpp
*/

#ifndef RTYPE_RTYPE_HPP_
#define RTYPE_RTYPE_HPP_

namespace rtype {
    /**
     * @class RType
     *
     * @brief The main class of the R-Type, containing, among others, the entry points.
     */
    class RType {
    public:
        /**
         * @brief The entry point of the R-Type.
         * Should be the only statement in the program main function, used as is:
         * ```cpp
         * #include "RType/RType.hpp"
         *
         * int main() {
         *     return rtype::RType::run();
         * }
         * ```
         *
         * @return The exit status of the program.
         */
        static int run();
    };
}

#endif /* !RTYPE_RTYPE_HPP_ */
