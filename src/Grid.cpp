#include "../include/Grid.h"
#include <iostream>

Grid::Grid(SDL_Renderer* renderer) : renderer(renderer) {
    // Initialize grid cells
    for (int i = 0; i < GRID_WIDTH; ++i) {
        for (int j = 0; j < GRID_HEIGHT; ++j) {
            cells[i][j].isActive = false;
        }
    }
}

Grid::~Grid() {
    // Cleanup ?
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

void Grid::update() {
    // Update grid state
}

void Grid::render() {
    // Render grid
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