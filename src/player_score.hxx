#pragma once

// an object to keep track of, modify, and access
// a player's score
class Player_score{
public:
    ///
    /// CONSTRUCTOR
    ///
    // constructs a new player with an initial score of 0
    void Player();

    ///
    /// PUBLIC MEMBER FUNCTIONS
    ///
    // gets score of player
    int get_score();

    // add 1 to score of player
    void plus_one();

    // reset score of the player back to 0
    void reset_score();

private:
    ///
    /// PRIVATE MEMBER VARIABLES
    ///
    // keeps track of the player
    int score_;

};