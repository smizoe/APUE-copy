#include "apue.h"
#include "tell_using_signal.h"
#include <fcntl.h>

#define SOCK_PATH "/tmp/ex_17_2.sock"

int main(int argc, char const* argv[])
{
  pid_t pid;
  int fd[2], new_fd;
  char errmsg[MAXLINE];
  if(argc < 2)
    err_quit("usage: a.out filename");

  if(fd_pipe(fd) < 0)
    err_sys("fd_pipe error");

  TELL_WAIT();
  if((pid = fork()) < 0)
    err_sys("fork error");
  else if (pid == 0){
    close(fd[0]);
    if((new_fd = open(argv[1], O_RDONLY)) < 0){
      snprintf(errmsg, MAXLINE-1, "can't open %s\n", argv[1]);
      send_err(fd[1], -1, errmsg);
    }
    send_fd(fd[1], new_fd);
    WAIT_PARENT();
    lseek(new_fd, 10, SEEK_CUR);
    TELL_PARENT(getppid());
  } else { // parent
    close(fd[1]);
    new_fd = recv_fd(fd[0], write);
    printf("file offset is: %llu\n", lseek(new_fd, 0, SEEK_CUR));
    TELL_CHILD(pid);
    WAIT_CHILD();
    printf("file offset is: %llu\n", lseek(new_fd, 0, SEEK_CUR));
    wait(NULL);
  }
  return 0;
}
