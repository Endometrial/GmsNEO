
#include <baphomet/queue.h>
#include <baphomet/input.h>

DATA {
  int number;
};

// self. is ((Object*)data)->

CREATE (void* data) {

  number = -222;
  fprintf(stderr, "[%u] This is running and is also cats!\n",self.id);

  return 0;
}

STEP (void* data, double delta_time) {
  if (key_press(VK_SPACE)) {
    fprintf(stderr, "[%u] This is inside the step event also the number is %u!\n",self.id,number);
  }
  return 0;
}

DRAW () {

}

// Default and wouldnt be shown
// CLEAN (void* data) {
//  free((((Object*)data)->data));
//}

DESTROY (void* data) {

}
