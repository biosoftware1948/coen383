#include "Job.h"
#include "Queue.h"
#include "CPU.h"
#include <stdlib.h>
#include "schedulingAlgorithms/SJF.h"

int main() {
    int NUM_JOBS = 3;

    // Not working for some reason
    int seed = time(NULL);
    srand(seed);

    Job* jobs = createJobs(NUM_JOBS);
    printAllJobs(jobs, NUM_JOBS);

    CPU* cpu = createCPU();

    //Have a function for each algo here that
    //takes the jobs and cpu
    //the algos can sort the jobs then use the queue
    //to put things on and off the cpu

    //RunRoundRobin(jobs, cpu)
    //RunHPF(jobs, cpu)
    //....
    //...
    RunSJF(cpu, jobs, NUM_JOBS);

    return 0;
}
