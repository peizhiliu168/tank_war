#include "board.hxx"
#include <catch.hxx>
#include <math.h>
#include "geometry.hxx"

TEST_CASE("create and reset virtual board")
{
    Geometry geometry{};

    Board b_board{geometry.board_size.width, geometry.board_size.height};
    std::vector<ge211::Rectangle> squares = b_board.get_squares();
    std::vector<ge211::Rectangle> walls = b_board.get_walls();

    CHECK(squares.size() == pow(geometry.board_size.width, 2));
    CHECK((geometry.board_size.width - 1) *
          (geometry.board_size.height - 1) == walls.size());

    b_board.reset();
    walls = b_board.get_walls();
    squares = b_board.get_squares();

    CHECK(squares.size() == pow(geometry.board_size.width, 2));
    CHECK((geometry.board_size.width - 1) *
          (geometry.board_size.height - 1) == walls.size());

}
