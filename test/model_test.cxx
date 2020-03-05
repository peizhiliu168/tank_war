#include "model.hxx"
#include <catch.hxx>

TEST_CASE("play the game")
{
    Geometry geometry;
    Model m(geometry);
    CHECK( m.bricks_.size() == 100 );

    m.ball_.live_ = true;
    Ball old_ball = m.ball_;

    m.update(0);
    CHECK( m.ball_.center_ == old_ball.center_ + old_ball.velocity_ );

    m.update(0);
    CHECK( m.ball_.center_ == old_ball.center_ + 2 * old_ball.velocity_ );

    m.update(0);
    CHECK( m.ball_.center_ == old_ball.center_ + 3 * old_ball.velocity_ );
}
TEST_CASE("destroy one brick")
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
}
TEST_CASE("ball follow paddle"){
    Geometry geometry;
    Model m(geometry);
    m.bricks_.clear();
    m.ball_.live_ = false;
    m.ball_.radius_ = 3;
    m.ball_.center_ = {450, 546};
    m.ball_.velocity_ = {2, -20};
    m.paddle_to(245);
    CHECK( m.ball_.center_.x == 295);
    CHECK( m.ball_.center_.y == 546);
}
TEST_CASE("gsc update mock"){
    Geometry geometry;
    geometry.scene_dims = {800, 600};
    geometry.ball_velocity0 = {2,-20};
    Model m(geometry);
    m.bricks_.clear();
    m.paddle_to(0);
    m.ball_.live_ = true;
    m.ball_.center_ = {400, 589};
    m.ball_.velocity_ = {2, 19};
    m.ball_.radius_ = 3;
    m.update(12);
    CHECK( m.ball_.velocity_.height == -20);
    CHECK( m.ball_.center_.x == 50);
    //CHECK( m.ball_.center_.y == 546);
    CHECK( m.ball_.live_ == false);
}
TEST_CASE("update: hitting side and top at the same time"){
    Geometry geometry;
    Model m(geometry);
    m.ball_.center_ = {0, 0};
    m.ball_.live_ = true;
    m.update(1);
    CHECK( m.ball_.velocity_.width == -3);
    CHECK( m.ball_.velocity_.height == 10);
}
TEST_CASE("update: hit top"){
    Geometry geometry;
    Model m(geometry);
    m.ball_.center_ = {100, 0};
    m.ball_.live_ = true;
    m.update(1);
    CHECK( m.ball_.velocity_.width == 3);
    CHECK( m.ball_.velocity_.height == 10);
}
TEST_CASE("update: hit side"){
    Geometry geometry;
    Model m(geometry);
    m.ball_.center_ = {0, 100};
    m.ball_.live_ = true;
    m.update(1);
    CHECK( m.ball_.velocity_.width == -3);
    CHECK( m.ball_.velocity_.height == -10);
}
TEST_CASE("update: hit bottom"){
    Geometry geometry;
    Model m(geometry);
    m.ball_.center_ = {200, 800};
    m.ball_.live_ = true;
    m.update(1);
    CHECK( m.ball_.live_ == false);
}
TEST_CASE("update: destroy brick"){
    Geometry geometry;
    Model m(geometry);
    m.ball_.center_ = {geometry.side_margin-3, geometry.top_margin+10};
    m.ball_.live_ = true;
    m.update(1);
    CHECK( m.ball_.velocity_.width == -3);
    CHECK( m.ball_.velocity_.height == 10);
}
TEST_CASE("hits paddle")
{
    Geometry geometry;
    Model m(geometry);
    m.ball_.live_ = true;
    m.ball_.velocity_.height = 10;
    m.update(10);
    CHECK( m.ball_.velocity_.height == -10);
    CHECK( m.ball_.velocity_.width == 13);
}