#include "Shell.h"
#include "Evaluation.h"
#include "Commandes_Internes.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>



void verifier(int cond, char *s){
  if (!cond){
      perror(s);
      exit(1);
  }
}


int evaluer_expr(Expression *e){
  pid_t sonPid;
  int status;

  if(e->type == SIMPLE){
    if(!strcmp(e->arguments[0], "echo"))
      return cmdEcho(&(e->arguments[1]));
    else if(!strcmp(e->arguments[0], "date"))
      return cmdDate(&(e->arguments[1]));
    else if(!strcmp(e->arguments[0], "cd"))
      return cmdCd(&(e->arguments[1]));
    else if(!strcmp(e->arguments[0], "pwd"))
      return cmdPwd(&(e->arguments[1]));
    else if(!strcmp(e->arguments[0], "history"))
      return cmdHistory(&(e->arguments[1]));
    else if(!strcmp(e->arguments[0], "hostname"))
      return cmdHostname(&(e->arguments[1]));
    else if(!strcmp(e->arguments[0], "kill"))
      return cmdKill(&(e->arguments[1]));
    else if(!strcmp(e->arguments[0], "exit"))
      return cmdExit(&(e->arguments[1]));
  }
  sonPid = fork();
  if(!sonPid)
    exit(exec_expr(e));
  else
    waitpid(sonPid, &status, 0);
  return status;
}

int exec_expr(Expression *e){
  int fd;
  int pipefd[2];
  int r;
  pid_t sonPid;

  if(e->type == SIMPLE){
    execvp(e->arguments[0], e->arguments);//or execve with "extern char **environ"
    perror("exec");
    return 1;//TODO : fail avec un masque
  }
  else if(e->type == REDIRECTION_O){ // >
    fd = open(e->arguments[0], O_CREAT | O_WRONLY, 0644);// WIP?
    dup2(fd, 1);
    close(fd);
    return exec_expr(e->gauche);
  }
  else if(e->type == REDIRECTION_A){ // >>
    fd = open(e->arguments[0], O_APPEND);// WIP?
    dup2(fd, 1);
    close(fd);
    exec_expr(e->gauche);
  }
  else if(e->type == REDIRECTION_E){ // 2>
    fd = open(e->arguments[0], O_CREAT | O_WRONLY, 0644);// WIP?
    dup2(fd, 2);
    close(fd);
    exec_expr(e->gauche);
  }
  else if(e->type == REDIRECTION_I){ // <
    fd = open(e->arguments[0], O_RDONLY);
    dup2(fd, 0);
    close(fd);
    exec_expr(e->gauche);
  }
  else if(e->type == PIPE){ // |
    pipe(pipefd);
    sonPid = fork();
    if(!sonPid){
      close(pipefd[0]);
      dup2(pipefd[1], 1);
      close(pipefd[1]);
      exec_expr(e->gauche);
    }
    else{
      close(pipefd[1]);
      dup2(pipefd[0], 0);
      close(pipefd[0]);
      exec_expr(e->droite);
    }
  }
  else if(e->type == BG){ // &
    pid_t sonPid;
    sonPid = fork();
    if(!sonPid)
      exec_expr(e->gauche);//TODO récupéré par init?
    return sonPid;
  }
  else if(e->type == SEQUENCE){ // ;
    evaluer_expr(e->gauche);
    exec_expr(e->droite);
  }
  else if(e->type == SEQUENCE_ET){ // &&
    r = evaluer_expr(e->gauche);
    if(r == 0)
      return exec_expr(e->droite);
    return r;
  }
  else if(e->type == SEQUENCE_OU){ // ||
    if(evaluer_expr(e->gauche) == 0)
      return 0;
    return exec_expr(e->droite);
  }
  else if(e->type == SOUS_SHELL){ // ()
    return evaluer_expr(e->gauche);
  }
}
