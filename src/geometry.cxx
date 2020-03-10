#include "geometry.hxx"

// Default constructor for "Geometry"
Geometry::Geometry() noexcept
        : brick_cols     {   10 }
        , brick_rows     {   10 }
        , top_margin     {  100 }
        , side_margin    {  170 }
        , brick_depth    {  300 }
        , bottom_margin  {   10 }
        , ball_radius    {    2 }
        , ball_speed     {    4 }
        , ball_red_velocity0 {0, -4}
        , ball_blue_velocity0 {   0, 4}
        , brick_spacing  {   10,   5 }
        , scene_dims     { 1024, 768 }
        , tank_dims_   {  20,  20 }
        , base_dims_   {50, 50}
        , board_margin_  {20}
        , wall_thickness_ {20}
        , board_size {5, 5}
        , start {board_margin_, board_margin_}
        , end {scene_dims.width - board_margin_, scene_dims.height - board_margin_ - score_height}
        , score_height {100}
        , first_board_pos {start.x, end.y + wall_thickness_}
        , second_board_pos {end.x - score_board_size.width,end.y + wall_thickness_}
        , score_board_size {75,50}
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

// Computes how large each brick can be (in a given dimension), given the
// total number of pixels available in that dimension, the number of bricks
// in that dimensions, and the number of space pixels to leave in between.
//
// PRECONDITION: divisor > 0
static int div_w_spacing(int total, int divisor, int space)
{
    if (divisor > 0)
        return (total - (divisor - 1) * space) / divisor;

    throw ge211::Client_logic_error("need at least 1 row & 1 column");
}

// Computes the dimensions of each brick from the other parameters.
ge211::Dimensions Geometry::brick_dims() const noexcept
{
    ge211::Dimensions field{scene_dims.width - 2 * side_margin,
                            brick_depth - top_margin};
    int width  = div_w_spacing(field.width, brick_cols, brick_spacing.width);
    int height = div_w_spacing(field.height, brick_rows, brick_spacing.height);
    return {width, height};
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
