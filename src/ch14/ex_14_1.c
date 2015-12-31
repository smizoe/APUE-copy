#include "apue.h"
#include <fcntl.h>
#include <errno.h>

int main(int argc, char const* argv[])
{
  if (argc != 3)
    err_quit("usage: %s (r|w) filename", argv[0]);

  int fd;
  if (strncmp("r", argv[1], 1) == 0){

    if((fd = open(argv[2], O_RDONLY)) < 0)
      err_sys("can't open %s", argv[2]);
    if(read_lock(fd, 0, SEEK_SET, 0) < 0)
      if(errno == EAGAIN || errno == EACCES)
        err_sys("failed to get read lock");

    printf("succeeded in obtaining read lock!\n");
  } else if (strncmp("w", argv[1], 1) == 0){

    if((fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC)) < 0)
      err_sys("can't creat %s", argv[2]);
    if(writew_lock(fd, 0, SEEK_SET, 0) < 0)
      err_sys("writew_lock failed");

    printf("succeeded in obtaining write lock!\n");
  } else
    err_sys("1st argument must start with r or w");
  printf("start sleeping 10 seconds...\n");
  sleep(10);
  un_lock(fd, 0, SEEK_SET, 0);
  printf("unlocked file %s\n", argv[2]);
  return 0;
}
