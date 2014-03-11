//#include "global_variables.h"

struct ORDER_QUEUE{
  int value;
  int direction;
  struct QUEUE* next;
}

struct ORDER_QUEUE order_queue;
