set(COMMON_SRC
        src/foo.cpp
)

set(COMMON_HEADERS
        include/EntityManager.hpp
        include/SparseSet.hpp
        include/ComponentManager.hpp
        include/SystemManager.hpp
)

add_library(r-type_common STATIC ${COMMON_SRC} ${COMMON_HEADERS})
target_include_directories(r-type_common PUBLIC include)
target_link_libraries(r-type_common PUBLIC spdlog::spdlog)
