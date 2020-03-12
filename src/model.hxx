#pragma once

#include "ball.hxx"
#include "geometry.hxx"
#include <vector>
#include "player_score.hxx"
#include "board.hxx"

// The game itself but without the UI. Controls all the
// logic of how the game is run for each step.
struct Model
{
    ///
    /// CONSTRUCTOR
    ///
    // constructs a model of the game given geometry
    explicit Model(Geometry const& geometry = Geometry());

    ///
    /// MEMBER FUNCTIONS
    ///
    // makes the red cannon ball live
    void launch_red();

    // makes the blue cannon balls live
    void launch_blue();

    // update the cannon balls depending on if they are live or dead
    // detects any collision of the cannon balls with other objects
    void update();

    // resets the positions of the base, tanks, cannonballs, as well as
    // regenerate a new set of walls/maze to restart a new round
    void game_reset();

    // resets the red cannon ball so that it is on its corresponding tank
    void ball_red_reset();

    // resets the blue cannon ball so that it is on its corresponding tank
    void ball_blue_reset();

    // calculates the total sum of score of both players to determine
    // whether the game is over
    bool is_game_over();

    // compares the scores of the players and determine the winner
    int get_winner();

    // sets the base as well as tanks at the randomly generated position
    void move_base();

    // helper function to determine whether two rectangles are overlapping
    bool is_touching(const ge211::Rectangle r1, const ge211::Rectangle r2);

    // randomly gets the top-left position of a square in the first row of
    // the board
    ge211::Position get_random_square();

    ///
    /// MEMBER VARIABLES
    ///
    // Geometry object
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

    // Player score object used to keep track of the score of the players
    Player_score blue_score_;
    Player_score red_score_;

    // Houses the Board object in the model
    Board board_;

};

