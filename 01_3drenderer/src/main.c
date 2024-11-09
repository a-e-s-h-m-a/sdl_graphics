#include "/opt/homebrew/include/SDL2/SDL.h"
#include <stdio.h>
#include <stdbool.h>

bool isRunning = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)  {
        fprintf(stderr, "Error initializing SDL \n");
        return false;
    }
    // sdl window
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_BORDERLESS
    );
    if(!window) {
        fprintf(stderr, "Error creating SDL window. \n");
        return false;
    }

    // sdl renderer
    renderer = SDL_CreateRenderer(
        window,
        -1, // default
        0
    );
    if(!renderer) {
        fprintf(stderr, "Error creating SDL renderer. \n");
        return false;
    }

    return true;
}

int main(void) {
    //create sdl window
    isRunning = initialize_window();

    return 0;
}