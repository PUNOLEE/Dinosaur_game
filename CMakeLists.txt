cmake_minimum_required(VERSION 3.3)
project(fp)
include(.ipd/cmake/CMakeLists.txt)

add_program(model_test
        test.cpp
        src/model.cpp
        src/controller.cpp
        src/view.cpp)
target_link_libraries(model_test ge211 catch)

add_program(fp
        src/dinogame.cpp
        src/model.cpp
        src/controller.cpp
        src/view.cpp)
target_link_libraries(fp ge211)
