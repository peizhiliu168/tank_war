// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "model.hxx"

Model::Model(Geometry const& geometry)
        : geometry_(geometry)
        , tank1_(Block::from_top_left(geometry_.tank_top_left1(),
                                       geometry_.tank_dims_))
        , tank2_(Block::from_top_left(geometry_.tank_top_left2(),
                                      geometry_.tank_dims_))
        , ball_red_(tank1_, geometry_, geometry_.ball_red_velocity0)
        , ball_blue_(tank2_, geometry_, geometry_.ball_blue_velocity0)
        , first_score_()
        , second_score_()
        , board_(geometry_.board_size.width, geometry_.board_size.height)
{}



// Freebie.
void Model::launch_red()
{
    ball_red_.live_ = true;
}

void Model::launch_blue()
{
    ball_blue_.live_ = true;
}

// Warning! Until you write code inside these member functions
// that uses at least one member variable, CLion is going to
// insist that you can make this function static. Don’t believe
// it! You’ll regret the change if you do once you want to
// access member variables, since a static member function
// doesn’t have access to an instance. (You should delete this
// warning after you’ve read it.)
//
// TL;DR: Don't go adding `static` to members.

void Model::update(int boost)
{
    Ball b1(ball_red_.next());
    if (ball_red_.live_){
        if (b1.hits_bottom(geometry_)||b1.hits_top(geometry_)||b1.hits_side(geometry_)||b1.destroy_brick(bricks_)){
            ball_red_.live_ = false;
            ball_red_.velocity_ = geometry_.ball_red_velocity0;
            ball_red_.center_.y = tank1_.top_left().y - geometry_.ball_radius - 1;
            ball_red_.center_.x = tank1_.x+tank1_.width/2;
            return;
        }
        //if (b1.hits_block(tank1_)) {
            //ball_red_.reflect_vertical();
            //ball_red_.velocity_.width = b1.velocity_.width + boost;
        //}
        // need to add more to this so that it can destroy the opponent
        ball_red_ = ball_red_.next();
    } else{
        Ball b(ball_red_);
        b.center_.x = tank1_.x+tank1_.width/2;
        b.center_.y = tank1_.y - b.radius_;
        ball_red_ = b;
    }
    Ball b2(ball_blue_.next());
    if (ball_blue_.live_){
        if (b2.hits_bottom(geometry_)||b2.hits_top(geometry_)||b2.hits_side(geometry_)||b2.destroy_brick(bricks_)){
            ball_blue_.live_ = false;
            ball_blue_.velocity_ = geometry_.ball_blue_velocity0;
            ball_blue_.center_.y = tank2_.top_left().y + tank2_.height + geometry_.ball_radius + 1;
            ball_blue_.center_.x = tank2_.x+tank2_.width/2;
            return;
        }
        //if (b1.hits_block(tank1_)) {
        //ball_red_.reflect_vertical();
        //ball_red_.velocity_.width = b1.velocity_.width + boost;
        //}
        // need to add more to this so that it can destroy the opponent
        ball_blue_ = ball_blue_.next();
    } else{
        Ball b(ball_blue_);
        b.center_.x = tank2_.x+tank2_.width/2;
        b.center_.y = tank2_.y + tank2_.height + b.radius_;
        ball_blue_ = b;
    }
}


