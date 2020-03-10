#pragma once

#include "geometry.hxx"
#include <ge211.hxx>

using Block = ge211::Rectangle;

struct Ball
{
    ///
    /// CONSTRUCTOR
    ///
    Ball(Block const& paddle, Geometry const&, ge211::Dimensions const& velocity);

    ///
    /// MEMBER FUNCTIONS
    ///

    // Returns the position of the top-left corner of the ball's "bounding
    // box", meaning the smallest rectangle in which is can be enclosed.
    // This is useful to the UI because sprites are positioned based on
    // their top-left corners.
    ge211::Position top_left() const;

    // Returns a new ball like this one but whose position has been
    // updated by adding on the velocity. This is useful because the
    // model's algorithm for collision detection involves speculatively
    // moving the ball and checking where it would end up, before
    // actually moving it.
    //
    // This can also be used to actually move it, via assignment:
    //
    //    ball_ = ball_.next();
    //
    Ball next() const;

    // These functions all perform collision detection by telling us whether
    // this ball is *past* the given edge.
    bool hits_top(Geometry const&) const;
    bool hits_bottom(Geometry const&) const;
    bool hits_side(Geometry const&) const;

    // Collision detection for blocks. Returns whether the circle's
    // bounding box intersects with the given block.
    //
    // Intersection between a circle and a rectangle is tricky, so we
    // will approximate it with the intersection of two rectangles.
    bool hits_block(Block const&) const;
    bool hits_ball(Ball const&) const;

    // Collision detection between the ball and the whole vector of bricks.
    // If the ball collides with some brick then that brick is removed and
    // the functions returns true. (The ball may collide with more than
    // one brick, but the function should return after the first collision
    // is found.) If there is no collision then the function returns false.
    bool destroy_brick(std::vector<Block>& bricks) const;

    ///
    /// MEMBER VARIABLES
    ///

    // The radius of the ball.
    int               radius_;

    // The velocity of the ball in pixels per tick.
    ge211::Dimensions velocity_;

    // The position of the center of the ball.
    ge211::Position   center_;

    // Whether the ball is moving freely (true) or stuck to the top of the
    // paddle (false).
    bool              live_;
};

// Compares two `Ball`s for equality. This may be useful for testing.
//
// Two `Ball`s are equal if all their member variables are pairwise
// equal.
bool operator==(Ball const&, Ball const&);

// Inequality for `Ball`s.
bool operator!=(Ball const&, Ball const&);

