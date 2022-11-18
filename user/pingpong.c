#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main()
{
  int pid;
  int status;

  int p[2];

  pipe(p);

  pid = fork();

  if (pid == 0) {
    char buf[1];
    read(p[0], buf, 1);
    printf("%d: received ping\n", getpid());
    write(p[1], buf, 1);
    exit(0);
  } else {
    write(p[1], "t", 1);
    wait(&status);
    char buf[1];
    read(p[0], buf, 1);
    printf("%d: received pong\n", getpid());
  }

  exit(0);
}