#include "/opt/homebrew/include/SDL2/SDL.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "display.h"
#include "vector.h"

//////////////////////////////////////////////////////////////
// declare a array of points/vectors
//////////////////////////////////////////////////////////////
const int NUMBER_OF_POINTS = 9 * 9 * 9; // 9 * 9 * 9 cube
vec3_t cube_points[NUMBER_OF_POINTS];
vec2_t projected_points[NUMBER_OF_POINTS];

float fov_factor = 640;
vec3_t camera_position = { .x = 0, .y = 0, .z = -5 };

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

    // starting loading array of vectors
    // from -1 to 1 , 9 * 9 * 9 cube
    int point_count = 0;

    for (float x = -1; x <= 1; x += 0.25) {
        for (float y = -1; y <= 1; y += 0.25) {
            for (float z = -1; z <= 1; z += 0.25) {
                vec3_t new_point = { .x = x, .y = y, .z = z };
                cube_points[point_count++] = new_point;
            }
        }
    }
    
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

vec2_t project(vec3_t point) {
    vec2_t projected_point = {
        .x = (fov_factor * point.x) / point.z,
        .y = (fov_factor * point.y) / point.z
    };
    return projected_point;
}

void update(void) {
    for (int i = 0; i < NUMBER_OF_POINTS; i++) {
        vec3_t point = cube_points[i];
        // project the current point
        point.z -= camera_position.z;
        vec2_t projected_point = project(point);
        
        projected_points[i] = projected_point;
    }
    
}

void render(void) {
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    // SDL_RenderClear(renderer);

    //draw_pixel(20, 20, 0xFFFFF00);
    draw_grid();
    //draw_rectangle(300, 200, 300, 150, 0xFFFF00FF);

    // loop all projected values and render em
    for (int i = 0; i < NUMBER_OF_POINTS; i++) {
        vec2_t projected_point = projected_points[i];
        draw_rectangle(
            projected_point.x + (window_width / 2),
            projected_point.y + (window_height / 2),
            1,
            1,
            0xFFFFFF00
        );
    }
    

    render_color_buffer();
    clear_color_buffer(0xFF000000);
    
    SDL_RenderPresent(renderer);
}

int main(void) {
    //create sdl window
    isRunning = initialize_window();

    //vec3_t myvec = { 2.0, 3.0, -4.5 };

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