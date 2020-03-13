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
        , blue_score_()
        , red_score_()
        , board_(geometry_.board_size.width, geometry_.board_size.height)
{
    move_base();
    ball_red_reset();
    ball_blue_reset();
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
void Model::update(Keys &keys)
{
    tank_update(keys);

    if (ball_red_.hits_ball(ball_blue_) && ball_red_.live_ && ball_blue_.live_){
        ball_red_.live_ = false;
        ball_blue_.live_ = false;
        ball_blue_reset();
        ball_red_reset();
    }
    Ball b1(ball_red_.next());
    if (ball_red_.live_){
        if (b1.hits_bottom(geometry_)||
            b1.hits_top(geometry_)||
            b1.hits_side(geometry_)||
            board_.destroy_wall(b1)){
            ball_red_.live_ = false;
            ball_red_reset();
            return;
        }
        if (b1.hits_block(tank_blue_) ||
            b1.hits_block(base_blue_)){
            game_reset();
            red_score_.plus_one();
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
            b2.hits_side(geometry_)||
            board_.destroy_wall(b2)){

            ball_blue_.live_ = false;
            ball_blue_reset();
            return;
        }
        if (b2.hits_block(tank_red_) ||
            b2.hits_block(base_red_)){

            game_reset();
            blue_score_.plus_one();
            return;
        }
        ball_blue_ = ball_blue_.next();
    } else{
        ball_blue_reset();
    }

    if (is_touching(base_red_, tank_blue_)){
        blue_score_.plus_one();
        game_reset();
    } else if (is_touching(base_blue_, tank_red_)){
        red_score_.plus_one();
        game_reset();
    }
}

void Model::move_base(){
    base_red_.x = get_random_square().x + geometry_.wall_thickness_;
    base_blue_.x = get_random_square().x + geometry_.wall_thickness_;
    tank_red_.x = base_red_.x + (base_red_.width - tank_red_.width) / 2;
    tank_blue_.x = base_blue_.x + (base_red_.width - tank_blue_.width) / 2;
}

ge211::Position Model::get_random_square(){
    int ind = std::rand() % (geometry_.board_size.width - 4);
    int ind_actual = (ind + 1) * geometry_.board_size.height;

    return board_.get_walls()[ind_actual].top_left();
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
        move_base();
        ball_red_reset();
        ball_blue_reset();
        board_.reset();
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

bool Model::is_touching(const ge211::Rectangle r1, const ge211::Rectangle r2) {
    ge211::Position rect1_tl = r1.top_left();
    ge211::Position rect1_br = r1.bottom_right();
    ge211::Position rect2_tl = r2.top_left();
    ge211::Position wall_br = r2.bottom_right();

    if (rect1_br.x <= rect2_tl.x || rect1_tl.x >= wall_br.x) {
        return false;
    }
    if (rect1_tl.y >= wall_br.y || rect1_br.y <= rect2_tl.y) {
        return false;
    }
    return true;
}

bool Model::tank_collision(ge211::Rectangle tank1, ge211::Rectangle tank2){
    ge211::Position tank1_tl = tank1.top_left();
    ge211::Position tank1_br = tank1.bottom_right();
    ge211::Position tank2_tl = tank2.top_left();
    ge211::Position tank2_br = tank2.bottom_right();

    if (tank1_br.x <= tank2_tl.x || tank1_tl.x >= tank2_br.x) {
        return false;
    }
    if (tank1_tl.y >= tank2_br.y || tank1_br.y <= tank2_tl.y) {
        return false;
    }

    return true;
}

void Model::tank_update(Keys &keys){
    if ( keys.a ){
        if (tank_red_orientation_ == 1) {
            tank_red_orientation_ = 4;
        }
        else{
            tank_red_orientation_ = tank_red_orientation_ - 1;
        }
        keys.a = false;
    }
    if ( keys.d ) {
        if (tank_red_orientation_ == 4) {
            tank_red_orientation_ = 1;
        }
        else{
            tank_red_orientation_ = tank_red_orientation_ + 1;
        }
        keys.d = false;
    }
    if ( keys.s ){
        if (tank_red_orientation_ == 1 &&
            tank_red_.y + geometry_.tank_dims_.height+3 < geometry_.scene_dims.height &&
            !board_.is_touching_wall(tank_red_, 3) &&
            !tank_collision(tank_red_, tank_blue_)){
            tank_red_.y += geometry_.tank_vel;
            if (board_.is_touching_wall(tank_red_, 3) ||
                tank_collision(tank_red_, tank_blue_))
                tank_red_.y -= geometry_.tank_vel;
        }

        if (tank_red_orientation_ == 3 &&
            tank_red_.y-3 > 0 &&
            !board_.is_touching_wall(tank_red_, 1) &&
            !tank_collision(tank_red_, tank_blue_)) {
            tank_red_.y -= geometry_.tank_vel;
            if (board_.is_touching_wall(tank_red_, 1) ||
                tank_collision(tank_red_, tank_blue_))
                tank_red_.y += geometry_.tank_vel;
        }
        if (tank_red_orientation_ == 2 &&
            tank_red_.x-3 > 0 &&
            !board_.is_touching_wall(tank_red_, 4) &&
            !tank_collision(tank_red_, tank_blue_)) {
            tank_red_.x -= geometry_.tank_vel;
            if (board_.is_touching_wall(tank_red_, 4) ||
                tank_collision(tank_red_, tank_blue_))
                tank_red_.x += geometry_.tank_vel;
        }
        if (tank_red_orientation_ == 4 &&
            tank_red_.x + geometry_.tank_dims_.width+3 < geometry_.scene_dims.width &&
            !board_.is_touching_wall(tank_red_, 2) &&
            !tank_collision(tank_red_, tank_blue_)) {
            tank_red_.x += geometry_.tank_vel;
            if (board_.is_touching_wall(tank_red_, 2) ||
                tank_collision(tank_red_, tank_blue_))
                tank_red_.x -= geometry_.tank_vel;
        }
    }

    if ( keys.w ){
        if (tank_red_orientation_ == 1 &&
            !board_.is_touching_wall(tank_red_, 1) &&
            tank_red_.y-3 > 0 &&
            !tank_collision(tank_red_, tank_blue_)) {
            tank_red_.y -= geometry_.tank_vel;
            if (board_.is_touching_wall(tank_red_, 1) ||
                tank_collision(tank_red_, tank_blue_))
                tank_red_.y += geometry_.tank_vel;
        }
        if (tank_red_orientation_ == 3 &&
            tank_red_.y + geometry_.tank_dims_.height+3 < geometry_.scene_dims.height &&
            !board_.is_touching_wall(tank_red_, 3) &&
            !tank_collision(tank_red_, tank_blue_)) {
            tank_red_.y += geometry_.tank_vel;
            if (board_.is_touching_wall(tank_red_, 3) ||
                tank_collision(tank_red_, tank_blue_))
                tank_red_.y -= geometry_.tank_vel;
        }
        if (tank_red_orientation_ == 2 &&
            tank_red_.x + geometry_.tank_dims_.width+3 < geometry_.scene_dims.width &&
            !board_.is_touching_wall(tank_red_, 2) &&
            !tank_collision(tank_red_, tank_blue_)) {
            tank_red_.x += geometry_.tank_vel;
            if (board_.is_touching_wall(tank_red_, 2) ||
                tank_collision(tank_red_, tank_blue_))
                tank_red_.x -= geometry_.tank_vel;
        }
        if (tank_red_orientation_ == 4 &&
            tank_red_.x-3 > 0 &&
            !board_.is_touching_wall(tank_red_, 4) &&
            !tank_collision(tank_red_, tank_blue_)) {
            tank_red_.x -= geometry_.tank_vel;
            if (board_.is_touching_wall(tank_red_, 4) ||
                tank_collision(tank_red_, tank_blue_))
                tank_red_.x += geometry_.tank_vel;
        }
    }



    ///tank blue operations
    if ( keys.left ) {
        if (tank_blue_orientation_ == 1) {
            tank_blue_orientation_ = 4;
        }
        else{
            tank_blue_orientation_ -= 1;
        }
        keys.left = false;
    }
    if ( keys.right ) {
        if (tank_blue_orientation_ == 4) {
            tank_blue_orientation_ = 1;
        }
        else{
            tank_blue_orientation_ += 1;
        }
        keys.right = false;
    }

    if ( keys.up ){
        if (tank_blue_orientation_ == 1 &&
            !board_.is_touching_wall(tank_blue_, 1) &&
            tank_blue_.y-3 > 0 &&
            !tank_collision(tank_red_, tank_blue_)) {
            tank_blue_.y -= geometry_.tank_vel;
            if (board_.is_touching_wall(tank_blue_, 1) ||
                tank_collision(tank_red_, tank_blue_))
                tank_blue_.y += geometry_.tank_vel;
        }
        if (tank_blue_orientation_ == 3 &&
            tank_blue_.y + geometry_.tank_dims_.height+3 < geometry_.scene_dims.height &&
            !board_.is_touching_wall(tank_blue_, 3) &&
            !tank_collision(tank_red_, tank_blue_)) {
            tank_blue_.y += geometry_.tank_vel;
            if (board_.is_touching_wall(tank_blue_, 3) ||
                tank_collision(tank_red_, tank_blue_))
                tank_blue_.y -= geometry_.tank_vel;
        }
        if (tank_blue_orientation_ == 2 &&
            tank_blue_.x + geometry_.tank_dims_.width+3 < geometry_.scene_dims.width &&
            !board_.is_touching_wall(tank_blue_, 2) &&
            !tank_collision(tank_red_, tank_blue_)) {
            tank_blue_.x += geometry_.tank_vel;
            if (board_.is_touching_wall(tank_blue_, 2) ||
                tank_collision(tank_red_, tank_blue_))
                tank_blue_.x -= geometry_.tank_vel;
        }
        if (tank_blue_orientation_ == 4 &&
            tank_blue_.x-3 > 0 &&
            !board_.is_touching_wall(tank_blue_, 4) &&
            !tank_collision(tank_red_, tank_blue_)) {
            tank_blue_.x -= geometry_.tank_vel;
            if (board_.is_touching_wall(tank_blue_, 4) ||
                tank_collision(tank_red_, tank_blue_))
                tank_blue_.x += geometry_.tank_vel;
        }
    }

    if ( keys.down ){
        if (tank_blue_orientation_ == 1 &&
            tank_blue_.y + geometry_.tank_dims_.height+3 < geometry_.scene_dims.height &&
            !board_.is_touching_wall(tank_blue_, 3) &&
            !tank_collision(tank_red_, tank_blue_)) {
            tank_blue_.y += geometry_.tank_vel;
            if (board_.is_touching_wall(tank_blue_, 3) ||
                tank_collision(tank_red_, tank_blue_))
                tank_blue_.y -= geometry_.tank_vel;
        }
        if (tank_blue_orientation_ == 3 &&
            tank_blue_.y-3 > 0 &&
            !board_.is_touching_wall(tank_blue_, 1) &&
            !tank_collision(tank_red_, tank_blue_)) {
            tank_blue_.y -= geometry_.tank_vel;
            if (board_.is_touching_wall(tank_blue_, 1) ||
                tank_collision(tank_red_, tank_blue_))
                tank_blue_.y += geometry_.tank_vel;
        }
        if (tank_blue_orientation_ == 2 &&
            tank_blue_.x-3 > 0 &&
            !board_.is_touching_wall(tank_blue_, 4) &&
            !tank_collision(tank_red_, tank_blue_)) {
            tank_blue_.x -= geometry_.tank_vel;
            if (board_.is_touching_wall(tank_blue_, 4) ||
                tank_collision(tank_red_, tank_blue_))
                tank_blue_.x += geometry_.tank_vel;
        }
        if (tank_blue_orientation_ == 4 &&
            tank_blue_.x + geometry_.tank_dims_.width+3 < geometry_.scene_dims.width &&
            !board_.is_touching_wall(tank_blue_, 2) &&
            !tank_collision(tank_red_, tank_blue_)) {
            tank_blue_.x += geometry_.tank_vel;
            if (board_.is_touching_wall(tank_blue_, 2) ||
                tank_collision(tank_red_, tank_blue_))
                tank_blue_.x -= geometry_.tank_vel;
        }
    }
}

bool Model::is_game_over(){
    return (blue_score_.get_score() + red_score_.get_score())
            == geometry_.max_rounds;
}

int Model::get_winner(){
    if (blue_score_.get_score() > red_score_.get_score()){
        return 1;
    } else if (blue_score_.get_score() < red_score_.get_score()){
        return 2;
    }
    return 0;
}


