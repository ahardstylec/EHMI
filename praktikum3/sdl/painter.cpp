#include "painter.h"
#include <SDL/SDL.h>
#include <iostream>

painter::painter()
{
    init_sdl();
}

void Painter::init_sdl(){

    // disable mouse because of virtual console
    SDL_putenv("SDL_NOMOUSE=1");

    // SDL VIDEO startable?
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cerr << "coudln't init SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }
    // register method, which will be called when application ends/exits
    atexit(SDL_Quit);

    surface = SDL_SetVideoMode();

}

void painter::draw()
{
}
