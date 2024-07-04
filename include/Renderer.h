// Renderer.h

#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

class Renderer 
{
public:
    Renderer(SDL_Renderer* renderer);
    ~Renderer(); 

    void handleEvent(SDL_Event& e);
    void render(); 

private:
    SDL_Renderer* renderer;
};

#endif // RENDERER_H