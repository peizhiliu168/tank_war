#pragma once

#include <ge211.hxx>

// A structure that contains all the necessary dimensions as well
// as values of objects in the game, it could be thought that
// all other values in the game are derived from values in this
// object.
struct Geometry
{
    ///
    /// CONSTRUCTOR
    ///
    Geometry() noexcept;

    ///
    /// MEMBER VARIABLE
    ///
    // the initial speed of the ball
    int ball_speed;

    // the radius of the ball
    int ball_radius;

    // bottom margin of the screen
    int bottom_margin;

    // the margin that surround the maze/board
    int board_margin_;

    // thickness of the wall; its width or length depending on orientation
    int wall_thickness_;

    // maximum sum of rounds in the game
    int max_rounds;

    // dimension of the scene
    ge211::Dimensions scene_dims;

    // dimension of the tank
    ge211::Dimensions tank_dims_;

    // dimension of the base
    ge211::Dimensions base_dims_;

    // velocity of the red ball
    ge211::Dimensions ball_red_velocity0;

    // velocity of the blue ball
    ge211::Dimensions ball_blue_velocity0;

    // dimension of the score board
    ge211::Dimensions score_board_size;

    // dimension of the virtual board, not in px
    ge211::Dimensions board_size;

    // upper left position of the maze/board
    ge211::Position start;

    // lower right position of the maze/board
    ge211::Position end;

    // position of the blue score board
    ge211::Position blue_board_pos;

    // position of the red score board
    ge211::Position red_board_pos;


    ///
    /// MEMBER FUNCTIONS
    ///
    // calculates the top-left position of the red tank
    ge211::Position tank_top_left_red() const noexcept;

    // calculates the top-left position of the blue tank
    ge211::Position tank_top_left_blue() const noexcept;

    // calculates the top-left position of the red base
    ge211::Position base_top_left_red() const noexcept;

    // calculates the top-left position of the blue base
    ge211::Position base_top_left_blue() const noexcept;

    // calculates the dimensions of the horizontal wall for Board
    ge211::Dimensions h_wall_dim() const noexcept;

    // calculates the dimensions of the vertical wall for Board
    ge211::Dimensions v_wall_dim() const noexcept;

    // calculates the dimensions of the square for Board
    ge211::Dimensions square_dim() const noexcept;
};
