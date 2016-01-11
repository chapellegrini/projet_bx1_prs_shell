#define _GNU_SOURCE
#include "Commandes_Internes.h"
#include "unistd.h"
#include "signal.h"
#include "stdio.h"
#include "stdlib.h"
#include <time.h>

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

int cmdExit(char** c){ //TODO notice me sempai Pellegrini
  int n = 0;
  if(c[0] != 0)
    n = atoi(c[0]);
  exit(n);
}



/*void cmdKill(char** c){
  int n = 0;
  if(c[0] != 0){
    n = atoi(c[0]);
    kill(n,SIGKILL);
  }
  }*/

int cmdKill(char** c){
  int n;
  int opt;
  char* param = "SIGKILL";
  if(c[0] == 0)
    return EXIT_FAILURE;
  int i = 0;
  if (c[0][0] == '-'){
    param = getParam(c[0]);
    printf("%s",param);
    i++;
  }
  if (param == "l"){
    printf( "1 HUP \n 2 INT \n 3 QUIT \n 4 ILL \n5 TRAP \n6 ABRT \n7 BUS \n8 FPE \n9 KILL \n10 USR1 \n11 SEGV \n12 USR2 \n13 PIPE \n14 ALRM \n15 TERM \n16 STKFLT \n17 CHLD \n18 CONT \n19 STOP \n20 TSTP \n21 TTIN \n22 TTOU \n23 URG \n24 XCPU \n25 XFSZ \n26 VTALRM \n27 PROF \n28 WINCH \n29 POLL \n30 PWR \n31 SYS \n");
  }
  while(c[i] != 0){
    int PID = atoi(c[i]);
    kill(PID,atoi(param));
  }
  return EXIT_SUCCESS;
}

int cmdEcho(char** c){
  int i = 0;
  while(c[i] != 0)
    printf("%s\n",c[i++]);
  return;
}

int cmdCd(char** c){
  chdir(c[0]);
  perror("cd");
  return EXIT_SUCCESS;
}

int cmdPwd(char** c){
  char* t = get_current_dir_name();
  printf("%s",t);
  free(t);
  return EXIT_SUCCESS;
}

int cmdGetHostName(char** c){
  char name[256];
  int i = gethostname(name, sizeof(name));
  if(i!=0)
    perror("errno");
  else{
    printf("%s",name);
  }
  return EXIT_SUCCESS;
}

int cmdDate(char** c){
  time_t t = time(NULL);
  struct tm *date = localtime(&t);
  char* param = "%a";
  if(c[0]!=0)
    param=getParam(c[0]);
  char str[256];
  strftime(str,sizeof(str),param,date);
  printf("%s \n",str);
  return EXIT_SUCCESS;
}
