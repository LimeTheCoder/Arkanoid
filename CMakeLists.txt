cmake_minimum_required(VERSION 3.5)
project(LionCourse)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp play_state.cpp play_state.h ball.cpp ball.h paddle.cpp paddle.h game_object.cpp game_object.h command.h block.cpp block.h game_state.h game.cpp game.h menu_state.cpp menu_state.h resourse_manager.cpp resourse_manager.h scores_state.cpp scores_state.h)
add_executable(LionCourse ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(LionCourse ${SFML_LIBRARIES})
endif()