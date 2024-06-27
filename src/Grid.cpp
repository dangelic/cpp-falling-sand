#include "../include/Grid.h"
#include <iostream>
#include <cstdlib> // For rand()

Grid::Grid(SDL_Renderer* renderer) : renderer(renderer) {
    // Initialize grid cells
    for (int i = 0; i < GRID_WIDTH; ++i) {
        for (int j = 0; j < GRID_HEIGHT; ++j) {
            cells[i][j].isActive = false;
        }
    }
}

Grid::~Grid() {
    // Cleanup if needed
}

void Grid::handleClick(int mouseX, int mouseY) {
    // Determine which cell was clicked based on mouse coordinates
    int cellX = mouseX / (800 / GRID_WIDTH);
    int cellY = mouseY / (600 / GRID_HEIGHT);

    if (cellX >= 0 && cellX < GRID_WIDTH && cellY >= 0 && cellY < GRID_HEIGHT) {
        cells[cellX][cellY].isActive = !cells[cellX][cellY].isActive;
        std::cout << "Cell (" << cellX << ", " << cellY << ") state changed to " << (cells[cellX][cellY].isActive ? "active" : "inactive") << std::endl;
    }
}

void Grid::spawnRandomGrain(int mouseX, int mouseY) {
    int cellX = mouseX / (800 / GRID_WIDTH);
    int cellY = mouseY / (600 / GRID_HEIGHT);

    if (cellX >= 0 && cellX < GRID_WIDTH && cellY >= 0 && cellY < GRID_HEIGHT) {
        // Randomly choose a neighboring cell to activate for sand effect
        int randDirection = rand() % 4;
        int neighborX = cellX;
        int neighborY = cellY;
        
        switch (randDirection) {
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

        cells[neighborX][neighborY].isActive = true;
        std::cout << "Random grain spawned at (" << neighborX << ", " << neighborY << ")" << std::endl;
    }
}

void Grid::update() {
    // Update grid
}

void Grid::render() {
    // Render the grid
    for (int i = 0; i < GRID_WIDTH; ++i) {
        for (int j = 0; j < GRID_HEIGHT; ++j) {
            if (cells[i][j].isActive) {
                SDL_Rect rect = { i * (800 / GRID_WIDTH), j * (600 / GRID_HEIGHT), 800 / GRID_WIDTH, 600 / GRID_HEIGHT };
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}