#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void transfer(int pi[2]);

int
main()
{
  close(0);

  int pi[2];
  pipe(pi);
  
  int pid;
  pid = fork();

  if (pid==0) {
    transfer(pi);
  } else {
    close(pi[0]);

    for (int i = 2; i <= 35; i++) {
      write(pi[1], &i, 1);
    }

    close(pi[1]);

    wait((int *)0);
  }

  exit(0);
}

void transfer(int pi[2]) {
  close(pi[1]);

  int buf;
  if (read(pi[0], &buf, 1) == 0) exit(0);

  int child[2];
  pipe(child);

  int pid = 0;
  pid = fork();

  if (pid == 0) {
    transfer(child);
  } else {
    close(child[0]);

    printf("prime %d\n", buf);
    int prime = buf;

    while (read(pi[0], &buf, 1) != 0) {
      if (buf % prime != 0) {
        write(child[1], &buf, 1);
      }
    }

    close(child[1]);
    wait((int *)0);
    exit(0);
  }
}