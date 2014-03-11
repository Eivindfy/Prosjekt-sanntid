//#include "global_variables.h"

struct ORDER_QUEUE{
  int floor;
  int direction;
  struct QUEUE* next;
}

struct ORDER_QUEUE* root;


void order_queue_initialize();

void order_queue_insert(int floor,int direction);

void order_queue_destroy();

struct order_queue order_queue_pop();
