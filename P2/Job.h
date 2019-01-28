#ifndef JOB_H
#define JOB_H
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Job {
	int pid;
	int arrival_time;
	int service_time;
	int priority;
	int remaining_service_time;
	int start_time;
	int finish_time;
	int age;
} Job;

//create array of jobs
struct Job* createJobs(int number_of_jobs);

// prints job info
void jobInfo(struct Job job);

void printAllJobs(Job* jobs, int num_jobs);

// swap position of the jobs in the array
void swap_jobs_in_array(Job* job_array, int pos_1, int pos_2);

// function to get the response time of a job
int response_time(Job j);

// function to get the average response time
double avg_response_time(Job* j, int numJobs);

// function to get the average turnaround time
double avg_turnaround_time(Job* j, int numJobs);

// function to get the average waiting time
double avg_wait_time(Job* j, int numJobs);


void sort_by_arrival_time(Job* jobs, int size);

void sort_by_service_time(Job* jobs, int size);

void sort_by_priority(Job* jobs, int size);

void sort_by_remaining_service_time(Job* jobs, int size);

void sort_by_finish_time(Job* jobs, int size);

#endif
