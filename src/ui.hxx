#pragma once

#include "model.hxx"
#include <ge211.hxx>
#include <string>
// NOTE: player number and player color will used interchangeably
// blue player = player 1, red player = player 2

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

    ge211::Font win_font_{"timesbd.ttf", 90};
    ge211::Font player_font_{"times.ttf", 20};
    ge211::Font score_font_{"times.ttf", 30};

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

    static bool tank_collision(ge211::Rectangle, ge211::Rectangle);

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

    ge211::Text_sprite first_score
            {std::to_string(model_.blue_score_.get_score()), score_font_};

    ge211::Text_sprite second_score
            {std::to_string(model_.red_score_.get_score()), score_font_};

    ge211::Text_sprite player_one
            {"Player 1", player_font_};
    ge211::Text_sprite player_two
            {"Player 2", player_font_};

    ge211::Text_sprite player_1_win
            {"Winner is Player 1!", win_font_};
    ge211::Text_sprite player_2_win
            {"Winner is Player 2!", win_font_};
};
