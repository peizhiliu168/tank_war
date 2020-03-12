#include "geometry.hxx"

// Default constructor for "Geometry"
Geometry::Geometry() noexcept
        : bottom_margin  {   10 }
        , ball_radius    {    2 }
        , ball_speed     {    4 }
        , ball_red_velocity0 {0, -4}
        , ball_blue_velocity0 {   0, 4}
        , scene_dims     { 1024, 768 }
        , tank_dims_   {  20,  20 }
        , base_dims_   {50, 50}
        , board_margin_  {20}
        , wall_thickness_ {20}
        , board_size {10, 10}
        , start {board_margin_, board_margin_}
        , end {scene_dims.width - board_margin_, scene_dims.height - board_margin_}
        , blue_board_pos {end.x - score_board_size.width, start.y}
        , red_board_pos {start.x, scene_dims.height - score_board_size.height - start.y}
        , score_board_size {75,50}
        , max_rounds {11}
{ }

ge211::Position Geometry::tank_top_left_red() const noexcept
{
    return { scene_dims.width / 2,
             scene_dims.height - bottom_margin - tank_dims_.height };
}
ge211::Position Geometry::tank_top_left_blue() const noexcept
{
    return { scene_dims.width / 2,
             bottom_margin};
}

ge211::Position Geometry::base_top_left_red() const noexcept
{
    return { scene_dims.width / 2 + tank_dims_.width/2 - base_dims_.width/2,
             scene_dims.height - base_dims_.height };
}
ge211::Position Geometry::base_top_left_blue() const noexcept
{
    return { scene_dims.width / 2 + tank_dims_.width/2 - base_dims_.width/2,
             0};
}

static int div_w_spacing(int total, int divisor, int space)
{
    if (divisor > 0)
        return (total - (divisor - 1) * space) / divisor;

    throw ge211::Client_logic_error("need at least 1 row & 1 column");
}

ge211::Dimensions Geometry::square_dim() const noexcept
{
    int width = ((end.x - start.x) - ((board_size.width + 1) * wall_thickness_)) / board_size.width;
    int height = ((end.y - start.y) - ((board_size.height + 1) * wall_thickness_)) / board_size.height;
    return {width, height};
}

ge211::Dimensions Geometry::v_wall_dim() const noexcept
{
    int width = wall_thickness_;
    int height = square_dim().height + 2 * wall_thickness_;
    return {width, height};
}

ge211::Dimensions Geometry::h_wall_dim() const noexcept
{
    int width = square_dim().width + 2 * wall_thickness_;
    int height = wall_thickness_;
    return {width, height};
}
