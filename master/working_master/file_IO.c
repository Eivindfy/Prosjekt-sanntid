#include <string.h>
#include <stdio.h>
#include "file_IO.h"




//kan ta inn fleire argument om ein treng det:
int write_backup(char* filename){
    FILE* fp;

    fp = fopen("filename", "w");

    if (fp == NULL) {
      printf("I couldn't open results.dat for writing.\n");
      return -1;
    }
   
    fprintf(fp,"%d#%d#%d#%s#\n", doublevariabel, doublevariabel, osv)
    fclose(fp);
   
    return 1;
}




int retrieve_backup(char* filename){

  FILE *fp;
  char buffer[1024];
  char* variable_string;
  variable_string= NULL;
   
  fp = fopen("filename", "r");
  if (fp == NULL) {
    printf("I couldn't open results.dat for reading.\n");
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
