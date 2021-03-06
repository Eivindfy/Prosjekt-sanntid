#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "client_backup.h"
#include "global_variables.h"




int write_backup_client(char* filename){

    FILE* fp;
    fp = fopen(filename, "w");
    
    if (fp == NULL) {
      printf("Error: couldn't open %s for writing in retreive_backup_client. \n",filename);
      return -1;
    }
    fclose(fp);
    
    
    fp = fopen(filename,"a");
    
	fprintf(fp,"$#%i#%i#%i#%i#$#", global_direction, global_current_floor, global_destination, global_idle);
	
	for(int i = 0 ; i < N_FLOORS ; i++){
    	fprintf(fp,"%i#",global_stop_array[i]);  // bryr oss ikkje om den blir updated underveis, satser paa reset som ikkje kjem heile tida
    }
   
   	fclose(fp);
    return 1;
}


int backup_tostring_client(char* filename, char* buffer, int size){

  FILE* fp;
  
   
  fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error: couldn't open %s for reading in backup_tostring\n", filename);
    return -1;
  }
  
  
  if(fgets(buffer, size, fp)!=NULL){
  	fclose(fp);
  	return 1;
  }
  else{
  	printf("Error: error reading line in file %s in backup_tostr\n",filename);
  	fclose(fp);
  	return -1;
  }
  
}


int retrieve_backup_client(char* filename){

  FILE *fp;
  char buffer[1024];
  char* variable_string;
  variable_string= NULL;
   
  fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error: couldn't open %s for reading in retreive_backup_client.\n", filename);
    return -1;
  }
  
  
  
  if(fgets(buffer, sizeof(buffer), fp)!=NULL){
  
    variable_string = strtok( buffer, "#");
    
    if(variable_string[0]!='$'){
    	printf("Error: error in backup file %s when retreiving backup\n", filename); 
    	fclose(fp);
    	return -1;
    }
    
    
    variable_string = strtok( NULL, "#");
    global_direction = atoi(variable_string);
    
    variable_string = strtok( NULL, "#");
    global_current_floor = atoi(variable_string);
    
    variable_string = strtok( NULL, "#");
    global_destination = atoi(variable_string);
    
    variable_string = strtok( NULL, "#");
    global_idle = atoi(variable_string);
    
    variable_string = strtok( NULL, "#");
    if(variable_string[0]!='$'){
    	printf("Error: faulty backup_file: file %s is corrupt",filename);
    	fclose(fp);
    	return -1;
    }
    
    int j = 0;
    while(variable_string!=NULL){
    
    	variable_string = strtok( NULL, "#");
    	if(variable_string==NULL){
    		break;
    	}
    	
    	global_stop_array[j]=atoi(variable_string);
    	
    	
    	j=j+1;
    	
    	if(j > N_FLOORS){
    		printf("Error: faulty backup_file: iterator int j bigger than N_FLOORS in backup file: %s \n",filename);
    		fclose(fp);
    		return -1;
    	}
    }
  }
  else{
  	printf("Error: could not copy line from file: %s \n",filename);
  }
       
  fclose(fp);
  return 1;
}
