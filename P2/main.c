#include "Job.h"
#include "Queue.h"
#include "CPU.h"
#include <stdlib.h>
#include "schedulingAlgorithms/SJF.h"
#include "schedulingAlgorithms/SRT.h"
#include "schedulingAlgorithms/HPFNP.h"
#include "schedulingAlgorithms/HPFP.h"

# define NUM_JOBS = 10;

int main() {
    //time chart
    //Average turn around time
    //Avereage waiting time
    //Average response time
    //Algorithm Throughput (HPF for priority level and all together)
    // ensure calculation is only on jobs that ran
    Job* jobs = createJobs(NUM_JOBS);
    //sort_by_arrival_time(jobs, NUM_JOBS);

    // Printing out each job's name, arrival time, expected run time & priority
    report_print(jobs, NUM_JOBS);



    Job *j1 = copyJobs(jobs, NUM_JOBS);//, *j2 = copyJobs(jobs), *j3 = copyJobs(jobs),
    //    *j4 = copyJobs(jobs), *j5 = copyJobs(jobs), *j6 = copyJobs(jobs);
    //Shortest Job First
    //RunSJF(createCPU(), copyJobs(jobs, NUM_JOBS), NUM_JOBS);

    //Shortest Remaining Time
    //RunSRT(createCPU(), copyJobs(jobs, NUM_JOBS), NUM_JOBS);

    //Highest Priority First (Non-preemptive)
    //RunHPFNP(createCPU(), copyJobs(jobs, NUM_JOBS), NUM_JOBS);

    //Highest Priority First (Preemptive)
    //RunHPFP(createCPU(), j1, NUM_JOBS);

    return 0;
}
