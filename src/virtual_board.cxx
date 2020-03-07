#include <iostream>
#include "virtual_board.hxx"

//////////////////////////Public/////////////////////////////////
Virtual_Board::Virtual_Board(int width, int height) {
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            square sq{ge211::Position {i,j},
                      std::vector<bool>{true, true, true, true},
                      false};
            vb_.push_back(sq);
        }
    }
    width_ = width;
    height_ = height;
    vb_create();
}

void Virtual_Board::vb_create() {
    recur_backtrack_();
}

square Virtual_Board::get_square_given_pos(ge211::Position pos){
    for (int i = 0; i < vb_.size(); i++){
        if (vb_[i].pos == pos){
            return vb_[i];
        }
    }
}

int Virtual_Board::height() {
    return height_;
}

int Virtual_Board::width() {
    return width_;
}



//////////////////////////Private/////////////////////////////////
void Virtual_Board::recur_backtrack_() {
    std::vector<ge211::Position> pos_stack{{0,0}};
    ge211::Position curr_pos{0, 0};
    while (true){
        std::vector<ge211::Position> available_moves = get_unvisited_neighbors_(curr_pos);
        get_square_given_pos_(curr_pos)->visited = true;
        if (available_moves.size() != 0){
            int ind = std::rand() % available_moves.size();
            ge211::Position next_pos =  available_moves[ind];
            int x_diff = next_pos.x - curr_pos.x;
            int y_diff = next_pos.y - curr_pos.y;
            if (x_diff == 0){
                if(y_diff == 1){
                    square* next_square = get_square_given_pos_(next_pos);
                    next_square->side_pres[2] = true;
                } else{
                    square* next_square = get_square_given_pos_(next_pos);
                    next_square->side_pres[0] = true;
                }
            } else{
                if(x_diff == 1){
                    square* next_square = get_square_given_pos_(next_pos);
                    next_square->side_pres[1] = true;
                } else{
                    square* next_square = get_square_given_pos_(next_pos);
                    next_square->side_pres[3] = true;
                }
            }

            pos_stack.push_back(next_pos);
            curr_pos = next_pos;

        } else{
            if (curr_pos == ge211::Position{0, 0}){
                break;
            }

            pos_stack.erase(pos_stack.end());
            curr_pos = pos_stack[pos_stack.size()-1];
        }
    }
}

std::vector<ge211::Position> Virtual_Board::get_unvisited_neighbors_(const ge211::Position pos) {
    int x_pos = pos.x;
    int y_pos = pos.y;
    std::vector<ge211::Position> neighbors{};
    for (int i = -1; i < 2; i = i + 2){
        int x_new = x_pos + i;
        int y_new = y_pos;
        if (x_new >= 0 && x_new < height_ && y_new >= 0 && y_new < width_ && !(get_square_given_pos_({x_new,y_new})->visited)) {
            neighbors.push_back(ge211::Position{x_new, y_new});
        }
    }
    for (int j = -1; j < 2; j = j + 2){
        int x_new = x_pos;
        int y_new = y_pos + j;
        if (x_new >= 0 && x_new < height_ && y_new >= 0 && y_new < width_ && !(get_square_given_pos_({x_new,y_new})->visited)) {
            neighbors.push_back(ge211::Position{x_new, y_new});
        }
    }

    return neighbors;
}

square* Virtual_Board::get_square_given_pos_(ge211::Position pos) {
    for (int i = 0; i < vb_.size(); i++){
        if (vb_[i].pos == pos){
            return &(vb_[i]);
        }
    }
}




