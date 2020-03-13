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

TEST_CASE("board within screen dim")
{
    Geometry geometry{};

    Board b_board{geometry.board_size.width, geometry.board_size.height};

    std::vector<ge211::Rectangle> walls = b_board.get_walls();
    for (ge211::Rectangle  wall : walls){
        CHECK(wall.top_left().x >= 0);
        CHECK(wall.top_left().x <= geometry.scene_dims.width);
        CHECK(wall.top_left().y >= 0);
        CHECK(wall.top_left().y <= geometry.scene_dims.width);

        CHECK(wall.bottom_right().x >= 0);
        CHECK(wall.bottom_right().x <= geometry.scene_dims.width);
        CHECK(wall.bottom_right().y >= 0);
        CHECK(wall.bottom_right().y <= geometry.scene_dims.width);

    }
}
