#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc < 2 || argc > 2) {
    write(1, "Please input a correct argument!", 32);
    exit(1);
  } 

  int time = atoi(argv[1]);

  sleep(time);

  exit(0);
}