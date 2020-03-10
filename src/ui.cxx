#include "ui.hxx"

///
/// VIEW CONSTANTS
///

ge211::Color const ball_red_color    {255, 51, 51};
ge211::Color const ball_blue_color    {51, 255, 255};
ge211::Color const tank_color  {0, 255, 0};
ge211::Color const brick_color   {100, 100, 100};
ge211::Color const base_color   {255, 255, 255};

///
/// VIEW FUNCTIONS
///

Ui::Ui(Model& model)
        : model_(model)
        , w(false)
        , a(false)
        , s(false)
        , d(false)
        , up(false)
        , down(false)
        , left(false)
        , right(false)
        , j(false)
        , p(false)

{ }

ge211::Dimensions Ui::initial_window_dimensions() const
{
    return model_.geometry_.scene_dims;
}

void Ui::draw(ge211::Sprite_set& sprites)
{
    // TODO: your code here
    sprites.add_sprite(base_sprite_, model_.base_red_.top_left(), 0);
    sprites.add_sprite(base_sprite_, model_.base_blue_.top_left(), 0);

    sprites.add_sprite(tank_sprite_, model_.tank_red_.top_left(), 1);
    sprites.add_sprite(tank_sprite_, model_.tank_blue_.top_left(), 1);

    sprites.add_sprite(ball_red_sprite_, model_.ball_red_.top_left(), 2);
    sprites.add_sprite(ball_blue_sprite_, model_.ball_blue_.top_left(), 2);

    std::vector<ge211::Rectangle> walls = model_.board_.get_walls();
    for (int i = 0; i < walls.size(); i++){
        if (walls[i].dimensions().height == model_.geometry_.wall_thickness_){
            sprites.add_sprite(h_wall_, walls[i].top_left(),0);
        } else{
            sprites.add_sprite(v_wall_, walls[i].top_left(),0);
        }
    }

    // creates score_board
    sprites.add_sprite(first_score_board, model_.geometry_.first_board_pos);
    sprites.add_sprite(second_score_board, model_.geometry_.second_board_pos);
}

///
/// CONTROLLER FUNCTIONS
///
void Ui::on_key_down(ge211::Key key) {
    if (key == ge211::Key::code('w'))
        w = true;
    if (key == ge211::Key::code('a'))
        a = true;
    if (key == ge211::Key::code('s'))
        s = true;
    if (key == ge211::Key::code('d'))
        d = true;
    if (key == ge211::Key::up())
        up = true;
    if (key == ge211::Key::down())
        down = true;
    if (key == ge211::Key::left())
        left = true;
    if (key == ge211::Key::right())
        right = true;
    if (key == ge211::Key::code('j'))
        j = true;
    if (key == ge211::Key::code('p'))
        p = true;
}
void Ui::on_key_up(ge211::Key key) {
    if (key == ge211::Key::code('w'))
        w = false;
    if (key == ge211::Key::code('a'))
        a = false;
    if (key == ge211::Key::code('s'))
        s = false;
    if (key == ge211::Key::code('d'))
        d = false;
    if (key == ge211::Key::up())
        up = false;
    if (key == ge211::Key::down())
        down = false;
    if (key == ge211::Key::left())
        left = false;
    if (key == ge211::Key::right())
        right = false;
    if (key == ge211::Key::code('j'))
        j = false;
    if (key == ge211::Key::code('p'))
        p = false;
}
void Ui::on_key(ge211::Key key)
{

    if (key == ge211::Key::code('q'))
        quit();

    ///cannon ball operations
    if ( j || key == ge211::Key::code('j')){
        model_.launch_red();
    }
    if ( p || key == ge211::Key::code('p')){
        model_.launch_blue();
    }

    ///tank red operations
    if ( a ){
        if (model_.tank_red_orientation_ == 1) {
            model_.tank_red_orientation_ = 4;
        }
        else{
            model_.tank_red_orientation_ = model_.tank_red_orientation_ - 1;
        }
        a = false;
    }
    if ( s || key == ge211::Key::code('s')){
        if (model_.tank_red_orientation_ == 1 &&
            model_.tank_red_.y+tank_sprite_.dimensions().height+3 < model_.geometry_.scene_dims.height &&
            !model_.board_.is_touching_wall(model_.tank_red_, 3) &&
            !tank_collision(model_.tank_red_, model_.tank_blue_)){
            model_.tank_red_.y += 3;
            if (model_.board_.is_touching_wall(model_.tank_red_, 3) ||
                tank_collision(model_.tank_red_, model_.tank_blue_))
                model_.tank_red_.y -= 3;
        }

        if (model_.tank_red_orientation_ == 3 &&
            model_.tank_red_.y-3 > 0 &&
            !model_.board_.is_touching_wall(model_.tank_red_, 1) &&
            !tank_collision(model_.tank_red_, model_.tank_blue_)) {
            model_.tank_red_.y -= 3;
            if (model_.board_.is_touching_wall(model_.tank_red_, 1) ||
                tank_collision(model_.tank_red_, model_.tank_blue_))
                model_.tank_red_.y += 3;
        }
        if (model_.tank_red_orientation_ == 2 &&
            model_.tank_red_.x-3 > 0 &&
            !model_.board_.is_touching_wall(model_.tank_red_, 4) &&
            !tank_collision(model_.tank_red_, model_.tank_blue_)) {
            model_.tank_red_.x -= 3;
            if (model_.board_.is_touching_wall(model_.tank_red_, 4) ||
                tank_collision(model_.tank_red_, model_.tank_blue_))
                model_.tank_red_.x += 3;
        }
        if (model_.tank_red_orientation_ == 4 &&
            model_.tank_red_.x+tank_sprite_.dimensions().width+3 < model_.geometry_.scene_dims.width &&
            !model_.board_.is_touching_wall(model_.tank_red_, 2) &&
            !tank_collision(model_.tank_red_, model_.tank_blue_)) {
            model_.tank_red_.x += 3;
            if (model_.board_.is_touching_wall(model_.tank_red_, 2) ||
                tank_collision(model_.tank_red_, model_.tank_blue_))
                model_.tank_red_.x -= 3;
        }
    }

    if ( w || key == ge211::Key::code('w')){
        if (model_.tank_red_orientation_ == 1 &&
            !model_.board_.is_touching_wall(model_.tank_red_, 1) &&
            model_.tank_red_.y-3 > 0 &&
            !tank_collision(model_.tank_red_, model_.tank_blue_)) {
            model_.tank_red_.y -= 3;
            if (model_.board_.is_touching_wall(model_.tank_red_, 1) ||
                tank_collision(model_.tank_red_, model_.tank_blue_))
                model_.tank_red_.y += 3;
        }
        if (model_.tank_red_orientation_ == 3 &&
            model_.tank_red_.y+tank_sprite_.dimensions().height+3 < model_.geometry_.scene_dims.height &&
            !model_.board_.is_touching_wall(model_.tank_red_, 3) &&
            !tank_collision(model_.tank_red_, model_.tank_blue_)) {
            model_.tank_red_.y += 3;
            if (model_.board_.is_touching_wall(model_.tank_red_, 3) ||
                tank_collision(model_.tank_red_, model_.tank_blue_))
                model_.tank_red_.y -= 3;
        }
        if (model_.tank_red_orientation_ == 2 &&
            model_.tank_red_.x+tank_sprite_.dimensions().width+3 < model_.geometry_.scene_dims.width &&
            !model_.board_.is_touching_wall(model_.tank_red_, 2) &&
            !tank_collision(model_.tank_red_, model_.tank_blue_)) {
            model_.tank_red_.x += 3;
            if (model_.board_.is_touching_wall(model_.tank_red_, 2) ||
                tank_collision(model_.tank_red_, model_.tank_blue_))
                model_.tank_red_.x -= 3;
        }
        if (model_.tank_red_orientation_ == 4 &&
            model_.tank_red_.x-3 > 0 &&
            !model_.board_.is_touching_wall(model_.tank_red_, 4) &&
            !tank_collision(model_.tank_red_, model_.tank_blue_)) {
            model_.tank_red_.x -= 3;
            if (model_.board_.is_touching_wall(model_.tank_red_, 4) ||
                tank_collision(model_.tank_red_, model_.tank_blue_))
                model_.tank_red_.x += 3;
        }
    }
    if ( d ) {
        if (model_.tank_red_orientation_ == 4) {
            model_.tank_red_orientation_ = 1;
        }
        else{
            model_.tank_red_orientation_ = model_.tank_red_orientation_ + 1;
        }
        d = false;
    }

    ///tank blue operations
    if ( up || key == ge211::Key::up()){
        if (model_.tank_blue_orientation_ == 1 &&
            !model_.board_.is_touching_wall(model_.tank_blue_, 1) &&
            model_.tank_blue_.y-3 > 0 &&
            !tank_collision(model_.tank_red_, model_.tank_blue_)) {
            model_.tank_blue_.y -= 3;
            if (model_.board_.is_touching_wall(model_.tank_blue_, 1) ||
                tank_collision(model_.tank_red_, model_.tank_blue_))
                model_.tank_blue_.y += 3;
        }
        if (model_.tank_blue_orientation_ == 3 &&
            model_.tank_blue_.y+tank_sprite_.dimensions().height+3 < model_.geometry_.scene_dims.height &&
            !model_.board_.is_touching_wall(model_.tank_blue_, 3) &&
            !tank_collision(model_.tank_red_, model_.tank_blue_)) {
            model_.tank_blue_.y += 3;
            if (model_.board_.is_touching_wall(model_.tank_blue_, 3) ||
                tank_collision(model_.tank_red_, model_.tank_blue_))
                model_.tank_blue_.y -= 3;
        }
        if (model_.tank_blue_orientation_ == 2 &&
            model_.tank_blue_.x+tank_sprite_.dimensions().width+3 < model_.geometry_.scene_dims.width &&
            !model_.board_.is_touching_wall(model_.tank_blue_, 2) &&
            !tank_collision(model_.tank_red_, model_.tank_blue_)) {
            model_.tank_blue_.x += 3;
            if (model_.board_.is_touching_wall(model_.tank_blue_, 2) ||
                tank_collision(model_.tank_red_, model_.tank_blue_))
                model_.tank_blue_.x -= 3;
        }
        if (model_.tank_blue_orientation_ == 4 &&
            model_.tank_blue_.x-3 > 0 &&
            !model_.board_.is_touching_wall(model_.tank_blue_, 4) &&
            !tank_collision(model_.tank_red_, model_.tank_blue_)) {
            model_.tank_blue_.x -= 3;
            if (model_.board_.is_touching_wall(model_.tank_blue_, 4) ||
                tank_collision(model_.tank_red_, model_.tank_blue_))
                model_.tank_blue_.x += 3;
        }
    }

    if ( down || key == ge211::Key::down()){
        if (model_.tank_blue_orientation_ == 1 &&
            model_.tank_blue_.y+tank_sprite_.dimensions().height+3 < model_.geometry_.scene_dims.height &&
            !model_.board_.is_touching_wall(model_.tank_blue_, 3) &&
            !tank_collision(model_.tank_red_, model_.tank_blue_)) {
            model_.tank_blue_.y += 3;
            if (model_.board_.is_touching_wall(model_.tank_blue_, 3) ||
                tank_collision(model_.tank_red_, model_.tank_blue_))
                model_.tank_blue_.y -= 3;
        }
        if (model_.tank_blue_orientation_ == 3 &&
            model_.tank_blue_.y-3 > 0 &&
            !model_.board_.is_touching_wall(model_.tank_blue_, 1) &&
            !tank_collision(model_.tank_red_, model_.tank_blue_)) {
            model_.tank_blue_.y -= 3;
            if (model_.board_.is_touching_wall(model_.tank_blue_, 1) ||
                tank_collision(model_.tank_red_, model_.tank_blue_))
                model_.tank_blue_.y += 3;
        }
        if (model_.tank_blue_orientation_ == 2 &&
            model_.tank_blue_.x-3 > 0 &&
            !model_.board_.is_touching_wall(model_.tank_blue_, 4) &&
            !tank_collision(model_.tank_red_, model_.tank_blue_)) {
            model_.tank_blue_.x -= 3;
            if (model_.board_.is_touching_wall(model_.tank_blue_, 4) ||
                tank_collision(model_.tank_red_, model_.tank_blue_))
                model_.tank_blue_.x += 3;
        }
        if (model_.tank_blue_orientation_ == 4 &&
            model_.tank_blue_.x+tank_sprite_.dimensions().width+3 < model_.geometry_.scene_dims.width &&
            !model_.board_.is_touching_wall(model_.tank_blue_, 2) &&
            !tank_collision(model_.tank_red_, model_.tank_blue_)) {
            model_.tank_blue_.x += 3;
            if (model_.board_.is_touching_wall(model_.tank_blue_, 2) ||
                tank_collision(model_.tank_red_, model_.tank_blue_))
                model_.tank_blue_.x -= 3;
        }
    }

    if ( left ) {
        if (model_.tank_blue_orientation_ == 1) {
            model_.tank_blue_orientation_ = 4;
        }
        else{
            model_.tank_blue_orientation_ -= 1;
        }
        left = false;
    }

    if ( right ) {
        if (model_.tank_blue_orientation_ == 4) {
            model_.tank_blue_orientation_ = 1;
        }
        else{
            model_.tank_blue_orientation_ += 1;
        }
        right = false;
    }
}

void Ui::on_frame(double)
{
    // TODO: your code here
    model_.update();
}

bool Ui::tank_collision(ge211::Rectangle tank1, ge211::Rectangle tank2){
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