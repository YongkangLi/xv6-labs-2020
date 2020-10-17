#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  char c;
  int childpid, status;
  int pipefd[2];

  if(argc != 1){
    fprintf(2, "Usage: pingpong\n");
    exit(1);
  }

  childpid = fork();
  if(childpid < 0){
    exit(-1);
  }

  pipe(pipefd);

  if(childpid> 0){
    write(pipefd[1], &c, 1);
    wait(&status);

    read(pipefd[0], &c, 1);
    fprintf(2, "%d: received pong\n", getpid());
  }else if(childpid == 0){
    read(pipefd[1], &c, 1);
    fprintf(2, "%d: received ping\n", getpid());
    
    write(pipefd[0], &c, 1);
  }

  exit(0);
}
