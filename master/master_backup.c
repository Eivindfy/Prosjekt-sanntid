#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "master_backup"
#include "global_variables.h"




int write_backup_master(char* filename, int* elevator_status, int* elevator_floor, struct ORDER_QUEUE* root){

    FILE* fp;
    fp = fopen(filename, "w");
    
    if (fp == NULL) {
      printf("Error: couldn't open %s for writing in retreive_backup_master. \n",filename);
      return -1;
    }
    
    fclose(fp);
    
    
    fp = fopen(filename,"a");
    
	fprintf(fp,"$#");
	for(int i = 0 ; i < N_ELEVATORS ; i++){
    	fprintf(fp,"%i#%i#",elevator_status[i],elevator_floor[i]);
    }
    fprintf(fp,"$#");
    
    struct ORDER_QUEUE* temp = root;
    
    //ikkje modulaert, men dette er pga c ikkje er objektorientert, order_queue er ein pseudo-klasse. Les queue.h
    while(temp->next != NULL){
    	temp=temp->next;
    	fprintf(fp,"%i#%i#",temp->floor,temp->direction);
    }
    fclose(fp);
   
    return 1;
}




int retrieve_backup_master(char* filename, int* elevator_status, int* elevator_floor, struct ORDER_QUEUE* root){

  FILE *fp;
  char buffer[1024];
  char* variable_string;
  variable_string= NULL;
   
  fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error: couldn't open %s for reading in retreive_backup_master.\n", filename);
    return -1;
  }
  
  
  
  if(fgets(buffer, sizeof(buffer), fp)!=NULL){
  
    variable_string = strtok( buffer, "#");
    //printf("første variable_string: %s      \n",variable_string);
    if(variable_string[0]!='$'){
    	printf("Error: error in backup file %s when retreiving backup\n", filename); 
    }
    
    
    int j = 0;
    while(variable_string!=NULL){
    	variable_string = strtok( NULL, "#");
    	if(variable_string[0]=='$'){
    		break;
    	}
    	elevator_status[j]=atoi(variable_string);
    	
    	
    	variable_string = strtok( NULL, "#");
    	if(variable_string[0]=='$'){
    		break;
    	}
    	elevator_floor[j]=atoi(variable_string);
    	
    	
    	j=j+1;
    	
    	if(j > N_ELEVATORS){
    		printf("Error: faulty backup_file: iterator int j bigger than N_ELEVATORS in backup file: %s \n",filename);
    		return -1;
    	}
    }
    
    
    

    if(!order_queue_isempty()){
    	order_queue_destroy();
    	order_queue_initialize();
    }
    struct ORDER_QUEUE* temp=root;
    
    while(variable_string!=NULL){
    	
    	
    	variable_string = strtok(NULL, "#");
    	if(variable_string==NULL){
    		break;
    	}
    	
    	temp->next = (struct ORDER_QUEUE*) malloc(sizeof(struct ORDER_QUEUE));
    	temp=temp->next;
    	temp->next=NULL;
    	
    	temp->floor=atoi(variable_string);
    	
    	
    	variable_string = strtok(NULL, "#");
    	temp->direction = atoi(variable_string);
    	
    }
  }
       
  fclose(fp);
  return 1;
}
