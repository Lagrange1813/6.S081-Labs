#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main()
{
  int w[2];
  int r[2];
  pipe(w);
  pipe(r);
  int pid = fork();

  if (pid == 0) {
    close(r[0]);
    close(w[1]);

    char buf[1];
    read(w[0], buf, 1);
    printf("%d: received ping\n", getpid());
    write(r[1], buf, 1);

    exit(0);

  } else {
    close(r[1]);
    close(w[0]);

    write(w[1], "b", 1);
    wait(0);
    char buf[1];
    read(r[0], buf, 1);
    printf("%d: received pong\n", getpid());
  }

  exit(0);
}