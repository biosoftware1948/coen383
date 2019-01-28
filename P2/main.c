#include "Job.h"
#include "Queue.h"
#include "CPU.h"

int main() {
    int NUM_JOBS = 100;

    Job* jobs = createJobs(NUM_JOBS);
    printAllJobs(jobs, NUM_JOBS);

    CPU* cpu = createCPU();
    

    //Have a function for each algo here thatr
    //takes the jobs and cpu
    //the algos can sort the jobs then use the queue
    //to put things on and off the cpu

    //RunRoundRobin(jobs, cpu)
    //RunHPF(jobs, cpu)
    //....
    //...

    return 0;
}