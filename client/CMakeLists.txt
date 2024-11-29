set(CLIENT_SRC
        src/main.cpp
)

set(CLIENT_HEADERS
        include/foo.hpp
)

add_executable(r-type_client ${CLIENT_SRC} ${CLIENT_HEADERS})
target_include_directories(r-type_client PUBLIC include)
target_link_libraries(r-type_client PRIVATE r-type_common)
