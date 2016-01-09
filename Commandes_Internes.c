#define _GNU_SOURCE
#include "Commandes_Internes.h"
#include "unistd.h"
#include "signal.h"
#include "stdio.h"

/*
Fonction utilitaire 
*/

char* getParam(char* c){
  char* param;
  int i = 1;
  while(c[i] != '\0'){
    param[i-1] = c[i];
    i++;
  }
  return param;
}


/*
Fonction Interne
*/

void cmdExit(char** c){ //TODO notice me sempai Pellegrini
  int n = 0;
  if(c[0] != 0)
    n = atoi(c[0]);
  return exit(n);
}



/*void cmdKill(char** c){
  int n = 0;
  if(c[0] != 0){
    n = atoi(c[0]);
    kill(n,SIGKILL);
  }
  }*/

void cmdKill(char** c){
  int n;
  int opt;
  char* param;
  if(c[0] == 0)
    return ;
  int i =0;
  while (c[i][0] == '-'){
    param = getParam(c[i]);
  }

}

void cmdEcho(char** c){
  printf("%s\n",c[0]);
}

void cmdCd(char** c){
  char* dir;
  char* tmp = get_current_dir_name();
 
  if(c[0]==".."){
    int pos;
    for(int i = 0; i<= strlen(tmp);i++){
      if(tmp[i]=='/')
	pos=i;
    }
    tmp[pos]='\0';
    for (int i = pos+1;i<strlen(tmp);i++){
      tmp[i]=0;
    }
    strcpy(dir,tmp);
  }
  else{
  strcat(dir,tmp);
  strcat(dir,c[0]);
    }
  free(tmp);
  chdir(dir);
  perror("cd");
}

void cmdPwd(char** c){
  char* tmp = get_current_dir_name();
  printf("%s",tmp);
  free(tmp);
}
