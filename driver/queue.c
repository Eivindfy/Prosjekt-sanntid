#include <stdio.h>
#include "queue.h"
#include <stdlib.h>
//#include "global_variables.h"



void order_queue_initialize(){
 
 root = (struct order_queue*) malloc(sizeof(struct order_queue));
 root->next=NULL;
 root->floor=-1;
 root->direction=0;
  
}

void order_queue_insert(int floor,int direction){
if(root->floor==-1){
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
 else{
 	perror("order_queue not initialized\n");
 }
}

void order_queue_destroy(){
if(root->floor==-1){
  struct order_queue* iterator = root;
  struct order_queue* it_next = root->next;
  
  free(iterator);
  
  while((it_next!=NULL){
    
    iterator=it_next;
    it_next=it_next->next;
    free(iterator);
    
  }
 }
 else{
 	perror("order_queue not initialized\n");
 }
}

struct order_queue order_queue_pop(){
  struct order_queue temp;
  if(root->floor==-1){
  	if(root->next!=NULL){
  		struct order_queue* popped = root->next;
  
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
  else{
  	perror("order_queue not initialized\n");
  }
  
  return temp;
}

int order_queue_isempty(){
	if(root->floor==-1){	
		if(root->next==NULL){
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		perror("order_queue not initialized\n");
		return 1;
  	}

}
