#pragma once

#include <ge211.hxx>

struct Geometry
{
    Geometry() noexcept;

    ge211::Dimensions scene_dims;

    ge211::Dimensions tank_dims_;

    ge211::Dimensions base_dims_;

    int ball_radius;

    ge211::Dimensions ball_red_velocity0;
    ge211::Dimensions ball_blue_velocity0;

    int ball_speed;

    int top_margin;

    int side_margin;

    int brick_depth;

    int bottom_margin;

    int board_margin_;

    int wall_thickness_;

    int score_height;

    ge211::Dimensions score_board_size;

    ge211::Dimensions board_size;

    ge211::Position start;

    ge211::Position end;

    ge211::Position first_board_pos;

    ge211::Position second_board_pos;

    ge211::Position tank_top_left_red() const noexcept;
    ge211::Position tank_top_left_blue() const noexcept;

    ge211::Position base_top_left_red() const noexcept;
    ge211::Position base_top_left_blue() const noexcept;

    ge211::Dimensions h_wall_dim() const noexcept;

    ge211::Dimensions v_wall_dim() const noexcept;

    ge211::Dimensions square_dim() const noexcept;
};
