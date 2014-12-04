#ifndef BUTTON_H
#define BUTTON_H
#include <SDL2/SDL.h>
#include <string.h>


#define BLUE_STATE true;
#define RED_STATE false;

class Button
{
//    const char* RED_BUTTON_PATH= "button-red.bmp";
//    const char* BLUE_BUTTON_PATH= "button-blue.bmp";

    const int rmask = 0x000000ff;
    const int gmask = 0x0000ff00;
    const int bmask = 0x00ff0000;
    const int amask = 0xff000000;
    const int hover_line=5;

    const SDL_Rect image_rect = { 5, 5, 225, 225 };
    bool state;

    SDL_Surface * red_button_surface;
    SDL_Surface * blue_button_surface;
    SDL_Surface * active_surface;
    SDL_Texture * texture_blue;
    SDL_Texture * texture_red;
    SDL_Renderer * renderer;

    void set_texture();

public:
    Button(SDL_Renderer*, int, int, int, int);
    ~Button();

    SDL_Rect DestR;
    SDL_Rect HoverR;
    void switch_state(void);
    bool hover_state;
    void hover(bool);
    SDL_Texture * active_texture;
};

#endif // BUTTON_H
