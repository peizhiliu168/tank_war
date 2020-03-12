#include "board.hxx"

///////////////////Public////////////////////////
Board::Board(int width, int height)
    : virtual_board_(width, height)
    {
        v_wall_dim_ = geometry_.v_wall_dim();
        h_wall_dim_ = geometry_.h_wall_dim();
        square_dim_ = geometry_.square_dim();
        width_ = width;
        height_ = height;
        b_create();
    }

std::vector<ge211::geometry::Rectangle> Board::get_squares() const {
    return squares_;
}

std::vector<ge211::geometry::Rectangle> Board::get_walls() const {
    return walls_;
}

bool Board::is_touching_wall(const ge211::Rectangle tank, const int ori){
    for (int i = 0; i < walls_.size(); i++){
        if (is_touching(tank, walls_[i], ori)){
            return true;
        }
    }
    return false;
}

bool Board::destroy_wall(const Ball cannon) {
    for (int i = 0; i < walls_.size(); i++){
        ge211::Rectangle bounding_box {};
        bounding_box.height = 2 * cannon.radius_;
        bounding_box.width = 2 * cannon.radius_;
        bounding_box.x = cannon.top_left().x;
        bounding_box.y = cannon.top_left().y;
        if (is_touching(bounding_box, walls_[i], 0)){
            walls_.erase(walls_.begin() + i);
            return true;
        }
    }
    return false;
}

bool Board::is_touching(const ge211::Rectangle object, const ge211::Rectangle wall, const int ori) {
    ge211::Position object_tl = object.top_left();
    ge211::Position object_br = object.bottom_right();
    ge211::Position wall_tl = wall.top_left();
    ge211::Position wall_br = wall.bottom_right();
    if (ori == 0) {
        if (object_br.x <= wall_tl.x || object_tl.x >= wall_br.x) {
            return false;
        }
        if (object_tl.y >= wall_br.y || object_br.y <= wall_tl.y) {
            return false;
        }
        return true;
    }
    if (ori == 1 && (object_tl.y <= wall_br.y && object_tl.y>=wall_tl.y) && (object_br.x >= wall_tl.x && object_tl.x <= wall_br.x))
        return true;
    if (ori == 2 && (object_br.x >= wall_tl.x&&object_br.x<=wall_br.x) && (object_tl.y <= wall_br.y && object_br.y >= wall_tl.y))
        return true;
    if (ori == 3 && (object_br.y >= wall_tl.y && object_br.y<=wall_br.y) && (object_br.x >= wall_tl.x && object_tl.x <= wall_br.x))
        return true;
    if (ori == 4 && (object_tl.x <= wall_br.x&&object_tl.x>=wall_tl.x) && (object_tl.y <= wall_br.y && object_br.y >= wall_tl.y))
        return true;

    return false;
}

void Board::reset() {
    Virtual_board new_vboard{width_, height_};
    virtual_board_ = new_vboard;
    std::vector<ge211::Rectangle> empty;
    walls_ = empty;
    squares_ = empty;
    b_create();
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






