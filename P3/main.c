#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "queue.h"
#include "seats.h"
#include "seller.h"
#include "Customer.h"

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
volatile pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//Create the auditorium with seats


// seller thread to serve one time slice (1 minute)
void * sell(Seller* seller, Auditorium* auditorium)
{
  //printf("About to print Queue of %d\n", seller->id);
  //printQueue(seller->customerQueue);
  //printf("printed q\n");
    
  while (!isEmpty(seller->customerQueue)) {
    pthread_mutex_lock(&mutex);
    //pthread_cond_wait(&cond, &mutex);
    Customer* c = deQueue(seller->customerQueue);
    printf("\n %d has queue length %d", seller->id, seller->customerQueue->size);
    if (seller->type == 'H') {
      for (int i = 0; i < 10; ++i) {
        //printf("seat: %d\n", seller->auditorium->seats[0][i].id);
        if (seller->auditorium->seats[0][i].id == -1) {
          seller->auditorium->seats[0][i].id = c->id;
          seller->auditorium->seats[0][i].type= c->type;

        }
      }
    }
      pthread_mutex_unlock(&mutex);
  }

  return NULL; // thread exits
}

void wakeup_all_seller_threads()
{
  pthread_mutex_lock(&mutex);
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&mutex);
}

int main(int argc, char** argv)
{
  //if(argc != 2) {
  //  printf("Please enter N as a command line argument, where N is the number of buyers\n");
  //  exit(0);
  //}
  volatile Auditorium* auditorium = createAuditorium();
  pthread_t tids[10]; 
  int N = 10;//atoi(argv[1]);

  //Create sellers with their customers
  Seller* H1 = createSeller('H', 0, N, auditorium);
 
  pthread_create(&tids[0], NULL, sell, H1);
  for(int i = 1; i < 4; ++i) {
    Seller* M = createSeller('M', i, N, auditorium);
    pthread_create(&tids[i], NULL, sell, M);
  }
  for(int i = 4; i < 10; ++i) {
    Seller* L = createSeller('L', i, N, auditorium);
    pthread_create(&tids[i], NULL, sell, L);
  }

  wakeup_all_seller_threads();
  // wait for all seller threads to exit for (i = 0 ; i < 10 ; i++)
  for(int i = 0; i < 10; ++i) { 
    pthread_join(tids[i], NULL);
    ;
  }
  // Printout simulation results …………
  exit(0);
  
}
