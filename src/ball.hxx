#pragma once

#include "geometry.hxx"
#include <ge211.hxx>

using Block = ge211::Rectangle;

// struct for cannon balls that the tanks can launch.
// When the balls hit each other, they annihilate. When
// the ball hits the edges of the screen, they are destroyed.
// When the balls hit the wall, they get destroyed as well as the
// wall. When the balls hit either the base or tank, they are
// destroyed along with the opponent.
struct Ball
{
    ///
    /// CONSTRUCTOR
    ///
    // constructor for ball, takes in parameters of paddle, a geometry object,
    // and a velocity
    Ball(Block const& paddle, Geometry const&, ge211::Dimensions const& velocity);

    ///
    /// MEMBER FUNCTIONS
    ///
    // determine the top left position of the ball's bounding box
    ge211::Position top_left() const;

    // generates a new ball for the next frame
    Ball next() const;

    // determines whether the ball has hit the top of the scene
    bool hits_top(Geometry const&) const;

    // determines whether the ball has hit the bottom of the scene
    bool hits_bottom(Geometry const&) const;

    // determines whether the ball has hit the sides of the scene
    bool hits_side(Geometry const&) const;

    // determines whether the ball has hit a block/rectangle
    bool hits_block(Block const&) const;

    // determines if the ball has hit another ball
    bool hits_ball(Ball const&) const;

    ///
    /// MEMBER VARIABLES
    ///

    // radius of the ball
    int               radius_;

    // velocity of the ball
    ge211::Dimensions velocity_;

    // center of the ball
    ge211::Position   center_;

    // determines whether the ball is live (moving), or
    // dead (not moving)
    bool              live_;
};

// overloaded operators to compare two different balls
bool operator==(Ball const&, Ball const&);
bool operator!=(Ball const&, Ball const&);

