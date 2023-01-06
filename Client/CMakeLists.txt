cmake_minimum_required(VERSION 3.18)
project(Client)

set(CMAKE_CXX_STANDARD 14)

#CLIENT CMAKE
set(SOURCE
        Client/graphic/Graphic.cpp
        Client/graphic/Settings.cpp
        )
set(HEADERS
        Client/graphic/Graphic.h
        Client/graphic/Settings.h
        )
add_executable(Client Client/client.cpp)

#LOCAL SFML
set(SFML_DIR "C:\\Users\\jgres\\Desktop\\Princípy operačných systémov\\SP POS\\Človeče\\SFML\\lib\\cmake\\SFML")
set(SFML_STATIC_LIBRARIES TRUE)
include_directories("C:/SFML/include")

find_package(SFML COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Clovece sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
