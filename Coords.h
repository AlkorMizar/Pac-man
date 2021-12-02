#pragma once
#include <math.h>

struct Coords
{
	int x=0;
	int y=0;
    Coords operator+(Coords sec)
    {
        return Coords{this->x+sec.x,this->y + sec.y };    // return old value
    }
    Coords operator*(double sp)
    {
        return Coords{ (int)round(this->x * sp), (int)round(this->y*sp) };    // return old value
    }
    Coords operator/(int sp)
    {
        return Coords{ this->x / sp,this->y / sp };    // return old value
    }
    Coords operator%(int sp)
    {
        return Coords{ this->x % sp,this->y % sp };    // return old value
    }
    Coords operator+(int sp)
    {
        return Coords{ this->x + sp,this->y + sp };    // return old value
    }
    bool operator==(Coords c)
    {
        return this->x==c.x && this->y == c.y;    // return old value
    }
    Coords operator-() {
        return Coords{ -this->x ,-this->y };
    }

    bool operator!=(Coords c) {
        return this->x!=c.x || this->y!=c.y ;
    }
};
