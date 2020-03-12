#pragma once

#include <vector>
#include <ge211.hxx>
#include "virtual_board.hxx"
#include "geometry.hxx"
#include "ball.hxx"

// A class for a Board object, used to convert a
// virtual_board into actual px values for walls
// and square that can be displayed on the screen.
class Board{
public:
    ///
    /// CONSTRUCTOR
    ///
    // constructs the actual board with dimensions in px from
    // the virtual board as well as initialize member variables
    explicit Board(int, int);

    ///
    /// PUBLIC MEMBER FUNCTIONS
    ///
    // returns a copy of the squares_ member variable to the caller
    std::vector<ge211::geometry::Rectangle> get_squares() const;

    // returns a copy of the walls_ member variable to the caller
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

    // given the orientation of the tank and two rectangles involved in
    // the collision, determine whether the tank has collided,
    // also works for general collision between two rectangles if the
    // ori paramater is set to 0
    bool is_touching_wall(const ge211::Rectangle, const int);

    // resets the board by creating a new virtual_board_ and updating walls_
    void reset();

private:

    ///
    /// PRIVATE MEMBER FUNCTIONS
    ///
    // takes a Virtual_board and creates a real board in px by filling
    // vectors walls_ and squares_ with rectangles
    void b_create();

    ///
    /// PRIVATE MEMBER VARIABLES
    ///
    // vector of ge211 rectangles, mainly used to determine the relative
    // locations of the walls
    std::vector<ge211::geometry::Rectangle> squares_;

    // vector of ge211 rectangles, the ui draws these walls onto the
    // screen
    std::vector<ge211::geometry::Rectangle> walls_;

    // geometry object from the Geometry class
    Geometry geometry_;

    // width of the virtual board
    int width_;

    // height of the virtual board
    int height_;

    // dimensions of vertical walls
    ge211::Dimensions v_wall_dim_;

    // dimensions of horizontal walls
    ge211::Dimensions h_wall_dim_;

    // dimensions of the squares in suqares_
    ge211::Dimensions square_dim_;

    // houses a Virtual_board object with a vector of
    // "square" structs
    Virtual_board virtual_board_;

};