#include <Pixel.h>

Pixel::Pixel(Screen* screenPtr, Vec2 position){
    this->position.x = position.x;
    this->position.y = position.y;
}

Pixel::Pixel(Screen* screenPtr, float x, float y){
    this->position.x = x;
    this->position.y = y;
}

Pixel::Draw(){
    this->screenPtr->CreatePixel(round(this->position.x), round(this->position.y));
}