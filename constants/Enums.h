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
    None,
    Paddle,
    Wall,
    Left,
    Right
};