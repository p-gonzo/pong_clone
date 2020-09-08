#pragma once

class Constants
{
private:
    Constants();
public:
    static constexpr auto WindowWidth { 1280 };
    static constexpr auto WindowHeight { 720 };
    static constexpr auto BallHeight { 15 };
    static constexpr auto BallWidth { 15 };
    static constexpr auto PaddleHeight { 100 };
    static constexpr auto PaddleWidth { 10 };
    static constexpr auto PaddleGap { 50.0f };
    static constexpr auto PaddleSpeed { 1.0f };
};