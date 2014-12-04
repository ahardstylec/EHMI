#ifndef PAINTER_H
#define PAINTER_H
#include <SDL2/SDL.h>
#include "button.h"

class Painter
{
public:
    Painter(int width, int height);
    ~Painter();
    void run();
private:
    SDL_Rect window_Rect;

    SDL_Surface * background_surface;
    SDL_Texture * background_texture;
    SDL_Event event;
    SDL_Window * window;
    SDL_Renderer * renderer;
    Button *button;

    bool mouse_in_object(SDL_Rect &);
    void shotdown();
    void mouse_clicked();
    void mouse_move();
    void draw_context();

    void init_sdl(int, int);
};

#endif // PAINTER_H
