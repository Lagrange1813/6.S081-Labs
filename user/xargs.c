#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int 
main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(2, "Please input correct arguments!\n");
  }

  char* ex_argv[MAXARG];
  for (int i = 1; i < argc; i++) {
    ex_argv[i - 1] = argv[i];
  }
  ex_argv[argc] = 0;

  while(1) {
    char buf[512];
    int i = 0;

    while (1) {
      int len = read(0, &buf[i], 1);
      if (len == 0 || buf[i] == '\n') break;
      i++;
    }

    if (i == 0) break;

    buf[i] = 0;
    ex_argv[argc - 1] = buf;

    int pid = fork();

    if (pid == 0) {
      exec(ex_argv[0], ex_argv);
      printf("exec failed!\n");
      exit(1);
    } else {
      wait(0);
    }
  }

  exit(0);
}