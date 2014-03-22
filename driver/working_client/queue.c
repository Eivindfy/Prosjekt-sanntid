#include <stdio.h>
#include "queue.h"
#include <stdlib.h>
//#include "global_variables.h"



void order_queue_initialize(){
 
 root =  (struct ORDER_QUEUE*) malloc(sizeof(struct ORDER_QUEUE));
 root->next=NULL;
 root->floor=-1;
 root->direction=0;
  
}

void order_queue_insert(int floor,int direction){
  struct ORDER_QUEUE* iterator = root;
  struct ORDER_QUEUE* it_next = root->next;
  while((it_next!=NULL)){
    
    if(it_next->floor==floor && it_next->direction==direction){
      return;
    }
    
    iterator=it_next;
    it_next=it_next->next;
    
  }

  iterator->next = (struct ORDER_QUEUE*) malloc(sizeof(struct ORDER_QUEUE));
  iterator->next->floor=floor;
  iterator->next->direction=direction;
  iterator->next->next=NULL;

}

void order_queue_destroy(){

  struct ORDER_QUEUE* iterator = root;
  struct ORDER_QUEUE* it_next = root->next;
  
  free(iterator);
  
  while(it_next!=NULL){
    
    iterator=it_next;
    it_next=it_next->next;
    free(iterator);
    
  }
  root=NULL;

}

struct ORDER_QUEUE order_queue_pop(){
  struct ORDER_QUEUE temp;
  	if(root->next!=NULL){
  		struct ORDER_QUEUE* popped = root->next;
  
  		temp.direction = popped->direction;
  		temp.floor = popped->floor;
  		temp.next=NULL;
  
  		root->next=popped->next;
  		free(popped);
  	}
  	else{
		temp.next=NULL;
		temp.floor=-1;
		temp.direction=0;
  	}

  
  return temp;
}

int order_queue_isempty(){	
		if(root->next==NULL){
			return 1;
		}
		else{
			return 0;
		}
}
