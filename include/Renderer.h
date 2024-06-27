#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

class Renderer {
public:
    Renderer();            
    ~Renderer();            

    void initialize();      
    void render();          

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif // RENDERER_H
