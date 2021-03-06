#ifndef QUEUE_H
#define QUEUE_H

//#include "global_variables.h"

struct ORDER_QUEUE{
  int floor;
  int direction;
  struct ORDER_QUEUE* next;
};

struct ORDER_QUEUE* root;

void order_queue_remove(int floor,int direction);

void order_queue_initialize();

void order_queue_insert(int floor,int direction);

void order_queue_destroy();

struct ORDER_QUEUE order_queue_pop();

struct ORDER_QUEUE order_queue_peek();

int order_queue_isempty();

#endif
