#include "Vector3.h"

class Platform
{
public:
    enum PLATFORM_TYPE
    {
        Normal,
    };

    Platform(Vector3 pos, Vector3 scale, PLATFORM_TYPE type);
    ~Platform();

    void Setpos(Vector3 pos);
    void Setscale(Vector3 scale);

    Vector3 getpos();
    Vector3 getscale();
    PLATFORM_TYPE type;
private:
    Vector3 pos;
    Vector3 scale;
};

