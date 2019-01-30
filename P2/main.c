#include "Job.h"
#include "Queue.h"
#include "CPU.h"
#include <stdlib.h>
#include "schedulingAlgorithms/SJF.h"
#include "schedulingAlgorithms/SRT.h"
#include "schedulingAlgorithms/HPFNP.h"
#include "schedulingAlgorithms/HPFP.h"

# define NUM_JOBS 10

int main() {
    Job* jobs = createJobs(NUM_JOBS);
    //sort_by_arrival_time(jobs, NUM_JOBS);

    // Printing out each job's name, arrival time, expected run time & priority
    report_print(jobs, NUM_JOBS);

    // First Come First Serve
    //RunFCFS(createCPU(), copyJobs(jobs, NUM_JOBS), NUM_JOBS);

    // Shortest Job First
    //RunSJF(createCPU(), copyJobs(jobs, NUM_JOBS), NUM_JOBS);

    // Shortest Remaining Time
    //RunSRT(createCPU(), copyJobs(jobs, NUM_JOBS), NUM_JOBS);

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
