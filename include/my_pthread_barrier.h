#ifndef GUARD_234B5073_7C92_423E_B8C2_AB380B69786E
#define GUARD_234B5073_7C92_423E_B8C2_AB380B69786E

// in writing this, I read the followings as reference
// http://blog.albertarmea.com/post/47089939939/using-pthread-barrier-on-mac-os-x
// http://www.howforge.com/implementing-barrier-in-pthreads

#define PTHREAD_BARRIER_SERIAL_THREAD -1

#include <pthread.h>
#include <errno.h>

#define pthread_barrier_t           barrier_t
#define pthread_barrier_attr_t      barrier_attr_t
#define pthread_barrier_init(b,a,n) barrier_init(b,n)
#define pthread_barrier_destroy(b)  barrier_destroy(b)
#define pthread_barrier_wait(b)     barrier_wait(b)

typedef struct {
  int count;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
} barrier_t;


int barrier_init(barrier_t * barrier, unsigned int count)
{
  if(count == 0){
    errno = EINVAL;
    return errno;
  }
  barrier->count = count;

  if (pthread_mutex_init(&barrier->mutex, NULL) != 0){
    return errno;
  }
  if (pthread_cond_init(&barrier->cond, NULL) != 0){
    return errno;
  }

  return 0;
}

int barrier_destroy(barrier_t *barrier)
{
  if(pthread_cond_destroy(&barrier->cond) != 0)
    return errno;

  if(pthread_mutex_destroy(&barrier->mutex) != 0)
    return errno;

  return 0;
}


int barrier_wait(barrier_t * barrier)
{
  pthread_mutex_lock(&barrier->mutex);

  barrier->count -= 1;
  int retval = 0;

  if(barrier->count <= 0){
    pthread_cond_broadcast(& barrier->cond);
    retval = PTHREAD_BARRIER_SERIAL_THREAD;
  }else{
    while(barrier->count > 0)
      if(pthread_cond_wait(& barrier->cond, & barrier->mutex) != 0)
        return errno;
  }

  if(pthread_mutex_unlock(&barrier->mutex) != 0)
    return errno;

  return retval;
}
#endif //GUARD_234B5073_7C92_423E_B8C2_AB380B69786E
