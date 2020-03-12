#pragma once

#include "ball.hxx"
#include "geometry.hxx"
#include <vector>
#include "player_score.hxx"
#include "board.hxx"

struct Model
{
    ///
    /// CONSTRUCTOR
    ///

    explicit Model(Geometry const& geometry = Geometry());

    ///
    /// MEMBER FUNCTIONS
    ///

    void launch_red();

    void launch_blue();

    void update();

    void game_reset();

    void ball_red_reset();

    void ball_blue_reset();

    bool is_game_over();

    int get_winner();

    void move_base();

    bool is_touching(const ge211::Rectangle r1, const ge211::Rectangle r2);

    ge211::Position get_random_square();

    ///
    /// MEMBER VARIABLES
    ///

    Geometry const     geometry_;

    // The position and dimensions of the tanks.
    Block              tank_red_;
    Block              tank_blue_;

    // The position and dimensions of the bases.
    Block              base_red_;
    Block              base_blue_;

    // The orientation of the two tanks, 1 means pointing top, 2 right, 3 bottom, 4 left
    int                tank_red_orientation_;
    int                tank_blue_orientation_;

    // The state of the cannon balls
    Ball               ball_red_;
    Ball               ball_blue_;

    Board board_;

    // Player score object used to keep track of the score of the players
    Player_score blue_score_;
    Player_score red_score_;

};

