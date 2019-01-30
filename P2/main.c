#include "Job.h"
#include "Queue.h"
#include "CPU.h"
#include <stdlib.h>
#include "schedulingAlgorithms/FCFS.h"
#include "schedulingAlgorithms/SJF.h"
#include "schedulingAlgorithms/SRT.h"
#include "schedulingAlgorithms/RR.h"
#include "schedulingAlgorithms/HPFNP.h"
#include "schedulingAlgorithms/HPFP.h"

# define NUM_JOBS 30

int main() {
    // Seeding for Random
    int seed = time(NULL);
    srand(seed);

    // Output header
    printf("Group 1: Matthew Findlay, Kevin Velcich, Esai Morales\n");
    printf("Project 2 Output\n\n\n");

    Job* jobs = createJobs(NUM_JOBS),
        *j2 = createJobs(NUM_JOBS), *j3 = createJobs(NUM_JOBS),
        *j4 = createJobs(NUM_JOBS), *j5 = createJobs(NUM_JOBS);
    sort_by_arrival_time(jobs, NUM_JOBS);
    printf("Printing All Jobs:\n");
    report_print(jobs, NUM_JOBS); // Printing out each job's name, arrival time, expected run time & priority

    // First Come First Serve
    Job *jobsCopy = copyJobs(jobs, NUM_JOBS),
        *jc2 = copyJobs(j2, NUM_JOBS), *jc3 = copyJobs(j3, NUM_JOBS),
        *jc4 = copyJobs(j4, NUM_JOBS), *jc5 = copyJobs(j5, NUM_JOBS);
    RunFCFS(createCPU(), jobsCopy, NUM_JOBS, 1);
    RunFCFS(createCPU(), jc2, NUM_JOBS, 0);
    RunFCFS(createCPU(), jc3, NUM_JOBS, 0);
    RunFCFS(createCPU(), jc4, NUM_JOBS, 0);
    RunFCFS(createCPU(), jc5, NUM_JOBS, 0);
    printf("\nMETRICS:\n");
    print_metrics(jobsCopy, jc2, jc3, jc4, jc5, NUM_JOBS, 0);

    // Shortest Job First
    printf("\n\n\n===== Running Shortest Jobs First: =====\n");
    jobsCopy = copyJobs(jobs, NUM_JOBS),
        jc2 = copyJobs(j2, NUM_JOBS), jc3 = copyJobs(j3, NUM_JOBS),
        jc4 = copyJobs(j4, NUM_JOBS), jc5 = copyJobs(j5, NUM_JOBS);
    RunSJF(createCPU(), jobsCopy, NUM_JOBS, 1);
    RunSJF(createCPU(), jc2, NUM_JOBS, 0);
    RunSJF(createCPU(), jc3, NUM_JOBS, 0);
    RunSJF(createCPU(), jc4, NUM_JOBS, 0);
    RunSJF(createCPU(), jc5, NUM_JOBS, 0);
    printf("\nMETRICS:\n");
    print_metrics(jobsCopy, jc2, jc3, jc4, jc5, NUM_JOBS, 0);

    // Shortest Remaining Time
    printf("\n\n\n===== Running Shortest Remaining Time: =====\n");
    jobsCopy = copyJobs(jobs, NUM_JOBS),
        jc2 = copyJobs(j2, NUM_JOBS), jc3 = copyJobs(j3, NUM_JOBS),
        jc4 = copyJobs(j4, NUM_JOBS), jc5 = copyJobs(j5, NUM_JOBS);
    RunSRT(createCPU(), jobsCopy, NUM_JOBS, 1);
    RunSRT(createCPU(), jc2, NUM_JOBS, 0);
    RunSRT(createCPU(), jc3, NUM_JOBS, 0);
    RunSRT(createCPU(), jc4, NUM_JOBS, 0);
    RunSRT(createCPU(), jc5, NUM_JOBS, 0);
    printf("\nMETRICS:\n");
    print_metrics(jobsCopy, jc2, jc3, jc4, jc5, NUM_JOBS, 0);

    // Round Robin
    printf("\n\n\n===== Running Round Robin: =====\n");
    jobsCopy = copyJobs(jobs, NUM_JOBS),
        jc2 = copyJobs(j2, NUM_JOBS), jc3 = copyJobs(j3, NUM_JOBS),
        jc4 = copyJobs(j4, NUM_JOBS), jc5 = copyJobs(j5, NUM_JOBS);
    RunRR(createCPU(), jobsCopy, NUM_JOBS, 1);
    RunRR(createCPU(), jc2, NUM_JOBS, 0);
    RunRR(createCPU(), jc3, NUM_JOBS, 0);
    RunRR(createCPU(), jc4, NUM_JOBS, 0);
    RunRR(createCPU(), jc5, NUM_JOBS, 0);
    printf("\nMETRICS:\n");
    print_metrics(jobsCopy, jc2, jc3, jc4, jc5, NUM_JOBS, 0);

    //Highest Priority First (non-preemptive)
    printf("\n\n\n===== Running Highest Priority First (non-preemptive): =====\n");
    jobsCopy = copyJobs(jobs, NUM_JOBS),
        jc2 = copyJobs(j2, NUM_JOBS), jc3 = copyJobs(j3, NUM_JOBS),
        jc4 = copyJobs(j4, NUM_JOBS), jc5 = copyJobs(j5, NUM_JOBS);
    RunHPFNP(createCPU(), jobsCopy, NUM_JOBS, 1);
    RunHPFNP(createCPU(), jc2, NUM_JOBS, 0);
    RunHPFNP(createCPU(), jc3, NUM_JOBS, 0);
    RunHPFNP(createCPU(), jc4, NUM_JOBS, 0);
    RunHPFNP(createCPU(), jc5, NUM_JOBS, 0);
    printf("\nMETRICS:\n");
    print_metrics(jobsCopy, jc2, jc3, jc4, jc5, NUM_JOBS, 1);

    //Highest Priority First (preemptive)
    printf("\n\n\n===== Running Highest Priority First (preemptive): =====\n");
    jobsCopy = copyJobs(jobs, NUM_JOBS),
        jc2 = copyJobs(j2, NUM_JOBS), jc3 = copyJobs(j3, NUM_JOBS),
        jc4 = copyJobs(j4, NUM_JOBS), jc5 = copyJobs(j5, NUM_JOBS);
    RunHPFP(createCPU(), jobsCopy, NUM_JOBS, 1);
    RunHPFP(createCPU(), jc2, NUM_JOBS, 0);
    RunHPFP(createCPU(), jc3, NUM_JOBS, 0);
    RunHPFP(createCPU(), jc4, NUM_JOBS, 0);
    RunHPFP(createCPU(), jc5, NUM_JOBS, 0);
    printf("\nMETRICS:\n");
    print_metrics(jobsCopy, jc2, jc3, jc4, jc5, NUM_JOBS, 1);

    return 0;
}
