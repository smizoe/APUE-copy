#include "apue.h"
#include <errno.h>


struct {
  int signo;
  char signame[10];
} sigmap[] = {
{SIGHUP, "SIGHUP"},
{SIGINT, "SIGINT"},
{SIGQUIT, "SIGQUIT"},
{SIGILL, "SIGILL"},
{SIGTRAP, "SIGTRAP"},
{SIGABRT, "SIGABRT"},
#if  (defined(_POSIX_C_SOURCE) && !defined(_DARWIN_C_SOURCE))
{SIGPOLL, "SIGPOLL"},
#else	/* (!_POSIX_C_SOURCE || _DARWIN_C_SOURCE) */
{SIGIOT, "SIGIOT"},
{SIGEMT, "SIGEMT"},
#endif	/* (!_POSIX_C_SOURCE || _DARWIN_C_SOURCE) */
{SIGFPE, "SIGFPE"},
{SIGKILL, "SIGKILL"},
{SIGBUS, "SIGBUS"},
{SIGSEGV, "SIGSEGV"},
{SIGSYS, "SIGSYS"},
{SIGPIPE, "SIGPIPE"},
{SIGALRM, "SIGALRM"},
{SIGTERM, "SIGTERM"},
{SIGURG, "SIGURG"},
{SIGSTOP, "SIGSTOP"},
{SIGTSTP, "SIGTSTP"},
{SIGCONT, "SIGCONT"},
{SIGCHLD, "SIGCHLD"},
{SIGTTIN, "SIGTTIN"},
{SIGTTOU, "SIGTTOU"},
#if  (!defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE))
{SIGIO, "SIGIO"},
#endif
{SIGXCPU, "SIGXCPU"},
{SIGXFSZ, "SIGXFSZ"},
{SIGVTALRM, "SIGVTALRM"},
{SIGPROF, "SIGPROF"},
#if  (!defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE))
{SIGWINCH, "SIGWINCH"},
{SIGINFO, "SIGINFO"},
#endif
{SIGUSR1, "SIGUSR1"},
{SIGUSR2, "SIGUSR2"}
    };

int nsigs = sizeof(sigmap)/sizeof(sigmap[0]);

void
pr_mask(const char *str)
{
  sigset_t sigset;
  int errno_save;
  errno_save = errno;
  if(sigprocmask(0, NULL, &sigset) < 0)
    err_ret("sigprocmask error");
  else{
    printf("%s", str);
    for(int indx = 0; indx < nsigs;indx++){
      if(sigismember(&sigset,sigmap[indx].signo))
        printf("%s ", sigmap[indx].signame);
    }
    printf("\n");
  }

  errno = errno_save;
}
