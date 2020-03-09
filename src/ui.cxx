// YOU DEFINITELY NEED TO MODIFY THIS FILE.

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

///
/// VIEW FUNCTIONS
///

// Data members that are references cannot be initialized by assignment
// in the constructor body and must be initialized in a member
// initializer list.
Ui::Ui(Model& model)
        : model_(model)
{ }

ge211::Dimensions Ui::initial_window_dimensions() const
{
    return model_.geometry_.scene_dims;
}

void Ui::draw(ge211::Sprite_set& sprites)
{


    // TODO: your code here
    sprites.add_sprite(tank_sprite_, model_.tank1_.top_left());
    sprites.add_sprite(tank_sprite_, model_.tank2_.top_left());
    sprites.add_sprite(ball_red_sprite_, model_.ball_red_.top_left());
    sprites.add_sprite(ball_blue_sprite_, model_.ball_blue_.top_left());
    //for (int i = 0; i<model_.bricks_.size(); i++){
        //sprites.add_sprite(brick_sprite_, model_.bricks_[i].top_left());
    //}

    // generates maze for board
    std::vector<ge211::Rectangle> walls = model_.board_.get_walls();
    for (int i = 0; i < walls.size(); i++){
        if (walls[i].dimensions().height == model_.geometry_.wall_thickness_){
            sprites.add_sprite(h_wall_, walls[i].top_left());
        } else{
            sprites.add_sprite(v_wall_, walls[i].top_left());
        }
    }

    // creates score_board
    sprites.add_sprite(first_score_board, model_.geometry_.first_board_pos);
    sprites.add_sprite(second_score_board, model_.geometry_.second_board_pos);

}

///
/// CONTROLLER FUNCTIONS
///

void Ui::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q'))
        quit();
    if (key == ge211::Key::code('j'))
        model_.launch_red();
    if (key == ge211::Key::code('p'))
        model_.launch_blue();
    if (key == ge211::Key::code('a'))
        model_.tank1_.x -= 3;
    if (key == ge211::Key::code('w'))
        model_.tank1_.y -= 3;
    if (key == ge211::Key::code('s'))
        model_.tank1_.y += 3;
    if (key == ge211::Key::code('d'))
        model_.tank1_.x += 3;
    if (key == ge211::Key::up())
        model_.tank2_.y += 3;
    if (key == ge211::Key::down())
        model_.tank2_.y -= 3;
    if (key == ge211::Key::left())
        model_.tank2_.x -= 3;
    if (key == ge211::Key::right())
        model_.tank2_.x += 3;
}

void Ui::on_frame(double)
{
    // TODO: your code here
    model_.update(get_random().between(0 - (model_.geometry_.max_boost),
            model_.geometry_.max_boost));
}

//void Ui::on_mouse_up(ge211::Mouse_button button, ge211::Position)
//{
    //if (button == ge211::Mouse_button::left){
        //model_.launch();
    //}
//}



