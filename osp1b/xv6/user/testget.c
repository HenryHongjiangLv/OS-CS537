#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

int
main(int argc, char *argv[])
{
  int n = getreadcount();
  printf(1, "getreadcount: begining status is %d\n", n);
  int fd = open("README", 0);
  read(fd, buf, sizeof(buf));
  n = getreadcount();
  printf(1, "getreadcount: after one read, the status is%d\n", n);
  read(fd, buf, sizeof(buf));
  read(fd, buf, sizeof(buf));
  n = getreadcount();
  printf(1, "getreadcount: after another two reads, the status is%d\n", n);

  close(fd);
  exit();
}
