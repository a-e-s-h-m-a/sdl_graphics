#include "/opt/homebrew/include/SDL2/SDL.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "display.h"

bool isRunning = false;

void setup(void) {
    //allocating required memory in bytes to the color buffer
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);
    if(!color_buffer) {
        fprintf(stderr, "Error creating color buffer. \n");
    }
    //create the sdl texture that use to display color
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );
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

    draw_grid();
    draw_rectangle(300, 200, 300, 150, 0xFFFF00FF);
    render_color_buffer();
    clear_color_buffer(0xFF000000);
    
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
    
    destroy_window();
    return 0;
}