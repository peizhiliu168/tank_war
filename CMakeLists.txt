cmake_minimum_required(VERSION 3.3)
project(brick_out CXX)
include(.cs211/cmake/CMakeLists.txt)

# Defines a variable to stand for the two .cxx files that implement
# the model.
set(MODEL_COMMON
        src/geometry.cxx
        src/ball.cxx
        src/model.cxx
        src/virtual_board.cxx)

# Adds a program named `brick_out` built from src/brick_out.cxx and
# the common model files.
add_program(brick_out
        src/brick_out.cxx
        src/ui.cxx
        ${MODEL_COMMON})
target_link_libraries(brick_out ge211)

# Adds a test program named `ball_test` built from test/ball_test.cxx
# and the common model files.
add_test_program(ball_test
        test/ball_test.cxx
        ${MODEL_COMMON})
target_link_libraries(ball_test ge211)

add_test_program(virtual_board_test
        test/virtual_board_test.cxx
        ${MODEL_COMMON})
target_link_libraries(virtual_board_test ge211)

# Adds a test program named `model_test` built from test/model_test.cxx
# and the common model files.
add_test_program(model_test
        test/model_test.cxx
        ${MODEL_COMMON})
target_link_libraries(model_test ge211)
