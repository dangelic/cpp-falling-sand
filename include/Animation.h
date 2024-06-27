#ifndef ANIMATION_H
#define ANIMATION_H

#include "Grid.h"

class Animation {
public:
    Animation(Grid* grid);
    void update();
private:
    Grid* grid;
    int calculateFallSpeed(int depth); // Function to calculate fall speed based on depth
};

#endif // ANIMATION_H