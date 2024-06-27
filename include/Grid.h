#ifndef GRID_H
#define GRID_H

#include <SDL.h>

const int GRID_WIDTH = 80;
const int GRID_HEIGHT = 60;

struct Cell {
    bool isActive;
};

class Grid {
public:
    Grid(SDL_Renderer* renderer);
    ~Grid();
    void handleClick(int mouseX, int mouseY);
    void spawnRandomGrain(int mouseX, int mouseY);
    void update();
    void render();

    Cell cells[GRID_WIDTH][GRID_HEIGHT];

private:
    SDL_Renderer* renderer;
};

#endif // GRID_H