#ifndef BAPHOMET_QUEUE_H
#define BAPHOMET_QUEUE_H

/*
	queue.h
	Created: xxxx-xx-xx
	Description:
		queue.h is a loose implimentation of a somewhat hodgepodge system for
    executing 'object' scripts in order. The idea is that every available object
    will be created and listed in a large include file which "room objects"
    directly running out of the mainloop can pull from to make interesting
    things happen :3. I think it may be a good idea to have a python
    preprocessor make this happen? I could write it all manually by defining
    name_event_xxx functions with an object definition at the end of the file
    all included in said larger include; However, that is like atleast 5 seconds
    of work and like... come on.. thats unacceptable. NOTE: Global variables
    are shared among object instances. Only the 'malloc'ed data is local
*/

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>


// AND is faster than a comparison?
#define EVENT_CREATE  0x0 << 0  // 00001
#define EVENT_STEP    0x1 << 1  // 00010
#define EVENT_DRAW    0x2 << 2  // 00100
#define EVENT_CLEAN   0x3 << 3  // 01000
#define EVENT_DESTROY 0x4 << 4  // 10000

typedef struct {
  int id; // Assigned in numerical order
  void* oid;
  int (*event_create)(void* object);
  int (*event_step)(void* object, double delta_time);
  int (*event_draw)(void* object, double delta_time);
  int (*event_clean)(void* object);
  int (*event_destroy)(void* object);
	void*  data;
} Object;

Object** debug_return_queue();

Object* queue_get_objects_by_oid(); // First entry is number of objects?
Object queue_get_object();
int queue_set_object();
int queue_add_object(Object object);
int queue_add_objects(Object object, int number);
int queue_duplicate_object();
int queue_remove_object_by_oid();
int queue_remove_object(int id);
int queue_execute_event(int event_flag, double delta_time);
int queue_execute_event_by_id(int id, int event_flag, double delta_time);
int queue_cleanup();

// ADD DEFAULT OBJECT EVENT FUNCTIONS HERE TO RUN ON NULL

#endif
