#ifndef GRID_H
#define GRID_H

#include <SDL.h>

const int GRID_WIDTH = 80 * 1.25;
const int GRID_HEIGHT = 60 * 1.25;

struct Cell 
{
    bool isActive;
    SDL_Color color; // Color of the cell
};

class Grid 
{
public:
    Grid(SDL_Renderer* renderer);
    ~Grid();
    void handleClick(int mouseX, int mouseY);
    void spawnRandomGrain(int mouseX, int mouseY);
    void update();
    void render();

    Cell cells[GRID_WIDTH][GRID_HEIGHT];

    // Function to set color tweak parameters
    void setColorTweak(float hueTweak);

private:
    SDL_Renderer* renderer;

    // Helper function for converting HSV to RGB
    float hueTweak; // Hue tweak parameter shifting the palette
    void HSVtoRGB(float h, float s, float v, int& r, int& g, int& b);
};

#endif // GRID_H
