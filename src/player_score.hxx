#pragma once

class Player_score{
public:
    void Player();

    // gets score of player
    int get_score();

    // add 1 to score of player
    void plus_one();

    // reset score of the player back to 0
    void reset_score();

private:
    // keeps track of the player
    int score_;

};