#include "painter.h"
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

Painter::Painter(int width, int height)
{
    this->init_sdl(width, height);
    this->background_surface = SDL_CreateRGBSurface(NULL, width, height, 32, 0, 0, 0, 0);
    SDL_FillRect(this->background_surface, NULL, SDL_MapRGB(this->background_surface->format, 255, 255, 255));
    this->window_Rect.h = height;
    this->window_Rect.w = width;
    this->window_Rect.x = 0;
    this->window_Rect.y = 0;

    this->background_texture = SDL_CreateTextureFromSurface(this->renderer, background_surface);
    SDL_RenderCopy(this->renderer, this->background_texture, NULL, &this->window_Rect);
    this->button= new Button(this->renderer, 100, 50, (width-100)/2, (height-50)/2);
    SDL_RenderPresent(this->renderer);
}

Painter::~Painter()
{
    SDL_DestroyTexture(this->background_texture);
    SDL_FreeSurface(this->background_surface);
    SDL_Quit();
    SDL_DestroyWindow(window);
}

void Painter::init_sdl(int width, int height){

    // register method, which will be called when application ends/exits
    atexit(SDL_Quit);

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cerr << "coudln't init SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }

    this->window = SDL_CreateWindow("Praktikum 3 SDL",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                width,
                                height, SDL_WINDOW_RESIZABLE);
    if (this->window == NULL) {
        // In the event that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        exit(1);
    }
    this->renderer= SDL_CreateRenderer(this->window, -1, 0);

}



void Painter::draw_context(){
    SDL_UpdateWindowSurface( this->window );
}

void Painter::run(){
    cout << "run start" << endl;
    bool done=false;
    uint i= 0;
    while(!done){

        if(SDL_PollEvent(&this->event)){

            switch (this->event.type) {
                case SDL_QUIT:
                    done=true;
                    break;
                case SDL_MOUSEMOTION:
                    mouse_move();
                    break;
                case SDL_MOUSEBUTTONUP:
                    mouse_clicked();
                    break;
            }
        }
        draw_context();
    }

    this->button->~Button();
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);

    cout << endl <<"run end" << endl;
}

bool Painter::mouse_in_object(SDL_Rect &object_rect){
   bool res= this->event.motion.x >=object_rect.x  && this->event.motion.x <= object_rect.x+(object_rect.w) &&
           this->event.motion.y >= object_rect.y  &&  this->event.motion.y <= object_rect.y+(object_rect.h);
   if(res){
//       cout << "mouse is in button" << flush;
   }
   return res;
}

void Painter::mouse_clicked()
{
   if(this->mouse_in_object(this->button->DestR)){
       this->button->switch_state();
       SDL_RenderPresent(this->renderer);
   }
//      cout << "mouse clicked" << endl <<flush;
}

void Painter::mouse_move()
{
    bool hover = this->mouse_in_object(this->button->DestR);
    if(hover != this->button->hover_state){

//        cout << "change hover state" << flush;
        this->button->hover(hover);
        SDL_RenderPresent(this->renderer);
    }
}
