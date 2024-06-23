
#include <baphomet/queue.h>
#include <baphomet/input.h>
#include <baphomet/audio.h>

DATA {
  Sound music;
  int pressed;
  int pressed2;
}; // perhaps all non function variables without the global keyword go here?

CREATE(void* DATA) {
  music = asset_load_sound("/home/luna/file/ogg/Mocks_You.mp3");
  fprintf(stderr, "[%u] This is running and is also cake!\n",self.id);
  return 0;
}

STEP(void* DATA, double delta_time) {
  if (!key_press(VK_SPACE))
    pressed = 0;
  if ((key_press(VK_SPACE)) && (pressed == 0)) {
    fprintf(stderr, "Playing sound\n");
    audio_sound_play(music, 1);
    pressed = 1;
  }

  if (!key_press(VK_ENTER))
    pressed2 = 0;
  if ((key_press(VK_ENTER)) && (pressed2 == 0)) {
    fprintf(stderr, "Pausing sound\n");
    audio_sound_pause(music);
    pressed2 = 1;
  }

  return 0;
}
