#include "model.hxx"
Model::Model(Geometry const& geometry)
        : geometry_(geometry)
        , tank_red_(Block::from_top_left(geometry_.tank_top_left_red(),
                                       geometry_.tank_dims_))
        , tank_blue_(Block::from_top_left(geometry_.tank_top_left_blue(),
                                      geometry_.tank_dims_))
        , tank_red_orientation_(1)
        , tank_blue_orientation_(3)
        , ball_red_(tank_red_, geometry_, geometry_.ball_red_velocity0)
        , ball_blue_(tank_blue_, geometry_, geometry_.ball_blue_velocity0)
        , base_red_(Block::from_top_left(geometry_.base_top_left_red(),
                                         geometry_.base_dims_))
        , base_blue_(Block::from_top_left(geometry_.base_top_left_blue(),
                                          geometry_.base_dims_))
        , first_score_()
        , second_score_()
        , board_(geometry_.board_size.width, geometry_.board_size.height)
{
}
///Launch cannon balls
void Model::launch_red()
{
    ball_red_.live_ = true;
}
void Model::launch_blue()
{
    ball_blue_.live_ = true;
}
///Update cannon balls
void Model::update()
{
    //Ball ball1(ball_red_.next());
    //Ball ball2(ball_blue_.next());
    if (ball_red_.hits_ball(ball_blue_)&&ball_red_.live_&&ball_blue_.live_){
        ball_red_.live_ = false;
        ball_blue_.live_ = false;
        ball_blue_reset();
        ball_red_reset();
    }
    Ball b1(ball_red_.next());
    if (ball_red_.live_){
        if (b1.hits_bottom(geometry_)||
            b1.hits_top(geometry_)||
            b1.hits_side(geometry_)){
            ball_red_.live_ = false;
            ball_red_reset();
            return;
        }
        if (b1.hits_block(tank_blue_)||
            b1.hits_block(base_blue_)){
            game_reset();
            return;
        }
        ball_red_ = ball_red_.next();
    } else{
        ball_red_reset();
    }
    Ball b2(ball_blue_.next());
    if (ball_blue_.live_){
        if (b2.hits_bottom(geometry_)||
            b2.hits_top(geometry_)||
            b2.hits_side(geometry_)){
            ball_blue_.live_ = false;
            ball_blue_reset();
            return;
        }
        if (b2.hits_block(tank_red_)||
            b2.hits_block(base_red_)){
            game_reset();
            return;
        }
        ball_blue_ = ball_blue_.next();
    } else{
        ball_blue_reset();
    }

}

void Model::game_reset() {
        tank_red_ = Block::from_top_left(geometry_.tank_top_left_red(),
                                       geometry_.tank_dims_);
        tank_blue_ = Block::from_top_left(geometry_.tank_top_left_blue(),
                                         geometry_.tank_dims_);
        tank_red_orientation_ = 1;
        tank_blue_orientation_ = 3;
        ball_red_.live_ = false;
        ball_blue_.live_ = false;
}

void Model::ball_red_reset() {
    if (tank_red_orientation_ == 1){
        ball_red_.center_.x = tank_red_.x+tank_red_.width/2;
        ball_red_.center_.y = tank_red_.top_left().y - geometry_.ball_radius - 1;
        ball_red_.velocity_ = {0, -geometry_.ball_speed};
    }
    if (tank_red_orientation_ == 2){
        ball_red_.center_.y = tank_red_.y+tank_red_.height/2;
        ball_red_.center_.x = tank_red_.top_left().x + tank_red_.width+geometry_.ball_radius+1;
        ball_red_.velocity_ = {geometry_.ball_speed, 0};
    }
    if (tank_red_orientation_ == 3){
        ball_red_.center_.x = tank_red_.x+tank_red_.width/2;
        ball_red_.center_.y = tank_red_.top_left().y + tank_red_.height+geometry_.ball_radius+1;
        ball_red_.velocity_ = {0, geometry_.ball_speed};
    }
    if (tank_red_orientation_ == 4){
        ball_red_.center_.y = tank_red_.y+tank_red_.height/2;
        ball_red_.center_.x = tank_red_.top_left().x - geometry_.ball_radius - 1;
        ball_red_.velocity_ = {-geometry_.ball_speed, 0};
    }
}

void Model::ball_blue_reset() {
    if (tank_blue_orientation_ == 1){
        ball_blue_.center_.x = tank_blue_.x+tank_blue_.width/2;
        ball_blue_.center_.y = tank_blue_.top_left().y - geometry_.ball_radius - 1;
        ball_blue_.velocity_ = {0, -geometry_.ball_speed};
    }
    if (tank_blue_orientation_ == 2){
        ball_blue_.center_.y = tank_blue_.y+tank_blue_.height/2;
        ball_blue_.center_.x = tank_blue_.top_left().x + tank_blue_.width+geometry_.ball_radius+1;
        ball_blue_.velocity_ = {geometry_.ball_speed, 0};
    }
    if (tank_blue_orientation_ == 3){
        ball_blue_.center_.x = tank_blue_.x+tank_blue_.width/2;
        ball_blue_.center_.y = tank_blue_.top_left().y + tank_blue_.height+geometry_.ball_radius+1;
        ball_blue_.velocity_ = {0, geometry_.ball_speed};
    }
    if (tank_blue_orientation_ == 4){
        ball_blue_.center_.y = tank_blue_.y+tank_blue_.height/2;
        ball_blue_.center_.x = tank_blue_.top_left().x - geometry_.ball_radius - 1;
        ball_blue_.velocity_ = {-geometry_.ball_speed, 0};
    }
}
