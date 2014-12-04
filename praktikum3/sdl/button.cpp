#include "button.h"
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

Button::Button(SDL_Renderer * renderer, int width, int height, int x, int y)
{
    this->DestR.y = y;
    this->DestR.x = x;
    this->DestR.h = height;
    this->DestR.w = width;

    this->HoverR.x = hover_line;
    this->HoverR.y = 80;
    this->HoverR.w = 40;
    this->HoverR.h = hover_line;
    this->hover_state=false;

    this->renderer= renderer;
    this->blue_button_surface   = SDL_CreateRGBSurface(NULL, height, width, 32, 0, 0, 0, 0);
    this->red_button_surface    = SDL_CreateRGBSurface(NULL, height, width, 32, 0, 0, 0, 0);
    this->set_texture();
    this->active_texture = this->texture_blue;

    SDL_RenderCopy(this->renderer, this->active_texture, NULL, &this->DestR);
    this->state=BLUE_STATE;
}



void Button::set_texture(){
    SDL_DestroyTexture(this->texture_red);
    SDL_DestroyTexture(this->texture_blue);
    if(this->hover_state){
        SDL_FillRect(this->blue_button_surface, &this->HoverR, SDL_MapRGB(this->blue_button_surface->format, 125, 125, 125));
        SDL_FillRect(this->red_button_surface,  &this->HoverR, SDL_MapRGB(this->red_button_surface->format, 125, 125, 125));
    }else{
        SDL_FillRect(this->blue_button_surface, NULL, SDL_MapRGB(this->blue_button_surface->format, 0, 0, 255));
        SDL_FillRect(this->red_button_surface, NULL, SDL_MapRGB(this->red_button_surface->format, 255, 0, 0));
    }
    this->texture_blue= SDL_CreateTextureFromSurface(this->renderer, this->blue_button_surface);
    this->texture_red= SDL_CreateTextureFromSurface(this->renderer, this->red_button_surface);
    if( this->state){
        this->active_texture=this->texture_blue;
    }else{
        this->active_texture=this->texture_red;
    }
}

Button::~Button()
{
    SDL_DestroyTexture(this->texture_blue);
    SDL_DestroyTexture(this->texture_red);
    SDL_DestroyTexture(this->active_texture);
    SDL_FreeSurface(this->blue_button_surface);
    SDL_FreeSurface(this->red_button_surface);
}

void Button::hover(bool hover){
    this->hover_state = hover;
    this->set_texture();
    SDL_RenderCopy(this->renderer, this->active_texture, NULL, &this->DestR);
}

void Button::switch_state(){
    if( this->state){
        this->active_texture= this->texture_red;
        this->state= RED_STATE;
    }else{
        this->active_texture= this->texture_blue;
        this->state= BLUE_STATE;
    }
    SDL_RenderCopy(this->renderer, this->active_texture, NULL, &this->DestR);
}
