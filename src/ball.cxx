// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "ball.hxx"
#include "geometry.hxx"

static ge211::Position block_top(Block const& block,
                                   Geometry const& geometry)
{
    return {block.x+block.width/2,
            block.top_left().y + block.height/2};
}

static ge211::Position block_bottom(Block const& block,
                                Geometry const& geometry)
{
    return {block.x+block.width/2,
            block.top_left().y + block.height/2};
}

static ge211::Position block_left(Block const& block,
                                Geometry const& geometry)
{
    return {block.x+block.width/2,
            block.top_left().y + block.height/2};
}

static ge211::Position block_right(Block const& block,
                                Geometry const& geometry)
{
    return {block.x+block.width/2,
            block.top_left().y + block.height/2};
}

// It won't compile without this, so you get it for free.
Ball::Ball(Block const& paddle, Geometry const& geometry, ge211::Dimensions const& velocity)
        : radius_   (geometry.ball_radius)
        , velocity_ (velocity)
        , center_   (block_top(paddle, geometry))
        , live_     (false)
{ }

ge211::Position Ball::top_left() const
{
    // TODO: your code here
    return {center_.x - radius_,center_.y - radius_};
}

bool Ball::hits_bottom(Geometry const& geometry) const
{
    // TODO: your code here
    return center_.y + radius_ > geometry.scene_dims.height;
}

bool Ball::hits_top(Geometry const& geometry) const
{
    // TODO: your code here
    return center_.y - radius_ < 0;
}

bool Ball::hits_side(Geometry const& geometry) const
{
    // TODO: your code here
    return center_.x - radius_ < 0 ||
           center_.x + radius_ > geometry.scene_dims.width;
}

Ball Ball::next() const
{
    // TODO: your code here
    Ball result(*this);
    result.center_ += result.velocity_;
    return result;
}

bool Ball::hits_block(Block const& block) const
{
    // TODO: your code here
    return !((center_.x+radius_<block.x ||
              block.x+block.width<center_.x-radius_)||
              (center_.y+radius_<block.y ||
               block.y+block.height<center_.y-radius_));
}

void Ball::reflect_vertical()
{
    velocity_.height *= -1;
}

void Ball::reflect_horizontal()
{
    velocity_.width *= -1;
}

bool Ball::destroy_brick(std::vector<Block>& bricks) const
{
    // TODO: your code here
    for(int i=0; i < bricks.size(); i++){
        if (hits_block(bricks[i])){
            std::swap(bricks[i], bricks.back());
            bricks.pop_back();
            return true;
        }
    }
    return false;
}

bool operator==(Ball const& b1, Ball const& b2)
{
    // TODO: your code here
    return (b1.velocity_ == b2.velocity_ &&
            b1.center_ == b2.center_ &&
            b1.radius_ == b2.radius_ &&
            b1.live_ == b2.live_);
}

bool operator!=(Ball const& b1, Ball const& b2)
{
    return !(b1 == b2);
}


