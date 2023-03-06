#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void 
transfer(int lp[2], int prime);

int
main()
{
  int p[2];
  pipe(p);

  int pid = fork();
  if (pid == 0) {
    close(p[1]);
    transfer(p, 2);
  } else {
    close(p[0]);
    for (int i = 2; i <= 35; i++) {
      write(p[1], &i, 4);
    }
    close(p[1]);
    wait(0);
  }
  
  exit(0);
}

void 
transfer(int lp[2], int prime) 
{
  int buf = 0;
  int hasRight = 0;
  int rp[2];

  printf("prime %d\n", prime);
  while (read(lp[0], &buf, 4) != 0) {
    if (buf % prime != 0) {
      if (hasRight == 0) {
        pipe(rp);
        int pid = fork();
        if (pid == 0) {
          close(rp[1]);
          transfer(rp, buf);
          break;
        } else {
          close(rp[0]);
          hasRight = 1;
        }
      } else {
        write(rp[1], &buf, 4);
      }
    } 
  }

  if (hasRight) {
    close(rp[1]);
    wait(0);
  }
  exit(0);
}