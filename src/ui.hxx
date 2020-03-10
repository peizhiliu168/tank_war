#pragma once

#include "model.hxx"
#include <ge211.hxx>

///
/// VIEW CONSTANTS
///

extern ge211::Color const ball_red_color, ball_blue_color, tank_color, brick_color, base_color;

///
/// MAIN UI STRUCT
///

struct Ui : ge211::Abstract_game
{
    ///
    /// CONSTRUCTOR
    ///

    explicit Ui(Model&);

    bool j;
    bool p;
    bool w;
    bool a;
    bool s;
    bool d;
    bool up;
    bool down;
    bool left;
    bool right;

    ///
    /// MEMBER FUNCTIONS (for the view)
    ///

    ge211::Dimensions initial_window_dimensions() const override;

    void draw(ge211::Sprite_set&) override;

    ///
    /// MEMBER FUNCTIONS (for the controller)
    ///

    void on_key(ge211::Key) override;

    void on_key_down(ge211::Key) override;

    void on_key_up(ge211::Key) override;

    void on_frame(double dt) override;

    bool tank_collision(ge211::Rectangle, ge211::Rectangle);

    ///
    /// MEMBER VARIABLE (model reference)
    ///

    Model& model_;

    ///
    /// MEMBER VARIABLES (for the view)
    ///

    ge211::Circle_sprite    const
            ball_red_sprite_    {model_.geometry_.ball_radius,  ball_red_color};

    ge211::Circle_sprite    const
            ball_blue_sprite_    {model_.geometry_.ball_radius,  ball_blue_color};

    ge211::Rectangle_sprite const
            tank_sprite_  {model_.geometry_.tank_dims_, tank_color};

    ge211::Rectangle_sprite const
            base_sprite_  {model_.geometry_.base_dims_, base_color};

    ge211::Rectangle_sprite const
            v_wall_   {model_.geometry_.v_wall_dim(), brick_color};

    ge211::Rectangle_sprite const
            h_wall_   {model_.geometry_.h_wall_dim(), brick_color};

    ge211::Rectangle_sprite const
            second_score_board {model_.geometry_.score_board_size,
                               ge211::Color::from_rgba(51, 255, 255)};

    ge211::Rectangle_sprite const
            first_score_board {model_.geometry_.score_board_size,
                                ge211::Color::from_rgba(255,51,51)};
};
