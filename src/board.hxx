#pragma once

#include <vector>
#include <ge211.hxx>
#include "virtual_board.hxx"
#include "geometry.hxx"
#include "ball.hxx"

class Board{
public:
    explicit Board(int, int);

    std::vector<ge211::geometry::Rectangle> get_squares() const;
    std::vector<ge211::geometry::Rectangle> get_walls() const;

    // takes in a rectangle, if a wall is touching the given rectangle (wall rectangle is in
    // walls_). Destroy wall (erase wall at that index) and return true. If not touching
    // rectangle, do nothing and return false.
    //
    // Use this for detecting collision with cannon.
    bool destroy_wall(Ball);

    // takes in 2 rectangles and determines whether they are touching, indicating
    // a collision.
    //
    // Use this for detecting collision with tank
    bool is_touching(ge211::Rectangle, ge211::Rectangle, const int);

    bool is_touching_wall(const ge211::Rectangle tank, const int);

private:

    void b_create();

    std::vector<ge211::geometry::Rectangle> squares_;
    std::vector<ge211::geometry::Rectangle> walls_;
    Geometry geometry_;

    ge211::Dimensions v_wall_dim_;
    ge211::Dimensions h_wall_dim_;
    ge211::Dimensions square_dim_;
    Virtual_Board virtual_board_;

};