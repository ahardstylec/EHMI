#ifndef PAINTER_H
#define PAINTER_H
#include <SDL/SDL.h>

class painter
{
public:
    painter();
    void draw(int x, int y);
private:
    SDL_Surface * surface;
    SDL_Event event;
};

#endif // PAINTER_H
