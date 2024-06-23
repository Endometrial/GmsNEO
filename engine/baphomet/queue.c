#include <baphomet/queue.h>

Object** QUEUE;
int QUEUE_LENGTH = 0;

Object** debug_return_queue() {
  return QUEUE;
}

int queue_add_object(Object object) {
  Object* obj_ptr = malloc(sizeof(Object));
  (*obj_ptr) = object;
  for (int v=0; v<QUEUE_LENGTH; v++) {
    if (!QUEUE[v])
      QUEUE[v] = obj_ptr;
      QUEUE[v]->id = v;
      return v;
  }

  QUEUE_LENGTH++;
  QUEUE = (QUEUE_LENGTH==1) ? malloc(QUEUE_LENGTH * sizeof(Object*)) : realloc(QUEUE, QUEUE_LENGTH * sizeof(Object*));

  QUEUE[QUEUE_LENGTH-1] = obj_ptr;
  QUEUE[QUEUE_LENGTH-1]->id = QUEUE_LENGTH-1;
  return QUEUE_LENGTH-1;
}

int queue_add_objects(Object object, int number) {
  int new_length;

  if (number<1) {
    fprintf(stderr, "ERROR: Creating less than 1 object?\n");
    return 1;
  }

  // Fill in any empty spots in the queue
  new_length = QUEUE_LENGTH+number; // Hypothetical maximum new size
  register int v;
  for (;v < QUEUE_LENGTH;v++) {
    if (QUEUE[v] == NULL) {
      Object* obj_ptr = malloc(sizeof(Object));
      (*obj_ptr) = object;
      QUEUE[v] = obj_ptr;
      QUEUE[v]->id = v;
      new_length--;
    }
  }

  // Resize the queue (or just return if not required)
  if (new_length < QUEUE_LENGTH)
    return 0;
  QUEUE = (QUEUE_LENGTH) ? realloc(QUEUE, new_length * sizeof(Object*)) : malloc(new_length * sizeof(Object*));

  // Add each additional object
  for (;v < new_length;v++) {
    Object* obj_ptr = malloc(sizeof(Object));
    (*obj_ptr) = object;
    QUEUE[v] = obj_ptr;
    QUEUE[v]->id = v;
  }
  QUEUE_LENGTH = new_length;

  return 0;
}

int queue_remove_object(int id) {
  if ((id>=QUEUE_LENGTH) || (QUEUE[id] == NULL))
    fprintf(stderr, "ERROR: Unable to locate object id [%u]\n", id);
  //queue_execute_event_by_id(id, EVENT_CLEAN, -1); PUT BACK LATER
  //queue_execute_event_by_id(id, EVENT_DESTROY, -1);
  QUEUE[id] = NULL;
  if (id == (QUEUE_LENGTH-1))
    QUEUE_LENGTH--;
    if (QUEUE_LENGTH) {
      QUEUE = realloc(QUEUE, QUEUE_LENGTH*sizeof(Object*));
    } else {free(QUEUE);}
  return 0;
}

int queue_cleanup() {
  for (int i=0; i<QUEUE_LENGTH; i++) {
    if (QUEUE[i] != NULL) {
      queue_execute_event_by_id(i, EVENT_CLEAN, -1);
      //queue_execute_event_by_id(i, EVENT_DESTROY, -1);
      free(QUEUE[i]);
    }
  }
  free(QUEUE);
  QUEUE_LENGTH = 0;
  return 0;
}

int queue_execute_event(int event_flag, double delta_time) {
  for (int i=0; i<QUEUE_LENGTH; i++) {
    if (QUEUE[i])
      queue_execute_event_by_id(i, event_flag, delta_time);
  }
}

int queue_execute_event_by_id(int id, int event_flag, double delta_time) {
  switch(event_flag) {
    case EVENT_CREATE:
      QUEUE[id]->event_create(QUEUE[id]);
      break;
    case EVENT_STEP:
      QUEUE[id]->event_step(QUEUE[id], delta_time);
      break;
    case EVENT_DRAW:
      QUEUE[id]->event_draw(QUEUE[id], delta_time);
      break;
    case EVENT_CLEAN:
      QUEUE[id]->event_clean(QUEUE[id]);
      break;
    case EVENT_DESTROY:
      QUEUE[id]->event_destroy(QUEUE[id]);
      break;
    default:
      fprintf(stderr, "ERROR: Event flag [%u] executed on object [%u] doesn't exist!\n", event_flag, id);
      return 1;
  }
  return 0;
}

Object* queue_get_objects_by_oid() {} // First entry is number of objects?
Object queue_get_object() {}
int queue_set_object() {}
int queue_duplicate_object(int id) {}
int queue_remove_object_by_oid() {}
int queue_execute_event_by_oid(int event_flag, int id) {}
