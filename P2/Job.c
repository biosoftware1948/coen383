#include "Job.h"

//job utils
int newServiceTime() {
	int service_time = rand() %11;
	if (service_time == 0) {
		service_time = 1;
	}
	return service_time;
}
//job utils
int newPriority() {
	int priority = rand() % 5;
	if (priority == 0) {
		priority = 1;
	}
	return priority;
}

//create new job
void newJob(Job* job, int pid) {
	job->pid = pid;
	job->arrival_time = rand() % 100;
	job->service_time = newServiceTime();
	job->priority = newPriority();

	job->remaining_service_time = job->service_time;
	job->start_time = -1;
	job->finish_time = -1;
	job->age = 0;
}

//Create array of jobs
struct Job* createJobs(int number_of_jobs) {
	struct Job* jobs = malloc(sizeof(Job) * number_of_jobs);
	for (int i = 0; i < number_of_jobs; ++i) {
		newJob(&jobs[i], i);
	}
	return jobs;
}

//print job info
void jobInfo(struct Job job) {
	printf("Job id: %d\n", job.pid);
	printf("\tArrival Time: %d\n", job.arrival_time);
	printf("\tPriority: %d", job.priority);
	printf("\tService Time: %d", job.service_time);
	printf("\tRemaining Service Time: %d", job.remaining_service_time);
	printf("\tStart Time: %d", job.start_time);
	printf("\tFinish Time: %d", job.finish_time);
	printf("\tAge: %d", job.age);
}


// swap position of the jobs in the array
void swap_jobs_in_array(Job* job_array, int pos_1, int pos_2) {
	struct Job tmp;

	tmp.pid = job_array[pos_1].pid;
	tmp.arrival_time = job_array[pos_1].arrival_time;
	tmp.service_time = job_array[pos_1].service_time;
	tmp.priority = job_array[pos_1].priority;
	tmp.remaining_service_time = job_array[pos_1].remaining_service_time;
	tmp.start_time = job_array[pos_1].start_time;
	tmp.finish_time = job_array[pos_1].finish_time;
	
	job_array[pos_1].pid = job_array[pos_2].pid;
	job_array[pos_1].arrival_time = job_array[pos_2].arrival_time;
	job_array[pos_1].service_time = job_array[pos_2].service_time;
	job_array[pos_1].priority = job_array[pos_2].priority;
	job_array[pos_1].remaining_service_time = job_array[pos_2].remaining_service_time;
	job_array[pos_1].start_time = job_array[pos_2].start_time;
	job_array[pos_1].finish_time = job_array[pos_2].finish_time;
	
	job_array[pos_2].pid = tmp.pid;
	job_array[pos_2].arrival_time = tmp.arrival_time;
	job_array[pos_2].service_time = tmp.service_time;
	job_array[pos_2].priority = tmp.priority;
	job_array[pos_2].remaining_service_time = tmp.remaining_service_time;
	job_array[pos_2].start_time = tmp.start_time;
	job_array[pos_2].finish_time = tmp.finish_time;
}

void sort_by_arrival_time(Job* jobs, int size) {
	for(int i = 0; i < size; i++) {
		for(int j = i + 1; j < size; j++) {
			if(jobs[i].arrival_time > jobs[j].arrival_time) {
				swap_jobs_in_array(jobs, i, j);
			}
		}
	}
}

void sort_by_service_time(Job* jobs, int size) {
	for(int i = 0; i < size; i++) {
		for(int j = i + 1; j < size; j++) {
			if(jobs[i].service_time > jobs[j].service_time) {
				swap_jobs_in_array(jobs, i, j);
			}
		}
	}
}

void sort_by_priority(Job* jobs, int size) {
	for(int i = 0; i < size; i++) {
		for(int j = i + 1; j < size; j++) {
			if(jobs[i].priority > jobs[j].priority) {
				swap_jobs_in_array(jobs, i, j);
			}
		}
	}
}

void sort_by_remaining_service_time(Job* jobs, int size) { 
	for(int i = 0; i < size; i++) {
		for(int j = i+1; j < size; j++) {
			if(jobs[i].remaining_service_time > jobs[j].remaining_service_time) {
				swap_jobs_in_array(jobs, i, j);
			}
		}
	}
}

void sort_by_finish_time(Job* jobs, int size) {
	for(int i = 0; i < size; i++) {
		for(int j = i+1; j < size; j++) {
			if(jobs[i].finish_time > jobs[j].finish_time) {
				swap_jobs_in_array(jobs, i, j);
			}
		}
	}

}

int get_job_response_time(Job j) {
	return (j.start_time - j.arrival_time);
}

double avg_response_time_in_job_array(Job* jobs, int numJobs) {
	double avg = 0;
	int notRunJobs = 0;
	// add up all of the response times
	for(int i = 0; i < numJobs; i++) {
		if(jobs[i].start_time != -1) {
			avg += (jobs[i].start_time - jobs[i].arrival_time);
		}
		else {
			notRunJobs++;
		}
	}
	// find the average response time
	return (avg / (numJobs - notRunJobs));
}

double avg_turnaround_time(Job* jobs, int numJobs) {
	double avg = 0;
	int notRunJobs = 0;
	// add up all of the turnaround times
	for(int i = 0; i < numJobs; i++) {
		if(jobs[i].start_time != -1) {
			avg += (jobs[i].finish_time - jobs[i].arrival_time);
		}
		else {
			notRunJobs++;
		}
	}
	// find the average turnaround time
	return (avg / (numJobs - notRunJobs));
}

double avg_wait_time(Job* jobs, int numJobs) {
	double avg = 0;
	int notRunJobs = 0;
	// add up all of the wait times
	for(int i = 0; i < numJobs; i++) {
		if(-1 != jobs[i].start_time) {
			avg += (jobs[i].finish_time - jobs[i].service_time);
		}
		else {
			notRunJobs++;
		}
	}
	// find the average wait time
	return (avg / (numJobs - notRunJobs));
}

