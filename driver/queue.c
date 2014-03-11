#include <stdio>
#include "queue.h"
//#include "global_variables.h"



void order_queue_initialize(){
 
 root = (struct order_queue*) malloc(sizeof(struct order_queue));
 root->next=NULL;
 root->floor=-1;
 root->direction=0;
  
}

void order_queue_insert(int floor,int direction){
  struct order_queue* iterator = root;
  struct order_queue* it_next = root->next;
  while((it_next!=NULL){
    
    if(it_next->.floor==floor && it_next->direction==direction){
      return;
    }
    
    iterator=next;
    it_next=it_next->next;
    
  }
  
  
  iterator->next = (struct order_queue*) malloc(sizeof(struct order_queue));
  iterator->next->floor=floor;
  iterator->next->direction=direction;
  iterator->next->next=NULL;
}

void order_queue_destroy(){
  struct order_queue* iterator = root;
  struct order_queue* it_next = root->next;
  
  free(iterator);
  
  while((it_next!=NULL){
    
    iterator=it_next;
    it_next=it_next->next;
    free(iterator);
    
  }
}

struct order_queue order_queue_pop(){
  struct order_queue temp;
  struct order_queue* popped = root->next;
  
  temp.direction = popped->direction;
  temp.floor = popped->floor;
  temp.next=NULL;
  
  root->next=popped->next;
  free(popped);
  
  return temp;
}
