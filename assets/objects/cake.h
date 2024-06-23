
#include <baphomet/queue.h>
#include <baphomet/input.h>
#include <baphomet/audio.h>
#include <math.h>

struct cake_data {
  int number;
  Sound music;
  int pressed;
  int pressed2;
  int rainbow;
};

int cake_create(void* data) {
  (((Object*)data)->data) = malloc(sizeof(struct cake_data) + sizeof(void*));
  ((struct cake_data*)(((Object*)data)->data))->number = -222;

  ((struct cake_data*)(((Object*)data)->data))->music = asset_load_sound("assets/audio/the-legendary-hero.ogg");

  ((struct cake_data*)(((Object*)data)->data))->rainbow = 0;

  fprintf(stderr, "[%u] This iss running and is also cake!\n",((Object*)data)->id);
  shader_set_uniform_vec4(draw_get_shader(), "tri_color", 1.0f, 1.0f, 1.0f, 1.0f);
  return 0;
}

int cake_step(void* data, double delta_time) {
  if (!key_press(VK_SPACE))
    ((struct cake_data*)(((Object*)data)->data))->pressed = 0;
  if ((key_press(VK_SPACE)) && (((struct cake_data*)(((Object*)data)->data))->pressed == 0)) {
    fprintf(stderr, "Playing sound\n");
    audio_sound_play(((struct cake_data*)(((Object*)data)->data))->music, 1);
    ((struct cake_data*)(((Object*)data)->data))->pressed = 1;
    ((struct cake_data*)(((Object*)data)->data))->rainbow = 1;
  }

  if (!key_press(VK_ENTER))
    ((struct cake_data*)(((Object*)data)->data))->pressed2 = 0;
  if ((key_press(VK_ENTER)) && (((struct cake_data*)(((Object*)data)->data))->pressed2 == 0)) {
    fprintf(stderr, "Pausing sound\n");
    audio_sound_pause(((struct cake_data*)(((Object*)data)->data))->music);
    ((struct cake_data*)(((Object*)data)->data))->pressed2 = 1;
    ((struct cake_data*)(((Object*)data)->data))->rainbow = 0;
    shader_set_uniform_vec4(draw_get_shader(), "tri_color", 1.0f, 1.0f, 1.0f, 1.0f);
  }

  if (((struct cake_data*)(((Object*)data)->data))->rainbow) {
    shader_set_uniform_vec4(draw_get_shader(), "tri_color", (sin((glfwGetTime()+1.224f)*8.0f)+1.0f)/1.5f, (cos((glfwGetTime()+5.123f)*4.0f)+1.0f)/1.5f, (sin((glfwGetTime()+3.942f)*16.0f)+1.0f)/1.5f, 1.0f);
  }

  return 0;
}

int cake_clean(void* data) {
  free((((Object*)data)->data));
}

Object cake = {0, NULL, &cake_create, &cake_step, NULL, &cake_clean, NULL, NULL};
