#pragma once

enum Buttons
{
    p1PaddleUp = 0,
    p1PaddleDown,
    p2PaddleUp,
    p2PaddleDown
};

enum CollisionType
{
    None        = (1u << 0),
    P1Paddle    = (1u << 1),
    P2Paddle    = (1u << 2),
    Wall        = (1u << 3),
    Left        = (1u << 4),
    Right       = (1u << 5)
};