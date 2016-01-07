#include "Commandes_Internes.h"
#include "unistd.h"
#include "signal.h"

void cmdExit(char** c){ //TODO notice me sempai Pellegrini
  int n = 0;
  if(c[0] != 0)
    n = atoi(c[0]);
  return exit(n);
}



void cmdKill(char** c){
  int n = 0;
  if(c[0] != 0){
    n = atoi(c[0]);
    kill(n,SIGKILL);
  }
}

void cmdEcho(char** c){
  write(STDOUT_FILENO,c,sizeof(c));
}
