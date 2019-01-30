#include "Job.h"
#include <math.h>

//job utils to create a service time
int newServiceTime() {
	int service_time = rand() %11;
	if (service_time == 0) {
		service_time = 1;
	}
	return service_time;
}
//job utils to create priority
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

void copyJob(Job *job, Job *jobCopy) {
	jobCopy->pid = job->pid;
	jobCopy->arrival_time = job->arrival_time;
	jobCopy->service_time = job->service_time;
	jobCopy->priority = job->priority;

	jobCopy->remaining_service_time = job->service_time;
	jobCopy->start_time = -1;
	jobCopy->finish_time = -1;
	jobCopy->age = 0;
}

struct Job* copyJobs(Job *jobs, int number_of_jobs) {
	struct Job* jobsCopy = malloc(sizeof(Job) * number_of_jobs);
	for (int i = 0; i < number_of_jobs; ++i) {
		copyJob(&jobs[i], &jobsCopy[i]);
	}
	return jobsCopy;
}

//print job info
void jobInfo(struct Job job) {
	printf("----------------------------\n");
	printf("Job id: %d\n", job.pid);
	printf("\tArrival Time: %d\n", job.arrival_time);
	printf("\tPriority: %d\n", job.priority);
	printf("\tService Time: %d\n", job.service_time);
	printf("\tRemaining Service Time: %d\n", job.remaining_service_time);
	printf("\tStart Time: %d\n", job.start_time);
	printf("\tFinish Time: %d\n", job.finish_time);
	printf("\tAge: %d\n", job.age);
	printf("----------------------------\n");
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

void printAllJobs(Job* jobs, int num_jobs) {
	for(int i = 0; i < num_jobs; ++i) {
		jobInfo(jobs[i]);
	}
}

void report_print(Job * jobs, int size) {
	for (int i = 0; i < size; i++) {
		printf("Job %d,   Arrival Time=%d,   Service Time=%d,   priority %d\n",
			jobs[i].pid, jobs[i].arrival_time, jobs[i].service_time, jobs[i].priority);
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
		if(jobs[i].finish_time != -1) {
			avg += (jobs[i].start_time - jobs[i].arrival_time);
		}
		else {
			notRunJobs++;
		}
	}
	// find the average response time
	return (avg / (numJobs - notRunJobs));
}

void print_response_time(Job* jobs, int numJobs) {
	double avg = 0;
	int notRunJobs = 0;
	// add up all of the response times
	for(int i = 0; i < numJobs; i++) {
		if(jobs[i].finish_time != -1) {
			printf("      - Job %d: %d,\t", jobs[i].pid, (jobs[i].start_time - jobs[i].arrival_time));
			avg += (jobs[i].start_time - jobs[i].arrival_time);
		}
		else {
			notRunJobs++;
		}
	}
	// find the average response time
	printf("\n      AVERAGE: %f\n", (avg / (numJobs - notRunJobs)));
}

double avg_wait_time(Job* jobs, int numJobs) {
	double avg = 0;
	int notRunJobs = 0;
	// add up all of the wait times
	for(int i = 0; i < numJobs; i++) {
		if(-1 != jobs[i].finish_time) {
			avg += jobs[i].finish_time - jobs[i].arrival_time - jobs[i].service_time;
		}
		else {
			notRunJobs++;
		}
	}
	// find the average wait time
	return (avg / (numJobs - notRunJobs));
}

void print_avg_wait_time(Job* jobs, int numJobs) {
	double avg = 0;
	int notRunJobs = 0;
	// add up all of the wait times
	for(int i = 0; i < numJobs; i++) {
		if(-1 != jobs[i].finish_time) {
			printf("      - Job %d: %d,\t", jobs[i].pid, jobs[i].finish_time - jobs[i].arrival_time - jobs[i].service_time);
			avg += jobs[i].finish_time - jobs[i].arrival_time - jobs[i].service_time;
		}
		else {
			notRunJobs++;
		}
	}
	// find the average wait time
	printf("\n      AVERAGE: %f\n", (avg / (numJobs - notRunJobs)));
}

double avg_turnaround_time(Job* jobs, int numJobs) {
	double avg = 0;
	int notRunJobs = 0;
	// add up all of the turnaround times
	for(int i = 0; i < numJobs; i++) {
		if(jobs[i].finish_time != -1) {
			avg += (jobs[i].finish_time - jobs[i].arrival_time);
		}
		else {
			notRunJobs++;
		}
	}
	// find the average turnaround time
	return (avg / (numJobs - notRunJobs));
}

void print_turn_arounds(Job * jobs, int numJobs) {
	double avg = 0;
	int notRunJobs = 0;
	// add up all of the wait times
	for(int i = 0; i < numJobs; i++) {
		if(-1 != jobs[i].finish_time) {
			avg += (jobs[i].finish_time - jobs[i].arrival_time);
			printf("      - Job %d: %d,\t", jobs[i].pid, jobs[i].finish_time - jobs[i].arrival_time);
		}
		else {
			notRunJobs++;
		}
	}
	// find the average wait time
	printf("\n      AVERAGE: %f\n", (avg / (numJobs - notRunJobs)));
}

double avg_5tat(Job *j1, Job *j2, Job *j3, Job *j4, Job *j5, int size) {
	int count = 5;

	double a1 = avg_turnaround_time(j1, size);
	double a2 = avg_turnaround_time(j2, size);
	double a3 = avg_turnaround_time(j3, size);
	double a4 = avg_turnaround_time(j4, size);
	double a5 = avg_turnaround_time(j5, size);


	if (fabs(a1) <= 0.0001) count --;
	if (fabs(a2) == 0.0001) count --;
	if (fabs(a3) == 0.0001) count --;
	if (fabs(a4) == 0.0001) count --;
	if (fabs(a5) == 0.0001) count --;

	if (count == 0) return 0;
	return (a1 + a2 + a3 + a4 + a5) / count;
}

double avg_5wait(Job *j1, Job *j2, Job *j3, Job *j4, Job *j5, int size) {
	int count = 5;

	double a1 = avg_wait_time(j1, size);
	double a2 = avg_wait_time(j2, size);
	double a3 = avg_wait_time(j3, size);
	double a4 = avg_wait_time(j4, size);
	double a5 = avg_wait_time(j5, size);

	return (a1 + a2 + a3 + a4 + a5) / count;
}

double avg_5response(Job *j1, Job *j2, Job *j3, Job *j4, Job *j5, int size) {
	int count = 5;

	double a1 = avg_response_time_in_job_array(j1, size);
	double a2 = avg_response_time_in_job_array(j2, size);
	double a3 = avg_response_time_in_job_array(j3, size);
	double a4 = avg_response_time_in_job_array(j4, size);
	double a5 = avg_response_time_in_job_array(j5, size);

	return (a1 + a2 + a3 + a4 + a5) / count;
}

void print_avg_5throughput(Job *j1, Job *j2, Job *j3, Job *j4, Job *j5, int size) {
	int count = 0;

	for (int i = 0; i < size; i++) {
		if (j1[i].finish_time != -1) count++;
		if (j2[i].finish_time != -1) count++;
		if (j3[i].finish_time != -1) count++;
		if (j4[i].finish_time != -1) count++;
		if (j5[i].finish_time != -1) count++;
	}

	printf("  Average Over 5 Runs: %f percent    %d out of %d.\n", (count * 1.0) / (size * 5) * 100, count, size * 5);
}

void print_avg_5throughput_hpf(Job *j1, Job *j2, Job *j3, Job *j4, Job *j5, int size) {
	int p1 = 0, p2 = 0, p3 = 0, p4 = 0, t1 = 0, t2 = 0, t3 = 0, t4 = 0;

	for (int i = 0; i < size; i++) {
		if (j1[i].priority == 1) {
			t1++;
			if (j1[i].finish_time != -1) p1++;
		} else if (j1[i].priority == 2) {
			t2++;
			if (j1[i].finish_time != -1) p2++;
		} else if (j1[i].priority == 3) {
			t3++;
			if (j1[i].finish_time != -1) p3++;
		} else if (j1[i].priority == 4) {
			t4++;
			if (j1[i].finish_time != -1) p4++;
		}

		if (j2[i].priority == 1) {
			t1++;
			if (j2[i].finish_time != -1) p1++;
		} else if (j2[i].priority == 2) {
			t2++;
			if (j2[i].finish_time != -1) p2++;
		} else if (j2[i].priority == 3) {
			t3++;
			if (j2[i].finish_time != -1) p3++;
		} else if (j2[i].priority == 4) {
			t4++;
			if (j2[i].finish_time != -1) p4++;
		}

		if (j3[i].priority == 1) {
			t1++;
			if (j3[i].finish_time != -1) p1++;
		} else if (j3[i].priority == 2) {
			t2++;
			if (j3[i].finish_time != -1) p2++;
		} else if (j3[i].priority == 3) {
			t3++;
			if (j3[i].finish_time != -1) p3++;
		} else if (j3[i].priority == 4) {
			t4++;
			if (j3[i].finish_time != -1) p4++;
		}

		if (j4[i].priority == 1) {
			t1++;
			if (j4[i].finish_time != -1) p1++;
		} else if (j4[i].priority == 2) {
			t2++;
			if (j4[i].finish_time != -1) p2++;
		} else if (j4[i].priority == 3) {
			t3++;
			if (j4[i].finish_time != -1) p3++;
		} else if (j4[i].priority == 4) {
			t4++;
			if (j4[i].finish_time != -1) p4++;
		}
	}
	printf("  Average Over 5 Runs:\n");
	printf("  - Priority 1: %f percent    %d out of %d.\n", (p1 * 1.0) / (t1 * 1.0) * 100, p1, t1);
	printf("  - Priority 2: %f percent    %d out of %d.\n", (p2 * 1.0) / (t2 * 1.0) * 100, p2, t2);
	printf("  - Priority 3: %f percent    %d out of %d.\n", (p3 * 1.0) / (t3 * 1.0) * 100, p3, t3);
	printf("  - Priority 4: %f percent    %d out of %d.\n", (p4 * 1.0) / (t4 * 1.0) * 100, p4, t4);
}

void print_metrics(Job *j1, Job *j2, Job *j3, Job *j4, Job *j5, int size, int hpf) {
	printf("-Turn Around Time:\n");
	printf("    For Shown Run:\n");
	print_turn_arounds(j1, size);
	printf("  Average Over 5 Runs: %f\n", avg_5tat(j1, j2, j3, j4, j5, size));

	printf("-Waiting Time:\n");
	printf("    For Shown Run:\n");
	print_avg_wait_time(j1, size);
	printf("  Average Over 5 Runs: %f\n", avg_5wait(j1, j2, j3, j4, j5, size));

	printf("-Response Time:\n");
	printf("    For Shown Run:\n");
	print_response_time(j1, size);
	printf("  Average Over 5 Runs: %f\n", avg_5response(j1, j2, j3, j4, j5, size));

	printf("-Throughput Rate:\n");
	if (hpf == 0) print_avg_5throughput(j1, j2, j3, j4, j5, size);
	else print_avg_5throughput_hpf(j1, j2, j3, j4, j5, size);
}
