#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int i;

  if(argc < 2){
    fprintf(2, "Usage: rm files...\n");
    exit(1);
  }

  for(i = 1; i < argc; i++){
    if(unlink(argv[i]) < 0){                            // call the unlink function to remove the specified file
      fprintf(2, "rm: %s failed to delete\n", argv[i]); // unlink returning a negative value means error occurring during removing
      break;
    }
  }

  exit(0);
}
