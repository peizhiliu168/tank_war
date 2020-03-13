#include "model.hxx"
#include <catch.hxx>

TEST_CASE("both tanks move")
{
    Geometry geometry{};
    Model model {geometry};
    Keys keys{};

    int init_b_x = model.tank_blue_.x;
    int init_b_y = model.tank_blue_.y;
    int init_r_x = model.tank_red_.x;
    int init_r_y = model.tank_red_.y;

    // testing red tank
    keys.w = true;
    model.update(keys);

    CHECK(model.tank_red_.x == init_r_x);
    CHECK(model.tank_red_.y == init_r_y - geometry.tank_vel);

    keys.d = true;
    model.update(keys);

    CHECK(model.tank_red_.x == init_r_x + geometry.tank_vel);
    CHECK(model.tank_red_.y == init_r_y - geometry.tank_vel);

    keys.d = false;
    keys.a = true;
    model.update(keys);

    CHECK(model.tank_red_.x == init_r_x + geometry.tank_vel);
    CHECK(model.tank_red_.y == init_r_y - 2 * geometry.tank_vel);

    keys.d = false;
    keys.a = false;
    keys.w = false;
    keys.s = true;
    model.update(keys);

    CHECK(model.tank_red_.x == init_r_x + geometry.tank_vel);
    CHECK(model.tank_red_.y == init_r_y - geometry.tank_vel);



    // testing blue tank
    keys.up = true;
    model.update(keys);

    CHECK(model.tank_blue_.x == init_b_x);
    CHECK(model.tank_blue_.y == init_b_y + geometry.tank_vel);

    keys.right = true;
    model.update(keys);

    CHECK(model.tank_blue_.x == init_b_x - geometry.tank_vel);
    CHECK(model.tank_blue_.y == init_b_y + geometry.tank_vel);

    keys.right = false;
    keys.left = true;
    model.update(keys);

    CHECK(model.tank_blue_.x == init_b_x - geometry.tank_vel);
    CHECK(model.tank_blue_.y == init_b_y + 2 * geometry.tank_vel);

    keys.right = false;
    keys.left = false;
    keys.up = false;
    keys.down = true;
    model.update(keys);

    CHECK(model.tank_blue_.x == init_b_x - geometry.tank_vel);
    CHECK(model.tank_blue_.y == init_b_y + geometry.tank_vel);
}

TEST_CASE("both tanks move at same time") {
    Geometry geometry{};
    Model model{geometry};
    Keys keys{};

    int init_b_x = model.tank_blue_.x;
    int init_b_y = model.tank_blue_.y;
    int init_r_x = model.tank_red_.x;
    int init_r_y = model.tank_red_.y;

    keys.w = true;
    keys.up = true;
    model.update(keys);

    CHECK(model.tank_blue_.x == init_b_x);
    CHECK(model.tank_blue_.y == init_b_y + geometry.tank_vel);
    CHECK(model.tank_red_.x == init_r_x);
    CHECK(model.tank_red_.y == init_r_y - geometry.tank_vel);

    keys.d = true;
    keys.right = true;
    model.update(keys);

    CHECK(model.tank_blue_.x == init_b_x - geometry.tank_vel);
    CHECK(model.tank_blue_.y == init_b_y + geometry.tank_vel);
    CHECK(model.tank_red_.x == init_r_x + geometry.tank_vel);
    CHECK(model.tank_red_.y == init_r_y - geometry.tank_vel);

    keys.d = false;
    keys.a = true;
    keys.right = false;
    keys.left = true;
    model.update(keys);

    CHECK(model.tank_blue_.x == init_b_x - geometry.tank_vel);
    CHECK(model.tank_blue_.y == init_b_y + 2 * geometry.tank_vel);
    CHECK(model.tank_red_.x == init_r_x + geometry.tank_vel);
    CHECK(model.tank_red_.y == init_r_y - 2 * geometry.tank_vel);

    keys.d = false;
    keys.a = false;
    keys.w = false;
    keys.s = true;
    keys.right = false;
    keys.left = false;
    keys.up = false;
    keys.down = true;
    model.update(keys);

    CHECK(model.tank_blue_.x == init_b_x - geometry.tank_vel);
    CHECK(model.tank_blue_.y == init_b_y + geometry.tank_vel);
    CHECK(model.tank_red_.x == init_r_x + geometry.tank_vel);
    CHECK(model.tank_red_.y == init_r_y - geometry.tank_vel);
}

TEST_CASE("cannonballs follow tank")
{
    Geometry geometry{};
    Model model{geometry};
    Keys keys{};

    int red_cannon_ball_x = model.ball_red_.top_left().x;
    int red_cannon_ball_y = model.ball_red_.top_left().y;
    int blue_cannon_ball_x = model.ball_blue_.top_left().x;
    int blue_cannon_ball_y = model.ball_blue_.top_left().y;

    keys.w = true;
    model.update(keys);

    CHECK(model.ball_red_.top_left().x == red_cannon_ball_x);
    CHECK(model.ball_red_.top_left().y == red_cannon_ball_y - geometry.tank_vel);

    keys.w = false;
    keys.s = true;
    model.update(keys);

    CHECK(model.ball_red_.top_left().x == red_cannon_ball_x);
    CHECK(model.ball_red_.top_left().y == red_cannon_ball_y);

    keys.up = true;
    model.update(keys);

    CHECK(model.ball_blue_.top_left().x == blue_cannon_ball_x);
    CHECK(model.ball_blue_.top_left().y == blue_cannon_ball_y + geometry.tank_vel);

    keys.up = false;
    keys.down = true;
    model.update(keys);

    CHECK(model.ball_blue_.top_left().x == blue_cannon_ball_x);
    CHECK(model.ball_blue_.top_left().y == blue_cannon_ball_y);
}

TEST_CASE("fire cannon ball")
{
    Geometry geometry{};
    Model model{geometry};
    Keys keys{};

    int red_cannon_ball_x = model.ball_red_.top_left().x;
    int red_cannon_ball_y = model.ball_red_.top_left().y;
    int blue_cannon_ball_x = model.ball_blue_.top_left().x;
    int blue_cannon_ball_y = model.ball_blue_.top_left().y;

    model.launch_blue();
    model.launch_red();
    model.update(keys);
    CHECK(model.ball_red_.top_left().x  == red_cannon_ball_x);
    CHECK(model.ball_red_.top_left().y == red_cannon_ball_y
                                          + model.ball_red_.velocity_.height);
    CHECK(model.ball_blue_.top_left().x  == blue_cannon_ball_x);
    CHECK(model.ball_blue_.top_left().y == blue_cannon_ball_y
                                           + model.ball_blue_.velocity_.height);

}

TEST_CASE("rotate before firing cannon ball")
{
    Geometry geometry{};
    Model model{geometry};
    Keys keys{};

    keys.d = true;
    keys.right = true;
    model.update(keys);

    int red_cannon_ball_x = model.ball_red_.top_left().x;
    int red_cannon_ball_y = model.ball_red_.top_left().y;
    int blue_cannon_ball_x = model.ball_blue_.top_left().x;
    int blue_cannon_ball_y = model.ball_blue_.top_left().y;

    model.launch_blue();
    model.launch_red();
    model.update(keys);
    CHECK(model.ball_red_.top_left().x  == red_cannon_ball_x
                                           + model.ball_red_.velocity_.width);
    CHECK(model.ball_red_.top_left().y == red_cannon_ball_y);
    CHECK(model.ball_blue_.top_left().x  == blue_cannon_ball_x
                                            + model.ball_blue_.velocity_.width);
    CHECK(model.ball_blue_.top_left().y == blue_cannon_ball_y);
}

TEST_CASE("red cannon hits blue tank")
{
    Geometry geometry{};
    Model model{geometry};
    Keys keys{};

    ge211::Position ball_init = model.ball_red_.top_left();
    model.launch_red();

    model.tank_blue_.x = 100;
    model.tank_blue_.y = 100;

    model.ball_red_.velocity_ = ge211::Dimensions {4, 0};
    model.ball_red_.center_ = ge211::Position {96, 100};

    model.update(keys);
    CHECK(model.ball_red_.live_ == false);
    CHECK(model.red_score_.get_score() == 1);
    CHECK(model.blue_score_.get_score() == 0);
}

TEST_CASE("blue cannon hits red tank")
{
    Geometry geometry{};
    Model model{geometry};
    Keys keys{};

    model.launch_blue();

    model.tank_red_.x = 100;
    model.tank_red_.y = 100;

    model.ball_blue_.velocity_ = ge211::Dimensions {4, 0};
    model.ball_blue_.center_ = ge211::Position {96, 100};

    model.update(keys);
    CHECK(model.ball_blue_.live_ == false);
    CHECK(model.blue_score_.get_score() == 1);
    CHECK(model.red_score_.get_score() == 0);
}

TEST_CASE("both hit tanks")
{
    Geometry geometry{};
    Model model{geometry};
    Keys keys{};

    model.launch_blue();
    model.launch_red();

    model.tank_red_.x = 100;
    model.tank_red_.y = 100;
    model.tank_blue_.x = 100;
    model.tank_blue_.y = 100;

    model.ball_blue_.velocity_ = ge211::Dimensions {4, 0};
    model.ball_blue_.center_ = ge211::Position {96, 100};

    model.ball_red_.velocity_ = ge211::Dimensions {-4, 0};
    model.ball_red_.center_ = ge211::Position {104, 100};

    model.update(keys);
    CHECK(model.ball_blue_.live_ == false);
    CHECK(model.ball_red_.live_ == false);
    CHECK(model.red_score_.get_score() == 1);
    CHECK(model.blue_score_.get_score() == 0);
}

TEST_CASE("cannon ball hits edge of screen"){
    Geometry geometry{};
    Model model{geometry};
    Keys keys{};

    ge211::Position blue_init = model.ball_blue_.top_left();
    ge211::Position red_init = model.ball_red_.top_left();

    model.launch_blue();
    model.ball_blue_.velocity_ = ge211::Dimensions {4, 0};
    model.ball_blue_.center_ = ge211::Position
            {geometry.scene_dims.width - 4, 100};
    model.update(keys);
    CHECK(blue_init == model.ball_blue_.top_left());
    CHECK(model.ball_blue_.live_ == false);

    model.launch_blue();
    model.ball_blue_.velocity_ = ge211::Dimensions {-4, 0};
    model.ball_blue_.center_ = ge211::Position
            {4, 100};
    model.update(keys);
    CHECK(blue_init == model.ball_blue_.top_left());
    CHECK(model.ball_blue_.live_ == false);

    model.launch_blue();
    model.ball_blue_.velocity_ = ge211::Dimensions {0, 4};
    model.ball_blue_.center_ = ge211::Position
            {100, geometry.scene_dims.height - 4};
    model.update(keys);
    CHECK(blue_init == model.ball_blue_.top_left());
    CHECK(model.ball_blue_.live_ == false);

    model.launch_blue();
    model.ball_blue_.velocity_ = ge211::Dimensions {0, -4};
    model.ball_blue_.center_ = ge211::Position
            {100, 4};
    model.update(keys);
    CHECK(blue_init == model.ball_blue_.top_left());
    CHECK(model.ball_blue_.live_ == false);

    model.launch_red();
    model.ball_red_.velocity_ = ge211::Dimensions {4, 0};
    model.ball_red_.center_ = ge211::Position
            {geometry.scene_dims.width - 4, 100};
    model.update(keys);
    CHECK(red_init == model.ball_red_.top_left());
    CHECK(model.ball_red_.live_ == false);

    model.launch_red();
    model.ball_red_.velocity_ = ge211::Dimensions {-4, 0};
    model.ball_red_.center_ = ge211::Position
            {4, 100};
    model.update(keys);
    CHECK(red_init == model.ball_red_.top_left());
    CHECK(model.ball_red_.live_ == false);

    model.launch_red();
    model.ball_red_.velocity_ = ge211::Dimensions {0, 4};
    model.ball_red_.center_ = ge211::Position
            {100, geometry.scene_dims.height - 4};
    model.update(keys);
    CHECK(red_init == model.ball_red_.top_left());
    CHECK(model.ball_red_.live_ == false);

    model.launch_red();
    model.ball_red_.velocity_ = ge211::Dimensions {0, -4};
    model.ball_red_.center_ = ge211::Position
            {100, 4};
    model.update(keys);
    CHECK(red_init == model.ball_red_.top_left());
    CHECK(model.ball_red_.live_ == false);
}

TEST_CASE("cannon ball hits base")
{
    Geometry geometry{};
    Model model{geometry};
    Keys keys{};

    model.launch_blue();

    model.ball_blue_.velocity_ = ge211::Dimensions {-4, 0};
    model.ball_blue_.center_ = ge211::Position
            {model.base_red_.x + model.base_red_.width + 4, model.base_red_.y};

    model.update(keys);
    CHECK(model.ball_blue_.live_ == false);
    CHECK(model.blue_score_.get_score() == 1);
    CHECK(model.red_score_.get_score() == 0);

    model.launch_red();

    model.ball_red_.velocity_ = ge211::Dimensions {-4, 0};
    model.ball_red_.center_ = ge211::Position
            {model.base_blue_.x + model.base_blue_.width + 4,
             model.base_blue_.y + model.base_blue_.height};

    model.update(keys);
    CHECK(model.ball_red_.live_ == false);
    CHECK(model.blue_score_.get_score() == 1);
    CHECK(model.red_score_.get_score() == 1);
}

TEST_CASE("cannon ball hits wall")
{
    Geometry geometry{};
    Model model{geometry};
    Keys keys{};

    ge211::Position blue_init = model.ball_blue_.top_left();
    ge211::Position red_init = model.ball_red_.top_left();

    std::vector<ge211::Rectangle> walls = model.board_.get_walls();
    int wall_init = walls.size();

    ge211::Rectangle wall = walls[0];
    model.launch_red();
    model.ball_red_.velocity_ = ge211::Dimensions {0, 0};
    model.ball_red_.center_ = ge211::Position {wall.x + model.ball_red_.radius_,
                                               wall.y + model.ball_red_.radius_};
    model.update(keys);
    CHECK(model.ball_red_.live_ == false);
    CHECK(model.ball_red_.top_left() == red_init);
    CHECK(model.board_.get_walls()[0] != walls[0]);
    CHECK(model.board_.get_walls().size() == wall_init - 1);


    walls = model.board_.get_walls();
    wall_init = walls.size();
    wall = walls[0];

    model.launch_blue();
    model.ball_blue_.velocity_ = ge211::Dimensions {0, 0};
    model.ball_blue_.center_ = ge211::Position {wall.x + model.ball_blue_.radius_,
                                               wall.y + model.ball_blue_.radius_};
    model.update(keys);
    CHECK(model.ball_blue_.live_ == false);
    CHECK(model.ball_blue_.top_left() == blue_init);
    CHECK(model.board_.get_walls()[0] != walls[0]);
    CHECK(model.board_.get_walls().size() == wall_init - 1);


}

TEST_CASE("cannon ball hits another cannon ball")
{
    Geometry geometry{};
    Model model{geometry};
    Keys keys{};

    model.ball_blue_.center_ = {10, 10};
    model.ball_red_.center_ = {10, 10};

    model.update(keys);
    CHECK(model.ball_red_.live_ == false);
    CHECK(model.ball_blue_.live_ == false);
    CHECK(model.red_score_.get_score() == 0);
    CHECK(model.blue_score_.get_score() == 0);
}

TEST_CASE("tank hits base")
{
    Geometry geometry{};
    Model model{geometry};
    Keys keys{};

    model.tank_red_.x = model.base_blue_.x;
    model.tank_red_.y = model.base_blue_.y;
    model.tank_blue_.top_left() = {200, 200};
    model.update(keys);
    CHECK(model.red_score_.get_score() == 1);
    CHECK(model.blue_score_.get_score() == 0);
}

TEST_CASE("tank hits wall with ball attached")
{
    Geometry geometry{};
    Model model{geometry};
    Keys keys{};


    std::vector<ge211::Rectangle> walls = model.board_.get_walls();
    ge211::Rectangle wall = walls[0];
    model.tank_red_.x = wall.x;
    model.tank_red_.y = wall.y;

    model.update(keys);
    CHECK(model.ball_red_.live_ == false);
    CHECK(model.tank_red_.x == wall.x);
    CHECK(model.tank_red_.y == wall.y);
}

TEST_CASE("tank hits tank with both cannon balls attached")
{
    Geometry geometry{};
    Model model{geometry};
    Keys keys{};

    model.tank_red_.top_left() = {100, 100};
    model.tank_blue_.top_left() = {100, 100};

    model.update(keys);
    CHECK(model.red_score_.get_score() == 0);
    CHECK(model.blue_score_.get_score() == 0);
    CHECK(model.tank_red_.x == model.base_red_.x + (model.base_red_.width - model.tank_red_.width) / 2);
    CHECK(model.tank_blue_.x == model.base_blue_.x + (model.base_blue_.width - model.tank_blue_.width) / 2);
}

TEST_CASE("tank hits edge of screen")
{
    Geometry geometry{};
    Model model{geometry};
    Keys keys{};

    model.tank_red_.x = 0;
    model.tank_red_.y = 0;
    keys.w = true;

    model.update(keys);
    CHECK(model.tank_red_.x == 0);
    CHECK(model.tank_red_.y == 0);
}

TEST_CASE("game ends after 11 rounds")
{
    Geometry geometry{};
    Model model{geometry};
    for (int i = 0; i < 11; i++){
        model.red_score_.plus_one();
    }
    CHECK(model.get_winner() == 2);
}