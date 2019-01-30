#include "Job.h"
#include "Queue.h"
#include "CPU.h"
#include <stdlib.h>
#include "schedulingAlgorithms/SJF.h"
#include "schedulingAlgorithms/SRT.h"
#include "schedulingAlgorithms/HPFNP.h"
#include "schedulingAlgorithms/HPFP.h"

int main() {
    int NUM_JOBS = 10;

    // Not working for some reason
    int seed = time(NULL);
    srand(seed);

    Job* jobs = createJobs(NUM_JOBS);
    printAllJobs(jobs, NUM_JOBS);

    //CPU* cpu = createCPU();

    //Have a function for each algo here that
    //takes the jobs and cpu
    //the algos can sort the jobs then use the queue
    //to put things on and off the cpu

    //First Come First Serve
    RunFCFS(createCPU(), copyJobs(jobs, NUM_JOBS), NUM_JOBS);

    //Round Robin
    // RunRR(createCPU(), copyJobs(jobs, NUM_JOBS), NUM_JOBS);

    //RunHPF(jobs, cpu)
    //....
    //...

    //Shortest Job First
    //RunSJF(createCPU(), copyJobs(jobs, NUM_JOBS), NUM_JOBS);

    //Shortest Remaining Time
    //RunSRT(createCPU(), copyJobs(jobs, NUM_JOBS), NUM_JOBS);

    //Highest Priority First (Non-preemptive)
    //RunHPFNP(createCPU(), copyJobs(jobs, NUM_JOBS), NUM_JOBS);

    //Highest Priority First (Preemptive)
    //RunHPFP(createCPU(), copyJobs(jobs), NUM_JOBS);
    return 0;
}
