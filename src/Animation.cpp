#include "../include/Animation.h"

Animation::Animation(Grid* grid) : grid(grid) {}

void Animation::update() {
    // Iterate from bottom to top to handle falling
    for (int j = GRID_HEIGHT - 2; j >= 0; --j) {
        for (int i = 0; i < GRID_WIDTH; ++i) {
            if (grid->cells[i][j].isActive && !grid->cells[i][j + 1].isActive) {
                // Calculate fall speed based on depth
                int fallSpeed = calculateFallSpeed(j);

                // Move grain down if the cell below is empty
                if (j + fallSpeed < GRID_HEIGHT && !grid->cells[i][j + fallSpeed].isActive) {
                    grid->cells[i][j].isActive = false;
                    grid->cells[i][j + fallSpeed].isActive = true;
                } else {
                    // Move grain as far as possible if it can't fall the full distance
                    for (int k = 1; k <= fallSpeed; ++k) {
                        if (j + k < GRID_HEIGHT && !grid->cells[i][j + k].isActive) {
                            grid->cells[i][j].isActive = false;
                            grid->cells[i][j + k].isActive = true;
                            break;
                        }
                    }
                }
            }
        }
    }
}

int Animation::calculateFallSpeed(int depth) {
    // Linearly increase fall speed with depth
    return 1 + (depth / 10); // This makes grains fall faster the deeper they are
}