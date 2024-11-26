#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    float x;
    float y;
} vec2_t;

typedef struct {
    float x;
    float y;
    float z;
} vec3_t;

//TODO: add functions to manipulate 2d and 3d vectors
vec3_t vec3_rotation_x(vec3_t v, float angle);
vec3_t vec3_rotation_y(vec3_t v, float angle);
vec3_t vec3_rotation_z(vec3_t v, float angle);

#endif