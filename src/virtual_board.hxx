#pragma once

#include <vector>
#include <ge211.hxx>
#include <cstdlib>

struct square{
    // position on the virtual board
    ge211::Position pos;

    // a vector of 4 boolean values, representing whether there
    // is a wall (true) on the top (index = 0), right (index = 1)
    // bottom (index = 2), or left (index = 3) of the square with
    // a particular position
    std::vector<bool> side_pres;

    // a boolean that indicates whether the position has been visited
    // (true) by the backtracking algorithm
    bool  visited;
};

// An object that contains a list of square structs as variable
// vb_. Each square struct contain its position, as well as a vector
// of booleans to indicate sides. The vector is basically a grid with
// dimension given by the geometry object. The virtual board
// basically modifies vb_ with a recursive backtrack algorithm to
// generate a maze.
class Virtual_board
{
public:

    ///
    /// CONSTRUCTOR
    ///
    // constructor, takes in width, height, and a
    // random seed to create virtual board
    explicit Virtual_board(int, int, int);

    ///
    /// PUBLIC MEMBER FUNCTIONS
    ///
    // returns the width of the board
    int height();

    // returns the height of the board
    int width();

    ///
    /// PUBLIC MEMBER VARIABLES
    ///
    // returns the square given a specific position
    square get_square_given_pos(ge211::Position) const;

    // overloaded assignment operator, replaces vb_ variable with
    // new vb_
    Virtual_board& operator=(const Virtual_board& );

private:
    ///
    /// PRIVATE MEMBER FUNCTIONS
    ///
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

    // remove edges represented by the boolean vector which are
    // repeats
    void remove_duplicate_edges();

    // remove edges represented by the boolean vector which are along
    // the outer edge of the board
    void remove_boundary();

    ///
    /// PRIVATE MEMBER VARIABLES
    ///
    // virtual representation of the board
    std::vector<square> vb_;

    // width, height, and seed of the virtual board
    int width_;
    int height_;
};