#include <SDL.h>
#include "include/Renderer.h"

int main(int argc, char* argv[]) {
    Renderer renderer;

    renderer.initialize();

    bool quit = false;

    SDL_Event e;

    // Main loop
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEMOTION) {
                renderer.handleEvent(e); // Pass the event to the renderer
            }
        }

        // Render scene
        renderer.render();
    }

    return 0;
}
