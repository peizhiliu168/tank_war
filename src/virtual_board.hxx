#pragma once

#include <vector>
#include <ge211.hxx>
#include <cstdlib>

struct square{
    ge211::Position pos;
    std::vector<bool> side_pres;
    bool  visited;
};

class Virtual_Board
{
public:
    // constructor, takes in width and height of the virtual board
    explicit Virtual_Board(int, int);

    // returns the width of the board
    int height();

    // returns the height of the board
    int width();

    // returns the square given a specific position
    square get_square_given_pos(ge211::Position) const;

private:
    // creates maze-like pattern for the board
    void vb_create();

    // function that uses recursive backtracking algorithm to generate
    // a random maze
    void recur_backtrack_();

    // helper function for recur_backtrack to get neighbors that haven't
    // been visited yet
    std::vector<ge211::Position> get_unvisited_neighbors_(ge211::Position);

    // takes in a position and gives back the square struct that
    // corresponds to that position as a square pointer
    square* get_square_given_pos_(ge211::Position);

    void remove_duplicate_edges();

    // virtual representation of the board
    std::vector<square> vb_;

    // width and height of the board
    int width_;
    int height_;

    void remove_boundary();
};