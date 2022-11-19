#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int 
main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("Please input correct arguments!\n");
  }

  char* exarg[MAXARG];
  for (int i = 1; i < argc; i++) {
    exarg[i-1] = argv[i];
  }
  exarg[argc] = 0;

  while(1) {
    char buf[512];
    int i = 0;

    while (1) {
      int len = read(0,&buf[i],1);
      if (len == 0 || buf[i] == '\n') break;
      i++;
    }

    if (i==0) break;

    buf[i] = 0;
    exarg[argc-1] = buf;

    int pid = 0, status;
    pid = fork();

    if (pid == 0) {
      exec(exarg[0], exarg);
      printf("exec failed!\n");
      exit(1);
    } else {
      wait(&status);
    }
  }

  exit(0);
}