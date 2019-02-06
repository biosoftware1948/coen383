#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "queue.h"
#include "seats.h"
#include "seller.h"
#include "Customer.h"
#include <unistd.h>
#include <time.h>

//Global mutex conditions
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
volatile pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//sleeps for the specified milliseconds
int nsleep(long miliseconds)
{
   struct timespec req, rem;

   if(miliseconds > 999)
   {   
        req.tv_sec = (int)(miliseconds / 1000);                            /* Must be Non-Negative */
        req.tv_nsec = (miliseconds - ((long)req.tv_sec * 1000)) * 1000000; /* Must be in range of 0 to 999999999 */
   }   
   else
   {   
        req.tv_sec = 0;                         /* Must be Non-Negative */
        req.tv_nsec = miliseconds * 1000000;    /* Must be in range of 0 to 999999999 */
   }   

   return nanosleep(&req , &rem);
}

//Seller thread
void * sell(Seller* seller, Auditorium* auditorium)
{
  // each minute is 100 milliseconds for simulation purposes
  long sleep_time = get_service_time(seller) *100;
  //continue while a seller still has customers
  while (!isEmpty(seller->customerQueue)) {
    if (seller->type == 'H') {
      int found_seat = 0;
      int starting_row = 0;
      while(!found_seat) {
        for (int i = 0; i < 10; ++i) {
        //printf("seat: %d\n", seller->auditorium->seats[0][i].id);
          if (seller->auditorium->seats[seller->current_row][i].customer_id == -1) {
            pthread_mutex_lock(&mutex);
            nsleep(sleep_time);
            reserveSeat(seller, i);
            pthread_mutex_unlock(&mutex);
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
            pthread_mutex_lock(&mutex);        
            nsleep(sleep_time);
            reserveSeat(seller, i);
            pthread_mutex_unlock(&mutex); 
            found_seat = 1;
            break;
          }
          if (i == 9) {
            seller->current_row = getNewMRow(seller->current_row);
            if(seller->current_row == -1 || seller->current_row == 10) {
              removeContents(seller->customerQueue);
              found_seat = 1;
          }
          }
        }
      }
    }

    if (seller->type == 'L') {
      int found_seat = 0;
      while(!found_seat) { 
      for (int i = 0; i < 10; ++i) {
        if (seller->auditorium->seats[seller->current_row][i].customer_id == -1) { 
          pthread_mutex_lock(&mutex);      
          nsleep(sleep_time);
          reserveSeat(seller, i);
          pthread_mutex_unlock(&mutex);
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

  return NULL; // thread exits
}

void wakeup_all_seller_threads()
{
  pthread_mutex_lock(&mutex);
  pthread_cond_broadcast(&condition);
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
  printf("Group 1: Matthew Findlay, Kevin Velcich, Esai Morales\n");
  printf("Project 3 Output\n\n\n");
  printf("Auditorium:\n");
  printAuditorium(auditorium);
  
  exit(0);
  
}
