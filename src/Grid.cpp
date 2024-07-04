#include "../include/Grid.h"
#include <iostream>
#include <cstdlib> // For rand()
#include <cmath> // For std::abs

Grid::Grid(SDL_Renderer* renderer) : renderer(renderer), hueTweak(0.0f) 
{
    // Initialize grid cells
    for (int i = 0; i < GRID_WIDTH; ++i) 
    {
        for (int j = 0; j < GRID_HEIGHT; ++j) 
        {
            cells[i][j].isActive = false;
        }
    }
}

Grid::~Grid() 
{
    // Cleanup if needed
}

void Grid::handleClick(int mouseX, int mouseY) 
{
    // Determine which cell was clicked based on mouse coordinates
    int cellX = mouseX / (800 / GRID_WIDTH);
    int cellY = mouseY / (600 / GRID_HEIGHT);

    if (cellX >= 0 && cellX < GRID_WIDTH && cellY >= 0 && cellY < GRID_HEIGHT) 
    {
        // Activate the clicked cell
        cells[cellX][cellY].isActive = true;

        // Determine color based on position relative to the grid
        float hue = std::abs(static_cast<float>(cellX - GRID_WIDTH / 2)) / (GRID_WIDTH / 2) * 360.0f + hueTweak;
        float saturation = 1.0f;
        float value = 1.0f;

        // Convert HSV to RGB
        int r, g, b;
        HSVtoRGB(hue, saturation, value, r, g, b);

        cells[cellX][cellY].color = { static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), 255 }; // RGBA, alpha is 255 (opaque)

        std::cout << "Cell (" << cellX << ", " << cellY << ") state changed to active with color ("
                  << r << ", " << g << ", " << b << ")" << std::endl;

        // Activate random neighboring cells for sand effect
        for (int i = 0; i < 3; ++i) { // Activate up to 3 random neighbors
            int randDirection = rand() % 4;
            int neighborX = cellX;
            int neighborY = cellY;

            switch (randDirection) 
            {
                case 0: // Left
                    neighborX = (cellX > 0) ? cellX - 1 : cellX;
                    break;
                case 1: // Right
                    neighborX = (cellX < GRID_WIDTH - 1) ? cellX + 1 : cellX;
                    break;
                case 2: // Up
                    neighborY = (cellY > 0) ? cellY - 1 : cellY;
                    break;
                case 3: // Down
                    neighborY = (cellY < GRID_HEIGHT - 1) ? cellY + 1 : cellY;
                    break;
            }

            if (neighborX != cellX || neighborY != cellY) 
            {
                cells[neighborX][neighborY].isActive = true;

                // Determine color based on position relative to the grid
                hue = std::abs(static_cast<float>(neighborX - GRID_WIDTH / 2)) / (GRID_WIDTH / 2) * 360.0f + hueTweak;

                // Convert HSV to RGB
                HSVtoRGB(hue, saturation, value, r, g, b);

                cells[neighborX][neighborY].color = { static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), 255 }; // RGBA, alpha is 255 (opaque)

                std::cout << "Neighbor cell (" << neighborX << ", " << neighborY << ") state changed to active with color ("
                          << r << ", " << g << ", " << b << ")" << std::endl;
            }
        }
    }
}

void Grid::spawnRandomGrain(int mouseX, int mouseY) 
{
    // Determine which cell the mouse pointer is currently over
    int cellX = mouseX / (800 / GRID_WIDTH);
    int cellY = mouseY / (600 / GRID_HEIGHT);

    if (cellX >= 0 && cellX < GRID_WIDTH && cellY >= 0 && cellY < GRID_HEIGHT) 
    {
        // Randomly choose a neighboring cell to activate for sand effect
        int randDirection = rand() % 4;
        int neighborX = cellX;
        int neighborY = cellY;

        switch (randDirection) 
        {
            case 0: // Left
                neighborX = (cellX > 0) ? cellX - 1 : cellX;
                break;
            case 1: // Right
                neighborX = (cellX < GRID_WIDTH - 1) ? cellX + 1 : cellX;
                break;
            case 2: // Up
                neighborY = (cellY > 0) ? cellY - 1 : cellY;
                break;
            case 3: // Down
                neighborY = (cellY < GRID_HEIGHT - 1) ? cellY + 1 : cellY;
                break;
        }

        // Determine color based on position relative to the grid
        float hue = std::abs(static_cast<float>(neighborX - GRID_WIDTH / 2)) / (GRID_WIDTH / 2) * 360.0f + hueTweak;
        float saturation = 1.0f;
        float value = 1.0f;

        // Convert HSV to RGB
        int r, g, b;
        HSVtoRGB(hue, saturation, value, r, g, b);

        // Assign RGB values to the neighboring cell
        cells[neighborX][neighborY].isActive = true;
        cells[neighborX][neighborY].color = { static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), 255 }; // RGBA, alpha is 255 (opaque)

        std::cout << "Random grain spawned at (" << neighborX << ", " << neighborY << ") with color ("
                  << r << ", " << g << ", " << b << ")" << std::endl;
    }
}

void Grid::update() 
{
    // Update grid
}

void Grid::render() 
{
    for (int i = 0; i < GRID_WIDTH; ++i) 
    {
        for (int j = 0; j < GRID_HEIGHT; ++j) 
        {
            if (cells[i][j].isActive) 
            {
                // Render cells with determined color
                SDL_Rect rect = { i * (800 / GRID_WIDTH), j * (600 / GRID_HEIGHT), 800 / GRID_WIDTH, 600 / GRID_HEIGHT };
                SDL_SetRenderDrawColor(renderer, cells[i][j].color.r, cells[i][j].color.g, cells[i][j].color.b, cells[i][j].color.a);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void Grid::HSVtoRGB(float h, float s, float v, int& r, int& g, int& b) 
{
    int i;
    float f, p, q, t;
    if (s == 0) 
    {
        // Achromatic (grey)
        r = g = b = static_cast<int>(v * 255.0f);
        return;
    }
    h /= 60.0f; // sector 0 to 5
    i = static_cast<int>(std::floor(h));
    f = h - i; // factorial part of h
    p = v * (1.0f - s);
    q = v * (1.0f - s * f);
    t = v * (1.0f - s * (1.0f - f));
    switch (i) 
    {
        case 0:
            r = static_cast<int>(v * 255.0f);
            g = static_cast<int>(t * 255.0f);
            b = static_cast<int>(p * 255.0f);
            break;
        case 1:
            r = static_cast<int>(q * 255.0f);
            g = static_cast<int>(v * 255.0f);
            b = static_cast<int>(p * 255.0f);
            break;
        case 2:
            r = static_cast<int>(p * 255.0f);
            g = static_cast<int>(v * 255.0f);
            b = static_cast<int>(t * 255.0f);
            break;
        case 3:
            r = static_cast<int>(p * 255.0f);
            g = static_cast<int>(q * 255.0f);
            b = static_cast<int>(v * 255.0f);
            break;
        case 4:
            r = static_cast<int>(t * 255.0f);
            g = static_cast<int>(p * 255.0f);
            b = static_cast<int>(v * 255.0f);
            break;
        default: // case 5:
            r = static_cast<int>(v * 255.0f);
            g = static_cast<int>(p * 255.0f);
            b = static_cast<int>(q * 255.0f);
            break;
    }
}

void Grid::setColorTweak(float hueTweak) 
{
    this->hueTweak = hueTweak;
}
