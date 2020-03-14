cmake_minimum_required(VERSION 3.3)
project(tank_war CXX)
include(.cs211/cmake/CMakeLists.txt)

set(MODEL_COMMON
        src/geometry.cxx
        src/ball.cxx
        src/model.cxx
        src/virtual_board.cxx
        src/board.cxx
        src/player_score.cxx)

add_program(tank_war
        src/tank_war.cxx
        src/ui.cxx
        ${MODEL_COMMON})
target_link_libraries(tank_war ge211)

add_test_program(virtual_board_test
        test/virtual_board_test.cxx
        ${MODEL_COMMON})
target_link_libraries(virtual_board_test ge211)

add_test_program(board_test
        test/board_test.cxx
        ${MODEL_COMMON})
target_link_libraries(board_test ge211)

add_test_program(model_test
        test/model_test.cxx
        ${MODEL_COMMON})
target_link_libraries(model_test ge211)
