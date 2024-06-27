#ifndef ANIMATION_H
#define ANIMATION_H

#include "Grid.h"

class Animation {
public:
    Animation(Grid* grid);
    void update();
private:
    Grid* grid;
};

#endif // ANIMATION_H