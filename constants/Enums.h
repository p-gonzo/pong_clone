#pragma once

enum Buttons
{
    p1PaddleUp = 0,
    p1PaddleDown,
    p2PaddleUp,
    p2PaddleDown
};

enum class CollisionType
{
    None    = (1u << 0),
    Paddle  = (1u << 1),
    Wall    = (1u << 2),
    Left    = (1u << 3),
    Right   = (1u << 4)
};