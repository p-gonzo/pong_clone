#pragma once;

using byte = unsigned char;

struct Rgba
{
    Rgba( byte r, byte g, byte b, byte a): r(r), g(g), b(b), a(a) { };
    byte r;
    byte g;
    byte b;
    byte a;
};