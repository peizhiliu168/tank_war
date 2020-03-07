#include "board.hxx"

///////////////////Public////////////////////////
Board::Board(int width, int height)
    : virtual_board_(width, height)
    {
        v_wall_dim_ = geometry_.v_wall_dim();
        h_wall_dim_ = geometry_.h_wall_dim();
        square_dim_ = geometry_.square_dim();
        b_create();
    }

std::vector<ge211::geometry::Rectangle> Board::get_squares() const {
    return squares_;
}

std::vector<ge211::geometry::Rectangle> Board::get_walls() const {
    return walls_;
}

bool Board::destroy_wall(const ge211::Rectangle cannon) {
    for (int i = 0; i < walls_.size(); i++){
        if (is_touching(cannon, walls_[i])){
            walls_.erase(walls_.begin() + i);
            return true;
        }
    }
    return false;
}

bool Board::is_touching(const ge211::Rectangle object, const ge211::Rectangle wall) {
    ge211::Position object_tl = object.top_left();
    ge211::Position object_br = object.bottom_right();
    ge211::Position wall_tl = wall.top_left();
    ge211::Position wall_br = wall.bottom_right();

    if (object_br.x < wall_tl.x || object_tl.x > wall_br.x){
        return false;
    }

    if (object_tl.y < wall_br.y || object_br.y > wall_tl.y){
        return false;
    }

    return true;

}

///////////////////Private////////////////////////

void Board::b_create() {
    for (int i = 0; i < geometry_.board_size.width; ++i) {
        for (int j = 0; j < geometry_.board_size.height; ++j) {
            ge211::Position square_pos {geometry_.start.x + geometry_.wall_thickness_ + i * (square_dim_.width + geometry_.wall_thickness_),
                                      geometry_.start.y + geometry_.wall_thickness_ + j * (square_dim_.height + geometry_.wall_thickness_)};
            ge211::Rectangle square{};
            square.height = square_dim_.height;
            square.width = square_dim_.width;
            square.x = square_pos.x;
            square.y = square_pos.y;

            squares_.push_back(square);

            for (int k = 0; k < 4; k++){
                bool side = virtual_board_.get_square_given_pos({i, j}).side_pres[k];
                if (k == 0 && side){
                    ge211::Rectangle wall{};
                    wall.height = h_wall_dim_.height;
                    wall.width = h_wall_dim_.width;
                    wall.x = square_pos.x - geometry_.wall_thickness_;
                    wall.y = square_pos.y - geometry_.wall_thickness_;

                    walls_.push_back(wall);
                }
                if (k == 1 && side){
                    ge211::Rectangle wall{};
                    wall.height = v_wall_dim_.height;
                    wall.width = v_wall_dim_.width;
                    wall.x = square_pos.x + square_dim_.width;
                    wall.y = square_pos.y - geometry_.wall_thickness_;

                    walls_.push_back(wall);
                }
                if (k == 2 && side){
                    ge211::Rectangle wall{};
                    wall.height = h_wall_dim_.height;
                    wall.width = h_wall_dim_.width;
                    wall.x = square_pos.x - geometry_.wall_thickness_;
                    wall.y = square_pos.y + square_dim_.height;

                    walls_.push_back(wall);
                }
                if (k == 3 && side){
                    ge211::Rectangle wall{};
                    wall.height = v_wall_dim_.height;
                    wall.width = v_wall_dim_.width;
                    wall.x = square_pos.x - geometry_.wall_thickness_;
                    wall.y = square_pos.y - geometry_.wall_thickness_;

                    walls_.push_back(wall);
                }
            }
        }
    }
}





