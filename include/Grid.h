// Grid.h

#ifndef GRID_H
#define GRID_H

#include "Cell.h"
#include <SDL.h>

class Grid {
public:
    static const int GRID_WIDTH = 100;
    static const int GRID_HEIGHT = 100;

    Grid(SDL_Renderer* renderer); 
    ~Grid();

    void handleClick(int mouseX, int mouseY);
    void update(); 
    void render(); 

private:
    Cell cells[GRID_WIDTH][GRID_HEIGHT];
    SDL_Renderer* renderer;
};

#endif // GRID_H
