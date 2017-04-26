cmake_minimum_required(VERSION 3.6)
project(klondike)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS -DDEBUG)

set(SOURCE_FILES src/Card.hpp src/CardStacks.cpp src/CardStacks.hpp src/Card.cpp
        src/Error.cpp src/Error.hpp src/Deck.cpp src/Deck.hpp src/Command.cpp src/Command.hpp
        )

add_executable(test_stack ${SOURCE_FILES} src/test_card_stack.cpp)
add_executable(deck_test ${SOURCE_FILES} src/deck_test.cpp)
add_executable(klondike ${SOURCE_FILES} src/main.cpp)