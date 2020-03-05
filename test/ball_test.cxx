#include "ball.hxx"
#include "model.hxx"
#include <catch.hxx>

Block const paddle{100, 400, 100, 20};

TEST_CASE("Ball::Ball")
{
    Geometry geometry;
    Ball ball(paddle, geometry);

    CHECK( ball.center_.x == 150 );
    CHECK( ball.center_.y == 394 );
}
TEST_CASE("Ball::hits_side")
{
    Geometry geometry;
    Ball ball(paddle, geometry);

    CHECK_FALSE( ball.hits_side(geometry) );
    ball.center_.x = 1;
    CHECK( ball.hits_side(geometry) );
    ball.center_.x = geometry.scene_dims.width - 1;
    CHECK( ball.hits_side(geometry) );
    ball.center_.x = geometry.scene_dims.width / 2;
    CHECK_FALSE( ball.hits_side(geometry) );
}
TEST_CASE("Ball::==")
{
    Geometry geometry;
    Ball ball1(paddle, geometry);
    Ball ball2(paddle, geometry);
    CHECK(ball1 == ball2);
}
TEST_CASE("Ball::!=")
{
    Geometry geometry;
    Ball ball1(paddle, geometry);
    Ball ball2(paddle, geometry);
    ball2.center_.x = 1;
    CHECK(ball1 != ball2);
    Ball ball3(paddle, geometry);
    ball3.velocity_.height = 1;
    CHECK(ball1 != ball3);
    Ball ball4(paddle, geometry);
    ball4.radius_ = 1;
    CHECK(ball1 != ball4);
    Ball ball5(paddle, geometry);
    ball5.live_ = true;
    CHECK(ball1 != ball5);
}
TEST_CASE("Ball::destroy_brick")
{
    Geometry geometry;
    Model m(geometry);
    m.bricks_.clear();
    m.bricks_.push_back({250, 200, 100, 20});
    m.ball_.live_ = true;
    m.ball_.center_ = {300, 400};
    m.ball_.velocity_ = {0, -50};
    Ball ball(m.ball_);
    m.update(0);
    ball = ball.next();
    CHECK( m.ball_ == ball );
    m.update(0);
    ball = ball.next();
    CHECK( m.ball_ == ball );
    m.update(0);
    ball = ball.next();
    CHECK( m.ball_ == ball );
    CHECK( m.ball_.center_.y == ball.center_.y );
    CHECK( m.bricks_.size() == 1 );
    m.update(0);
    ball.velocity_ *= -1;
    ball = ball.next();
    CHECK( m.ball_ == ball );
    CHECK( m.ball_.center_.x == ball.center_.x );
    CHECK( m.ball_.center_.y == ball.center_.y );
    CHECK( m.ball_.velocity_.width == ball.velocity_.width );
    CHECK( m.ball_.velocity_.height == ball.velocity_.height );
    CHECK( m.bricks_.empty() );
    CHECK(ball.destroy_brick(m.bricks_)==false);
}
TEST_CASE("Ball::hits_block from right")
{
    Geometry geometry;
    Model m(geometry);
    m.bricks_.clear();
    m.bricks_.push_back({250, 200, 100, 20});
    m.ball_.live_ = true;
    m.ball_.center_ = {400, 200};
    m.ball_.velocity_ = {-50, 0};
    m.update(0);
    CHECK(m.bricks_.empty());
}
TEST_CASE("Ball::hits_block from left")
{
    Geometry geometry;
    Model m(geometry);
    m.bricks_.clear();
    m.bricks_.push_back({250, 200, 100, 20});
    m.ball_.live_ = true;
    m.ball_.center_ = {200, 200};
    m.ball_.velocity_ = {50, 0};
    m.update(0);
    CHECK(m.bricks_.empty());
}
TEST_CASE("Ball::hits_block from top")
{
    Geometry geometry;
    Model m(geometry);
    m.bricks_.clear();
    m.bricks_.push_back({250, 200, 100, 20});
    m.ball_.live_ = true;
    m.ball_.center_ = {250, 150};
    m.ball_.velocity_ = {0, 50};
    m.update(0);
    CHECK(m.bricks_.empty());
}
TEST_CASE("Ball::hits_block from bottom")
{
    Geometry geometry;
    Model m(geometry);
    m.bricks_.clear();
    m.bricks_.push_back({250, 200, 100, 20});
    m.ball_.live_ = true;
    m.ball_.center_ = {250, 250};
    m.ball_.velocity_ = {0, -50};
    m.update(0);
    CHECK(m.bricks_.empty());
}
TEST_CASE("Ball::next")
{
    Geometry geometry;
    Ball ball(paddle, geometry);
    Ball ball1(ball.next());
    CHECK(ball1.center_ == ball.center_+ball.velocity_);
}
TEST_CASE("Ball::hits_top")
{
    Geometry geometry;
    Ball ball(paddle, geometry);
    CHECK(ball.hits_top(geometry) == false);
    ball.velocity_.height = -1000;
    ball = ball.next();
    CHECK(ball.hits_top(geometry) == true);
}
TEST_CASE("Ball::hits_bottom")
{
    Geometry geometry;
    Ball ball(paddle, geometry);
    CHECK(ball.hits_bottom(geometry) == false);
    ball.velocity_.height = 1000;
    ball = ball.next();
    CHECK(ball.hits_bottom(geometry) == true);
}
TEST_CASE("Ball::top_left")
{
    Geometry geometry;
    Ball ball(paddle, geometry);
    CHECK(ball.top_left().x == 145);
    CHECK(ball.top_left().y == 389);
}
TEST_CASE("Ball::above_block")
{
    Geometry geometry;
    Ball ball(paddle, geometry);
    CHECK( ball.center_.x == 150 );
    CHECK( ball.center_.y == 394 );
}
