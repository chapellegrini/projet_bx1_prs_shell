#include "Shell.h"
#include "Evaluation.h"
#include "Commandes_Internes.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>


void
verifier(int cond, char *s)
{
  if (!cond)
    {
      perror(s);
      exit(1);
    }
}

void cmd(char **arg){
  extern char **environ;

  execve(arg[0], arg, environ);
  perror("exec");
  exit(1);
}


int evaluer_expr(Expression *e){
  pid_t sonPid;

  sonPid = fork();
  if(!sonPid)
    exec_expr(e);
  else
    waitpid(sonPid, 0, 0);
  return 1;
}

int exec_expr(Expression *e){
  int fd;
  int pipefd[2];
  pid_t sonPid;

  if(e->type == SIMPLE){
    cmd(e->arguments);
  }
  else if(e->type == REDIRECTION_O){
    fd = open(e->arguments[0], O_CREAT | O_WRONLY, 0644);// WIP?
    dup2(fd, 1);
    close(fd);
    exec_expr(e->gauche);
  }
  else if(e->type == PIPE){
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
  return 1;
}


