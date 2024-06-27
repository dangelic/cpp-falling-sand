#include "../include/Animation.h"

Animation::Animation(Grid* grid) : grid(grid) {}

void Animation::update() {
    // Iterate from bottom to top to handle falling
    for (int j = GRID_HEIGHT - 2; j >= 0; --j) {
        for (int i = 0; i < GRID_WIDTH; ++i) {
            if (grid->cells[i][j].isActive) {
                int fallSpeed = calculateFallSpeed(j);

                // Check if the cell directly below is empty
                if (j + 1 < GRID_HEIGHT && !grid->cells[i][j + 1].isActive) {
                    grid->cells[i][j].isActive = false;
                    grid->cells[i][j + 1].isActive = true;
                } else {
                    // Attempt to move diagonally left or right
                    bool moved = false;
                    if (i > 0 && j + 1 < GRID_HEIGHT && !grid->cells[i - 1][j + 1].isActive) {
                        grid->cells[i][j].isActive = false;
                        grid->cells[i - 1][j + 1].isActive = true;
                        moved = true;
                    } else if (i < GRID_WIDTH - 1 && j + 1 < GRID_HEIGHT && !grid->cells[i + 1][j + 1].isActive) {
                        grid->cells[i][j].isActive = false;
                        grid->cells[i + 1][j + 1].isActive = true;
                        moved = true;
                    }
                }
            }
        }
    }
}

int Animation::calculateFallSpeed(int depth) {
    // Example: linearly increase fall speed with depth
    return 1 + (depth / 10); // This makes grains fall faster the deeper they are
}
