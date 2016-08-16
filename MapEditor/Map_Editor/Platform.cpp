
#include "Platform.h"


Platform::Platform(Vector3 pos, Vector3 scale, PLATFORM_TYPE type)
{
    this->pos = pos;
    this->scale = scale;
    this->type = type;
}


Platform::~Platform()
{
}


void Platform::Setpos(Vector3 pos)
{
    this->pos = pos;
}
void Platform::Setscale(Vector3 scale)
{
    this->scale = scale;
}

Vector3 Platform::getpos()
{
    return pos;
}
Vector3 Platform::getscale()
{
    return scale;
}