#include "virtual_board.hxx"
#include <catch.hxx>

TEST_CASE("initialized bool array")
{
    Virtual_board v_board{5, 5};
    for (int i = 0; i < v_board.width(); ++i){
        for (int j = 0; j < v_board.height(); ++j) {
            CHECK(v_board.get_square_given_pos({i, j})
            .side_pres.size() == 4);
        }
    }

    Virtual_board v_board1{5, 10};
    for (int i = 0; i < v_board.width(); ++i){
        for (int j = 0; j < v_board.height(); ++j) {
            CHECK(v_board.get_square_given_pos({i, j})
                          .side_pres.size() == 4);
        }
    }

    Virtual_board v_board2{10, 5};
    for (int i = 0; i < v_board.width(); ++i){
        for (int j = 0; j < v_board.height(); ++j) {
            CHECK(v_board.get_square_given_pos({i, j})
                          .side_pres.size() == 4);
        }
    }
}

TEST_CASE("all squares visited")
{
    Virtual_board v_board{5, 5};
    for (int i = 0; i < v_board.width(); ++i){
        for (int j = 0; j < v_board.height(); ++j) {
            CHECK(v_board.get_square_given_pos({i, j}).visited);
        }
    }

    Virtual_board v_board1{5, 10};
    for (int i = 0; i < v_board.width(); ++i){
        for (int j = 0; j < v_board.height(); ++j) {
            CHECK(v_board.get_square_given_pos({i, j}).visited);
        }
    }

    Virtual_board v_board2{10, 5};
    for (int i = 0; i < v_board.width(); ++i){
        for (int j = 0; j < v_board.height(); ++j) {
            CHECK(v_board.get_square_given_pos({i, j}).visited);
        }
    }
}

