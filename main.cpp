#include <SDL.h>
#include "include/Renderer.h"
#include "include/Grid.h"
#include "include/Animation.h"

int main(int argc, char* argv[]) {
    // Initialize SDL and create window
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          800, 600,
                                          SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Log("Window could not be created! SDL_Error: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Renderer could not be created! SDL_Error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    Renderer sdlRenderer(renderer); 
    Grid grid(renderer);
    Animation animation(&grid); 

    // Main loop flag
    bool quit = false;
    bool mouseHeld = false;
    int mouseX, mouseY;

    // Event handler
    SDL_Event e;

    // Timer for animation updates
    Uint32 lastUpdateTime = SDL_GetTicks();
    Uint32 animationDelay = 100; // ms

    // Main loop
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            // Handle mouse events
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                mouseHeld = true;
                SDL_GetMouseState(&mouseX, &mouseY);
                grid.handleClick(mouseX, mouseY);
            }
            if (e.type == SDL_MOUSEBUTTONUP) {
                mouseHeld = false;
            }
            if (e.type == SDL_MOUSEMOTION && mouseHeld) {
                SDL_GetMouseState(&mouseX, &mouseY);
            }
        }

        // Spawn grains if mouse is held down
        if (mouseHeld) {
            grid.spawnRandomGrain(mouseX, mouseY);
        }

        // Update grid state with animation logic if enough time has passed
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastUpdateTime >= animationDelay) {
            animation.update();
            lastUpdateTime = currentTime;
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Render grid
        grid.render();

        // Update screen
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}