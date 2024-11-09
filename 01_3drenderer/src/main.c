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

void setup(void) {

}

void process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
            isRunning = false;
        break;
    }
}

void update(void) {
    
}

void render(void) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}

int main(void) {
    //create sdl window
    isRunning = initialize_window();

    setup();
    while (isRunning)
    {
        process_input();
        update();
        render();
    }
    
    return 0;
}