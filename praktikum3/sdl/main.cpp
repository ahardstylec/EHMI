#include <iostream>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <assert.h>
#include "painter.h"

using namespace std;

int main()
{
    Painter painter(640, 480);
    painter.run();
    return 0;
}
