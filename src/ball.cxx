#include "ball.hxx"
#include "geometry.hxx"

static ge211::Position block_top(Block const& block,
                                   Geometry const& geometry)
{
    return {block.x+block.width/2,
            block.top_left().y + block.height/2};
}

Ball::Ball(Block const& paddle, Geometry const& geometry, ge211::Dimensions const& velocity)
        : radius_   (geometry.ball_radius)
        , velocity_ (velocity)
        , center_   (block_top(paddle, geometry))
        , live_     (false)
{ }

ge211::Position Ball::top_left() const
{
    return {center_.x - radius_,center_.y - radius_};
}

bool Ball::hits_bottom(Geometry const& geometry) const
{
    return center_.y + radius_ > geometry.scene_dims.height;
}

bool Ball::hits_top(Geometry const& geometry) const
{
    return center_.y - radius_ < 0;
}

bool Ball::hits_side(Geometry const& geometry) const
{
    return center_.x - radius_ < 0 ||
           center_.x + radius_ > geometry.scene_dims.width;
}

Ball Ball::next() const
{
    Ball result(*this);
    result.center_ += result.velocity_;
    return result;
}

bool Ball::hits_block(Block const& block) const
{
    return !((center_.x+radius_<block.x ||
              block.x+block.width<center_.x-radius_)||
              (center_.y+radius_<block.y ||
               block.y+block.height<center_.y-radius_));
}

bool Ball::hits_ball(Ball const& ball) const{
    return !((center_.x+radius_< ball.center_.x-ball.radius_ ||
                ball.center_.x+ball.radius_<center_.x-radius_)||
             (center_.y+radius_<ball.center_.y-ball.radius_ ||
              ball.center_.y+ball.radius_<center_.y-radius_));
}

bool operator==(Ball const& b1, Ball const& b2)
{
    return (b1.velocity_ == b2.velocity_ &&
            b1.center_ == b2.center_ &&
            b1.radius_ == b2.radius_ &&
            b1.live_ == b2.live_);
}

bool operator!=(Ball const& b1, Ball const& b2)
{
    return !(b1 == b2);
}