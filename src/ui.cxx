#include "ui.hxx"

///
/// VIEW CONSTANTS
///

// Colors are red-green-blue(-alpha), each component
// from 0 to 255.
ge211::Color const ball_red_color    {255, 127, 127};
ge211::Color const ball_blue_color    {127, 127, 255};
ge211::Color const paddle_color  {127, 255, 127};
ge211::Color const brick_color   {100, 100, 100};
ge211::Color const base_color   {255, 255, 255};

///
/// VIEW FUNCTIONS
///

// Data members that are references cannot be initialized by assignment
// in the constructor body and must be initialized in a member
// initializer list.
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
    if (j == true || key == ge211::Key::code('j')){
        model_.launch_red();
    }
    if (p == true || key == ge211::Key::code('p')){
        model_.launch_blue();
    }

    ///tank red operations
    if (a == true || key == ge211::Key::code('a')){
        if (model_.tank_red_orientation_ == 1) {
            model_.tank_red_orientation_ = 4;
        }
        else{
            model_.tank_red_orientation_ = model_.tank_red_orientation_ - 1;
        }
    }
    if (s == true || key == ge211::Key::code('s')){
        if (model_.tank_red_orientation_ == 1)
            if (model_.tank_red_.y+tank_sprite_.dimensions().height+3 < model_.geometry_.scene_dims.height
                && !model_.board_.is_touching_wall(model_.tank_red_))
                model_.tank_red_.y += 3;
        if (model_.tank_red_orientation_ == 3)
            if (model_.tank_red_.y-3 > 0)
                model_.tank_red_.y -= 3;
        if (model_.tank_red_orientation_ == 2)
            if (model_.tank_red_.x-3 > 0)
                model_.tank_red_.x -= 3;
        if (model_.tank_red_orientation_ == 4)
            if (model_.tank_red_.x+tank_sprite_.dimensions().width+3 < model_.geometry_.scene_dims.width
                && !model_.board_.is_touching_wall(model_.tank_red_))
                model_.tank_red_.x += 3;
    }
    if (w == true || key == ge211::Key::code('w')){
        if (model_.tank_red_orientation_ == 1)
            if (model_.tank_red_.y-3 > 0)
                model_.tank_red_.y -= 3;
        if (model_.tank_red_orientation_ == 3)
            if (model_.tank_red_.y+tank_sprite_.dimensions().height+3 < model_.geometry_.scene_dims.height
            && !model_.board_.is_touching_wall(model_.tank_red_))
                model_.tank_red_.y += 3;
        if (model_.tank_red_orientation_ == 2)
            if (model_.tank_red_.x+tank_sprite_.dimensions().width+3 < model_.geometry_.scene_dims.width
                && !model_.board_.is_touching_wall(model_.tank_red_))
                model_.tank_red_.x += 3;
        if (model_.tank_red_orientation_ == 4 )
            if (model_.tank_red_.x-3 > 0)
                model_.tank_red_.x -= 3;
    }
    if (d == true || key == ge211::Key::code('d')) {
        if (model_.tank_red_orientation_ == 4) {
            model_.tank_red_orientation_ = 1;
        }
        else{
            model_.tank_red_orientation_ = model_.tank_red_orientation_ + 1;
        }
    }

    ///tank blue operations
    if (up == true || key == ge211::Key::up()){
        if (model_.tank_blue_orientation_ == 1)
            if (model_.tank_blue_.y-3 > 0)
                model_.tank_blue_.y -= 3;
        if (model_.tank_blue_orientation_ == 3)
            if (model_.tank_blue_.y+tank_sprite_.dimensions().height+3 < model_.geometry_.scene_dims.height
            && !model_.board_.is_touching_wall(model_.tank_blue_))
                model_.tank_blue_.y += 3;
        if (model_.tank_blue_orientation_ == 2)
            if (model_.tank_blue_.x+tank_sprite_.dimensions().width+3 < model_.geometry_.scene_dims.width
            && !model_.board_.is_touching_wall(model_.tank_blue_))
                model_.tank_blue_.x += 3;
        if (model_.tank_blue_orientation_ == 4)
            if (model_.tank_blue_.x-3 > 0)
                model_.tank_blue_.x -= 3;
    }
    if (down == true || key == ge211::Key::down()){
        if (model_.tank_blue_orientation_ == 1)
            if (model_.tank_blue_.y+tank_sprite_.dimensions().height+3 < model_.geometry_.scene_dims.height
            && !model_.board_.is_touching_wall(model_.tank_blue_))
                model_.tank_blue_.y += 3;
        if (model_.tank_blue_orientation_ == 3)
            if (model_.tank_blue_.y-3 > 0)
                model_.tank_blue_.y -= 3;
        if (model_.tank_blue_orientation_ == 2)
            if (model_.tank_blue_.x-3 > 0)
                model_.tank_blue_.x -= 3;
        if (model_.tank_blue_orientation_ == 4)
            if (model_.tank_blue_.x+tank_sprite_.dimensions().width+3 < model_.geometry_.scene_dims.width
            && !model_.board_.is_touching_wall(model_.tank_blue_))
                model_.tank_blue_.x += 3;
    }
    if (left == true || key == ge211::Key::left()) {
        if (model_.tank_blue_orientation_ == 1) {
            model_.tank_blue_orientation_ = 4;
        }
        else{
            model_.tank_blue_orientation_ -= 1;
        }
    }
    if (right == true || key == ge211::Key::right()) {
        if (model_.tank_blue_orientation_ == 4) {
            model_.tank_blue_orientation_ = 1;
        }
        else{
            model_.tank_blue_orientation_ += 1;
        }
    }
}

void Ui::on_frame(double)
{
    // TODO: your code here
    model_.update();
}
