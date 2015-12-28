#include "apue.h"
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>


extern char **environ;

pthread_mutex_t env_mutex;

static pthread_once_t init_done = PTHREAD_ONCE_INIT;
static int environ_extended = 0;
void update_existing_env(const char *str, int env_indx);
void add_new_env(const char *str);

static void thread_init(void) {
  pthread_mutexattr_t attr;

  pthread_mutexattr_init(&attr);
  pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
  pthread_mutex_init(&env_mutex, &attr);
}

int putenv_r(char *str) {
  int err, i, len, env_indx;
  sigset_t mask, old_mask;
  sigfillset(&mask);
  pthread_once(&init_done, thread_init);

  if (strpbrk(str, "=") == NULL) // not in a correct format
    return -1;

  len = strcspn(str, "=");

  pthread_mutex_lock(&env_mutex);
  if((err = pthread_sigmask(SIG_SETMASK, &mask, &old_mask)) != 0)
    err_exit(err, "SIG_BLOCK error");

  env_indx = -1;
  for (i = 0; environ[i] != NULL; i++) {
    if((strncmp(str, environ[i], len) == 0) &&
       (environ[i][len] == '=')) {
      env_indx = i;
      break;
    }
  }
  if(env_indx >= 0)
    update_existing_env(str, env_indx);
  else
    add_new_env(str);

  if (sigprocmask(SIG_SETMASK, &old_mask, NULL) < 0)
    err_sys("SIG_SETMASK error");

  pthread_mutex_unlock(&env_mutex);
  return 0;
}

void update_existing_env(const char *str, int env_indx) {
  int env_len, new_env_len;
  env_len = strlen(environ[env_indx]);
  new_env_len = strlen(str);
  if(env_len < new_env_len)
    strcpy(environ[env_indx], str);
  else {
    char *new_env_ptr = (char *) malloc(new_env_len + 1);
    strcpy(new_env_ptr, str);
    //char *old_env_ptr = environ[env_indx];
    environ[env_indx] = new_env_ptr;
    // we can't free the old pointer since we are not sure whether it is allocated by us or not
    //free(old_env_ptr);
  }
}

void add_new_env(const char *str) {
  int env_len = 0;
  for(int i = 0; environ[i] != NULL; i++)
    env_len++;

  char *new_env_ptr = malloc(strlen(str) + 1);
  strcpy(new_env_ptr, str);

  if (environ_extended){
    environ = realloc(environ, env_len + 1);
  } else {
    char ** new_environ = malloc(env_len + 1);
    for(int i = 0; environ[i] != NULL; i++)
      new_environ[i] = environ[i];
    environ = new_environ;
    environ_extended = 1;
  }
  environ[env_len] = new_env_ptr;
  environ[env_len + 1] = NULL;
}
