#include "apue.h"
#include <dirent.h>
#include <limits.h>

typedef int Myfunc(const char *, const struct stat *, int);

static Myfunc myfunc;
static int myftw(char *, Myfunc *);
static int dopath(Myfunc *);

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main(int argc, char *argv[])
{
  int ret;
  if (argc != 2)
    err_quit("usage: ftw <starting-pathname>");

  ret = myftw(argv[1], myfunc);

  ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
  if (ntot == 0)
    ntot = 1;
  printf("regular files   = %7ld, %5.2f %%\n", nreg, nreg * 100.0 / ntot);
  printf("directories     = %7ld, %5.2f %%\n", ndir, ndir * 100.0 / ntot);
  printf("block special   = %7ld, %5.2f %%\n", nblk, nblk * 100.0 / ntot);
  printf("char special    = %7ld, %5.2f %%\n", nchr, nchr * 100.0 / ntot);
  printf("FIFOs           = %7ld, %5.2f %%\n", nfifo, nfifo * 100.0 / ntot);
  printf("symbolic links  = %7ld, %5.2f %%\n", nslink, nslink * 100.0 / ntot);
  printf("sockets         = %7ld, %5.2f %%\n", nsock, nsock * 100.0 / ntot);

  exit(ret);
}

#define FTW_F   1
#define FTW_D   2
#define FTW_DNR 3
#define FTW_NS  4

static char *fullpath;
static size_t pathlen;

static int
myftw(char *pathname, Myfunc *func)
{
  fullpath = path_alloc(&pathlen);
  if (pathlen <= strlen(pathname)){
    pathlen = strlen(pathname) * 2;
    if ((fullpath = realloc(fullpath, pathlen)) == NULL)
      err_sys("realloc failed");
  }
  strcpy(fullpath, pathname);
  return(dopath(func));
}

static int
dopath(Myfunc * func)
{
  struct stat    statbuf;
  struct dirent *dirp;
  DIR           *dp;
  int            ret,n;

  if (lstat(fullpath, &statbuf) < 0)
    return(func(fullpath, &statbuf, FTW_NS));
  if (S_ISDIR(statbuf.st_mode) == 0)
    return(func(fullpath, &statbuf, FTW_F));

  if ((ret = func(fullpath, &statbuf, FTW_D)) != 0)
    return(ret);

  n = strlen(fullpath);
  if (n + NAME_MAX + 2 > pathlen){
    pathlen *= 2;
    if ((fullpath = realloc(fullpath, pathlen)) == NULL)
      err_sys("realloc failed");
  }
  fullpath[n++] = '/';
  fullpath[n] = 0;
  if ((dp = opendir(fullpath)) == NULL)
    return(func(fullpath, &statbuf, FTW_DNR));

  while ((dirp = readdir(dp)) != NULL) {
    if (strcmp(dirp->d_name, ".") == 0 ||
        strcmp(dirp->d_name, ".."))
      continue;


  }
}
