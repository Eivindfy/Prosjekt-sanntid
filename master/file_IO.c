#include <string.h>
#include <stdio.h>
#include "file_IO.h"




//kan ta inn fleire argument om ein treng det:
int write_backup_master(char* filename){
    FILE* fp;

    fp = fopen("filename", "w");

    if (fp == NULL) {
      printf("Error: couldn't open %s \n",filename);
      return -1;
    }
    fclose(fp);
    
    fp = fopen("filename","a");
    
   git b
   for
    fprintf(fp,"%d#%d#%d#%s#\n", doublevariabel, doublevariabel, osv)
    
    
    fclose(fp);
   
    return 1;
}




int retrieve_backup_master(char* filename){

  FILE *fp;
  char buffer[1024];
  char* variable_string;
  variable_string= NULL;
   
  fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("I couldn't open %s for reading.\n", filename);
    return -1;
  }
  
  if(gets(buffer, sizeof(buffer), fp)!=NULL){
    variable_string = strtok( buffer, "#");
    //gjer noko med første variabel
    
    variable_string = strtok( NULL, "#");
    //gjer noko med andre variabel
    
    variable_string = strtok( NULL, "#");
    //tredje variabel osv, veit ikkje kvifor NULL fungerer som input
    
    
    //FLEIRE HEISAR?? FORTSETT I SLUTTEN TIL DU NÅR variable_string==NULL
  
  }
  
  
  
  
      
  fclose(fp);
  return 1;
}
