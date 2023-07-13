#include <baphomet/camera.h>

mat4 projection_matrix;
mat4 view_matrix;

mat4* camera_get_projection_matrix() {
	return &projection_matrix;
}

mat4* camera_get_view_matrix() {
	return &view_matrix;
}

void camera_set_view_lookat(float cam_x, float cam_y, float cam_z, 
	float lookat_x, float lookat_y, float lookat_z) {
	vec3 up = {0.0f, 1.0f, 0.0f};
	vec3 cam_pos = {cam_x, cam_y, cam_z};
	vec3 cam_target = {lookat_x, lookat_y, lookat_z};
	glm_lookat(cam_pos, cam_target, up, view_matrix);
}

void camera_set_projection_ortho(float left, float right, 
	float bottom, float top, float near, float far) {
	glm_ortho(left, right, bottom, top, near, far, projection_matrix);
}

void camera_set_projection_perspective(float fov, 
	float aspect_ratio, float near, float far) {
	glm_perspective(fov, aspect_ratio, near, far, projection_matrix);
}