#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int i, childpid;
  char buf[512];

  childpid = fork();
  if(childpid < 0){
    exit(-1);
  }else if(childpid == 0){
    int spaces = 0;
    char *p = buf;
    while(read(0, p, 1) > 0){
      if(*p == ' ' || *p == '\n')
        spaces++;
      p++;
    }
    int n1 = argc;
    int n2 = spaces;
    char *new_argv[n1+n2];
    for(i = 1; i < n1; i++)
      new_argv[i-1]=argv[i];
    p = buf;
    for(i = 0; i < n2; i++){
      new_argv[n1+i-1] = p;
      for(; *p != ' ' && *p != '\n'; )
        p++;
      *p = 0;
    p++;
    }
    exec(new_argv[0], new_argv);
    exit(0);
  }
  wait(0);
  exit(0);
}