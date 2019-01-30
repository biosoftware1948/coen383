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
    //RunFCFS(createCPU(), copyJobs(jobs, NUM_JOBS), NUM_JOBS);

    // Shortest Job First
    printf("\n\n\n===== Running Shortest Jobs First: =====\n");
    Job *jobsCopy = copyJobs(jobs, NUM_JOBS),
        *jc2 = copyJobs(j2, NUM_JOBS), *jc3 = copyJobs(j3, NUM_JOBS),
        *jc4 = copyJobs(j4, NUM_JOBS), *jc5 = copyJobs(j5, NUM_JOBS);
    RunSJF(createCPU(), jobsCopy, NUM_JOBS, 1);
    RunSJF(createCPU(), jc2, NUM_JOBS, 0);
    RunSJF(createCPU(), jc3, NUM_JOBS, 0);
    RunSJF(createCPU(), jc4, NUM_JOBS, 0);
    RunSJF(createCPU(), jc5, NUM_JOBS, 0);
    printf("\nMETRICS:\n");
    print_metrics(jobsCopy, jc2, jc3, jc4, jc5, NUM_JOBS);

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
    print_metrics(jobsCopy, jc2, jc3, jc4, jc5, NUM_JOBS);

    // Round Robin
    //RunRR(createCPU(), copyJobs(jobs, NUM_JOBS), NUM_JOBS);

    //Highest Priority First (non-preemptive)
    //RunHPFNP(createCPU(), copyJobs(jobs, NUM_JOBS), NUM_JOBS);

    //Highest Priority First (preemptive)
    //RunHPFP(createCPU(), j1, NUM_JOBS);


    // TODO: Report Outputs
    //time chart
    //Average turn around time
    //Avereage waiting time
    //Average response time
    //Algorithm Throughput (HPF for priority level and all together)
    // ensure calculation is only on jobs that ran

    return 0;
}
