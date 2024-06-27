#include "../include/Animation.h"

Animation::Animation(Grid* grid) : grid(grid) {}

void Animation::update() {
    for (int i = 0; i < GRID_WIDTH; ++i) {
        // Traverse from bottom to top to prevent overwriting
        for (int j = GRID_HEIGHT - 1; j > 0; --j) {
            if (grid->cells[i][j].isActive == false && grid->cells[i][j-1].isActive == true) {
                grid->cells[i][j].isActive = true;
                grid->cells[i][j-1].isActive = false;
            }
        }
    }
}