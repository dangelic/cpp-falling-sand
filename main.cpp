#include <SDL.h>
#include "include/Renderer.h"

int main(int argc, char* argv[]) {
    Renderer renderer;

    // Initialize SDL and create window
    renderer.initialize();

    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

    // Main loop
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Render scene
        renderer.render();
    }

    return 0;
}
