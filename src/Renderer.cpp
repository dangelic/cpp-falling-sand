#include "../include/Renderer.h"

Renderer::Renderer() : window(nullptr), renderer(nullptr) {}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow("SDL2 Canvas",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              800, 600,
                              SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Log("Window could not be created! SDL_Error: %s", SDL_GetError());
        SDL_Quit();
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Renderer could not be created! SDL_Error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // Initialize canvas to false (empty)
    for (int x = 0; x < 80; ++x) {
        for (int y = 0; y < 60; ++y) {
            canvas[x][y] = false;
        }
    }
}

void Renderer::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
    SDL_RenderClear(renderer);

    drawCanvas();

    SDL_RenderPresent(renderer);
}

void Renderer::handleEvent(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = e.button.x / 10; // Assuming each pixel is 10x10
        int mouseY = e.button.y / 10;

        if (mouseX >= 0 && mouseX < 80 &&
            mouseY >= 0 && mouseY < 60) {
            // Toggle the canvas state at the clicked pixel
            canvas[mouseX][mouseY] = !canvas[mouseX][mouseY];
        }
    }
}

void Renderer::drawCanvas() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black for filled pixels

    for (int x = 0; x < 80; ++x) {
        for (int y = 0; y < 60; ++y) {
            if (canvas[x][y]) {
                SDL_Rect pixelRect = { x * 10, y * 10, 10, 10 }; // Each pixel is 10x10
                SDL_RenderFillRect(renderer, &pixelRect);
            }
        }
    }
}