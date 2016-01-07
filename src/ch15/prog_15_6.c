#include "apue.h"
#include <sys/wait.h>

#define DEF_PAGEER "/bin/more"

int main(int argc, char const* argv[])
{
  int n;
  int fd[2];
  pid_t pid;
  char *pager, *argv0;
  char line[MAXLINE];
  FILE *fp;
  if (argc != 2)
    err_quit("usage: a.out <pathname>");
  if ((fp = fopen(argv[1], "r")) == NULL)
    err_sys("can't open %s", argv[1]);
  if (pipe(fd) < 0)
    err_sys("pipe error");
  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid > 0) {
    close(fd[0]);

    while (fgets(line, MAXLINE, fp) != NULL) {
      n = strlen(line);
      if (write(fd[1], line, n) != n)
        err_sys("write error to pipe");
    }
    if (ferror(fp))
      err_sys("fgets error");
    close(fd[1]);
    // we don't need waitpid if we can guarantee that the child always dup2 before the parent exits;
    // if the parent exits before the child and nothing flows in from stdin, the child has to exit.
    // What happens if we removed waitpid? Several of the followings will occur:
    // - parent will surely write content of the specified file to the write end of pipe
    // - parent exits
    // - pager will read (or wait for input) from stdin, whose content is data written from write end of the pipe
    // - SIGHUP is sent to child if parent exits before completion of child
    // so depending on the order of occurrence of 2nd and 3rd item, this program can print initial part of the file
    // or print nothing.
    if (waitpid(pid, NULL, 0) < 0)
      err_sys("waitpid error");
    exit(0);
  } else {
    close(fd[1]);
    if (fd[0] != STDIN_FILENO) {
      if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
        err_sys("dup2 error to stdin");
      close(fd[0]);
    }
    if ((pager = getenv("PAGER")) == NULL)
      pager = DEF_PAGEER;
    if ((argv0 = strrchr(pager, '/')) != NULL)
      argv0++;
    else
      argv0 = pager;
    if (execl(pager, argv0, (char *)0) < 0)
      err_sys("execl error for %s", pager);
  }
  exit(0);
}
