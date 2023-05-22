#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <cglm/mat4.h>
#include <cglm/vec3.h>
#include <cglm/cam.h>


void camera_set_view_lookat(float cam_x, float cam_y, float cam_z, float lookat_x, float lookat_y, float lookat_z);
mat4* camera_get_projection_matrix();
mat4* camera_get_view_matrix();
void camera_set_projection_ortho(float left, float right, float bottom, float top, float near, float far);
void camera_set_projection_perspective(float fov, float aspect_ratio, float near, float far);

#endif