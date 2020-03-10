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

    ge211::Position top_left() const;

    Ball next() const;

    bool hits_top(Geometry const&) const;
    bool hits_bottom(Geometry const&) const;
    bool hits_side(Geometry const&) const;

    bool hits_block(Block const&) const;
    bool hits_ball(Ball const&) const;

    ///
    /// MEMBER VARIABLES
    ///

    int               radius_;

    ge211::Dimensions velocity_;

    ge211::Position   center_;

    bool              live_;
};

bool operator==(Ball const&, Ball const&);
bool operator!=(Ball const&, Ball const&);

