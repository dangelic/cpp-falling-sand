#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

class Renderer {
public:
    Renderer();
    ~Renderer();

    void initialize();
    void render();
    void handleEvent(SDL_Event& e);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool canvas[80][60]; // 80x60 canvas, each cell represents a pixel

    void drawCanvas();
};

#endif // RENDERER_H