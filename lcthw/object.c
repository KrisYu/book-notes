#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "object.h"
#include <assert.h>


void Object_destroy(void *self) {
  Object *obj = self;

  if (obj) {
    if (obj->description) free(obj->description);
    free(obj);
  }
}

void Object_describe(void *self) {
  Object *obj = self;
  printf("%s.\n",obj->description );
}


int Object_init(void *self){
  // do really nothing
  return 1;
}

void *Object_move(void *self, Direction direction){
  printf("You can't go that direction\n" );
  return NULL;
}

int Object_attack(void *self, int damage){
  printf("You can't attack that\n" );
  return 0;
}

void *Object_new(size_t size, Object proto, char *description){
  // set up the default functions in case they aren't set
  if (!proto.init) proto.init = Object_init;
  if (!proto.describe) proto.describe = Object_describe;
  if (!proto.destroy) proto.destroy = Object_destroy;
  if (!proto.attack) proto.attack = Object_attack;
  if (!proto.move) proto.move = Object_move;

  // this seems werid, but we can make a struct of one size.
  // then point a diffrent pointer at it to 'cast' it
  Object *e1 = calloc(1, size);
  *e1 = proto;

  //copy the description over
  e1->description = strdup(description);

  // initialize it with whatever init we were given
  if (!e1->init(e1)) {
    // looks like it didn't initialize properly
    e1->destroy(e1);
    return NULL;
  } else {
    // all done, we made an object of any type.
    return e1;
  }

}
