#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int ready = 0;

void *provide(void* arg) {
  while (true) {
    pthread_mutex_lock(&lock);
    if (ready == 1)
    {
      pthread_mutex_unlock(&lock);
      continue;
    }
    ready = 1;
    printf("provided\n");
    pthread_cond_signal(&cond1);
    pthread_mutex_unlock(&lock);
    sleep(1);
  }
}

void *consume(void* arg) {
  while (true) {
    pthread_mutex_lock(&lock);
    while (ready == 0)
    {
      pthread_cond_wait(&cond1, &lock);
      //printf("awoke\n");
    }
    ready = 0;
    printf("consumed\n");
    pthread_mutex_unlock(&lock);
  }
}

int main(int argc, char *argv[])
{
        pthread_t prov, cons;
        pthread_create(&prov, 0, provide, 0);
        pthread_create(&cons, 0, consume, 0);
        pthread_join(prov,0);
        pthread_join(cons,0);
        pthread_mutex_destroy(&lock);
        return 0;
}