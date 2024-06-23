
#include <baphomet/queue.h>
#include <baphomet/input.h>
#include <math.h>

struct cats_data {
  int number;
  unsigned int VAO;
  Texture image;
  Mesh rect;
};

int cats_create(void* data) {
  (((Object*)data)->data) = malloc(sizeof(struct cats_data) + sizeof(void*));
  ((struct cats_data*)(((Object*)data)->data))->number = -222;

  //camera_set_projection_ortho(-40.0f, 40.0f, -30.0f, 30.0f, 0.001f, 10000.0f);
  camera_set_projection_perspective(-5.0f, 2.0f, 0.00001f, 1000000.0f);
	camera_set_view_lookat(0.0f, 0.0f, -50.0f, 0.0f, 0.0f, 0.0f);

  fprintf(stderr, "[%u] This iss running and is also cats!\n",((Object*)data)->id);

  ((struct cats_data*)(((Object*)data)->data))->image = asset_load_texture("baphomet.png");
  draw_set_texture(((struct cats_data*)(((Object*)data)->data))->image);
  ((struct cats_data*)(((Object*)data)->data))->rect = mesh_generate_rect(1.0f, 1.0f);
  //((struct cats_data*)(((Object*)data)->data))->rect = mesh_generate_cube(1.0f, 1.0f, 1.0f);

  float vertex[] = {
    -0.5f,  -0.5f,  0.0f,
     0.5f,  -0.5f,  0.0f,
     0.0f,   0.5f,  0.0f
  };

  /*
  unsigned int VBO;
  glGenBuffers(1, &VBO);

  glGenVertexArrays(1, &(((struct cats_data*)(((Object*)data)->data))->VAO));
  glBindVertexArray(((struct cats_data*)(((Object*)data)->data))->VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
  glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE,3*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0); */

  return 0;
}

int cats_step(void* data, double delta_time) {
  glUseProgram(draw_get_shader().program);
  draw_set_texture(((struct cats_data*)(((Object*)data)->data))->image);
  draw_mesh_ext(((struct cats_data*)(((Object*)data)->data))->rect, 0.0f, 0.0f, sin(glfwGetTime()) + 2.0f, 20.0f,20.0f,20.0f, sin(glfwGetTime())*6.28f, cos(glfwGetTime())*6.28f, 0.0f);
  //draw_mesh_ext(((struct cats_data*)(((Object*)data)->data))->rect, 0.0f, 0.0f, 0.0f, 20.0f,20.0f,20.0f, 3.14f, 0.0f, 0.0f);
  /*glBindVertexArray(((struct cats_data*)(((Object*)data)->data))->VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);*/
  return 0;
}

int cats_clean(void* data) {
  free((((Object*)data)->data));
}

Object cats = {0, NULL, &cats_create, &cats_step, NULL, &cats_clean, NULL, NULL};
