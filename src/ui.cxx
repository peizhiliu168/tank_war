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
        , keys_{}

{}

ge211::Dimensions Ui::initial_window_dimensions() const
{
    return model_.geometry_.scene_dims;
}

void Ui::draw(ge211::Sprite_set& sprites)
{
    if (model_.is_game_over()){
        if (model_.get_winner() == 1){
            sprites.add_sprite(player_1_win,
                {(model_.geometry_.scene_dims.width - player_1_win.dimensions().width) / 2,
                 (model_.geometry_.scene_dims.height-player_1_win.dimensions().height) / 2});
        } else if (model_.get_winner() == 2){
            sprites.add_sprite(player_2_win,
                {(model_.geometry_.scene_dims.width - player_2_win.dimensions().width) / 2,
                (model_.geometry_.scene_dims.height-player_2_win.dimensions().height) / 2});
        }

        return;
    }

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
    sprites.add_sprite(first_score_board, model_.geometry_.blue_board_pos, 0);
    sprites.add_sprite(second_score_board, model_.geometry_.red_board_pos, 0);

    // adds text sprites to score board
    sprites.add_sprite(player_one, {(model_.geometry_.blue_board_pos.x + (model_.geometry_.score_board_size.width - player_one.dimensions().width) / 2),
                                    model_.geometry_.blue_board_pos.y}, 1);
    sprites.add_sprite(player_two, {(model_.geometry_.red_board_pos.x + (model_.geometry_.score_board_size.width - player_two.dimensions().width) / 2),
                                    model_.geometry_.red_board_pos.y}, 1);
    first_score.reconfigure(ge211::Text_sprite::Builder(score_font_).message(std::to_string(model_.blue_score_.get_score())));
    second_score.reconfigure(ge211::Text_sprite::Builder(score_font_).message(std::to_string(model_.red_score_.get_score())));
    sprites.add_sprite(first_score, {(model_.geometry_.blue_board_pos.x + (model_.geometry_.score_board_size.width - first_score.dimensions().width) / 2),
                                     model_.geometry_.blue_board_pos.y + first_score.dimensions().height / 2}, 1);
    sprites.add_sprite(second_score, {(model_.geometry_.red_board_pos.x + (model_.geometry_.score_board_size.width - second_score.dimensions().width) / 2),
                                      model_.geometry_.red_board_pos.y + second_score.dimensions().height / 2}, 1);
}

///
/// CONTROLLER FUNCTIONS
///
void Ui::on_key_down(ge211::Key key) {
    if (key == ge211::Key::code('w'))
        keys_.w = true;
    if (key == ge211::Key::code('a'))
        keys_.a = true;
    if (key == ge211::Key::code('s'))
        keys_.s = true;
    if (key == ge211::Key::code('d'))
        keys_.d = true;
    if (key == ge211::Key::up())
        keys_.up = true;
    if (key == ge211::Key::down())
        keys_.down = true;
    if (key == ge211::Key::left())
        keys_.left = true;
    if (key == ge211::Key::right())
        keys_.right = true;
    if (key == ge211::Key::code('j'))
        keys_.j = true;
    if (key == ge211::Key::code('p'))
        keys_.p = true;
}
void Ui::on_key_up(ge211::Key key) {
    if (key == ge211::Key::code('w'))
        keys_.w = false;
    if (key == ge211::Key::code('a'))
        keys_.a = false;
    if (key == ge211::Key::code('s'))
        keys_.s = false;
    if (key == ge211::Key::code('d'))
        keys_.d = false;
    if (key == ge211::Key::up())
        keys_.up = false;
    if (key == ge211::Key::down())
        keys_.down = false;
    if (key == ge211::Key::left())
        keys_.left = false;
    if (key == ge211::Key::right())
        keys_.right = false;
    if (key == ge211::Key::code('j'))
        keys_.j = false;
    if (key == ge211::Key::code('p'))
        keys_.p = false;
}

void Ui::on_key(ge211::Key key)
{

    if (key == ge211::Key::code('q'))
        quit();

    ///cannon ball operations
    if ( keys_.j || key == ge211::Key::code('j')){
        model_.launch_red();
    }
    if ( keys_.p || key == ge211::Key::code('p')){
        model_.launch_blue();
    }

    ///tank red operations

}

void Ui::on_frame(double)
{
    model_.update(keys_);
}