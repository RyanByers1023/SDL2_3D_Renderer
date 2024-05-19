#pragma once
#include <Vec2.h>
#include <Screen.h>

class Pixel{
public:
    Pixel(Screen* screenPtr, Vec2 position);
    Vec2(Screen* screenPtr, float x, float y)
    Vec2 position;
    void Draw();
private:
    Screen* screenPtr;
};