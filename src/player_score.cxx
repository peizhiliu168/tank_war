#include "player_score.hxx"

void Player_score::Player() {
    score_ = 0;
}

int Player_score::get_score() {
    return score_;
}

void Player_score::plus_one() {
    ++score_;
}

void Player_score::reset_score() {
    score_ = 0;
}
