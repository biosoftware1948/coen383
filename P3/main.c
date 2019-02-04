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
  while (!isEmpty(seller->customerQueue)) {
    pthread_mutex_lock(&mutex);
    //pthread_cond_wait(&cond, &mutex);
    Customer* c = deQueue(seller->customerQueue);

    if (seller->type == 'H') {
      int found_seat = 0;
      int starting_row = 0;
      while(!found_seat) {
        for (int i = 0; i < 10; ++i) {
        //printf("seat: %d\n", seller->auditorium->seats[0][i].id);
          if (seller->auditorium->seats[seller->current_row][i].customer_id == -1) {
            seller->auditorium->seats[seller->current_row][i].customer_id = c->id;
            seller->auditorium->seats[seller->current_row][i].seller_id = seller->id;
            seller->auditorium->seats[seller->current_row][i].type= c->type;
            found_seat = 1;
            break;
          }
          if (i == 9) {
            ++seller->current_row;
            if(seller->current_row == 10) {
              removeContents(seller->customerQueue);
              found_seat = 1;
          }
          }
        }
      }
    }
    if (seller->type == 'M') {
      int found_seat = 0;
      int starting_row = 5;
      while(!found_seat) {
        for (int i = 0; i < 10; ++i) {
        //printf("seat: %d\n", seller->auditorium->seats[0][i].id);
          if (seller->auditorium->seats[seller->current_row][i].customer_id == -1) {
            seller->auditorium->seats[seller->current_row][i].customer_id = c->id;
            seller->auditorium->seats[seller->current_row][i].seller_id = seller->id;
            seller->auditorium->seats[seller->current_row][i].type= c->type;
            found_seat = 1;
            break;
          }
          if (i == 9) {
            ++seller->current_row;
            if(seller->current_row == -1 || seller->current_row == 10) {
              removeContents(seller->customerQueue);
              found_seat = 1;
          }
          }
        }
      }
    }

    if (seller->type == 'L') {
       {
      int found_seat = 0;
      while(!found_seat) { 
      for (int i = 0; i < 10; ++i) {
        if (seller->auditorium->seats[seller->current_row][i].customer_id == -1) {
          seller->auditorium->seats[seller->current_row][i].customer_id = c->id;
          seller->auditorium->seats[seller->current_row][i].seller_id = seller->id;
          seller->auditorium->seats[seller->current_row][i].type= c->type;
          found_seat = 1;
          break;
        }
        if (i == 9) {
          //Row is full
          --seller->current_row;
          if(seller->current_row == -1) {
            removeContents(seller->customerQueue);
            found_seat = 1;
          }
        }
      }
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
  if(argc != 2) {
    printf("Please enter N as a command line argument, where N is the number of buyers\n");
    exit(0);
  }
  volatile Auditorium* auditorium = createAuditorium();
  pthread_t tids[10]; 
  int N = atoi(argv[1]);

  //Create sellers with their customers
  Seller* H1 = createSeller('H', 0, 0, N, auditorium);
 
  pthread_create(&tids[0], NULL, sell, H1);
  for(int i = 1; i < 4; ++i) {
    Seller* M = createSeller('M', i, 4, N, auditorium);
    pthread_create(&tids[i], NULL, sell, M);
  }
  for(int i = 4; i < 10; ++i) {
    Seller* L = createSeller('L', i, 9, N, auditorium);
    pthread_create(&tids[i], NULL, sell, L);
  }

  wakeup_all_seller_threads();
  // wait for all seller threads to exit for (i = 0 ; i < 10 ; i++)
  for(int i = 0; i < 10; ++i) { 
    pthread_join(tids[i], NULL);
    ;
  }
  // Printout simulation results …………
  printAuditorium(auditorium);
  exit(0);
  
}
