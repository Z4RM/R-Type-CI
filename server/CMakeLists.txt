set(SERVER_SRC
        src/main.cpp
)

set(SERVER_HEADERS
        include/foo.hpp
)

add_executable(r-type_server ${SERVER_SRC} ${SERVER_HEADERS})
target_include_directories(r-type_server PUBLIC include)
target_link_libraries(r-type_server PRIVATE r-type_common)
