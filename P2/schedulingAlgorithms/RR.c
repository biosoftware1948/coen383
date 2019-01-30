# include <assert.h>
# include "../CPU.h"
# include "../Job.h"
# include "../queue.h"
# include "RR.h"

bool processStarted(Job * jobs, int count){
    for (int i = 0; i < count; i++){
        if (jobs[i].remaining_service_time != 0 &&  jobs[i].remaining_service_time != jobs[i].service_time){
            return true;
        }
    }
    return false;
}

void RunRR(CPU *cpu, Job *jobs, unsigned jobsCount, int output){
    int completed = 0, i = 0;
    unsigned slice = 1;

    sort_by_arrival_time(jobs, jobsCount);

    Queue * queue = createQueue();

    while((cpu->global_time < 100 && completed < jobsCount) || processStarted(jobs, jobsCount)){

        // update queue
        while(jobs[i].arrival_time <= cpu->global_time && i < jobsCount)
            enQueue(queue, &jobs[i++]);

        // if jobs in queue
        while(!isEmpty(queue)){

            // get job at front of queue and remove it
            Job *job = getFrontQueueElement(queue);
            deQueue(queue);

            // run job for 1 slice
            if (job->remaining_service_time == job->service_time)
                job->start_time = cpu->global_time;

            giveCPUJob(cpu, job);
            runCurrentJob(cpu, slice, output);

            // put job back in queue if still not completed
            if (job->remaining_service_time > 0)
                enQueue(queue, job);
            else
                completed++;
                job->finish_time = cpu->global_time;

            // update queue
            while(jobs[i].arrival_time <= cpu->global_time && i < jobsCount)
                enQueue(queue, &jobs[i++]);
        }

        // if any jobs left, run idle until next job
        if (i < jobsCount)
            runIdle(cpu, jobs[i].arrival_time - cpu->global_time, output);
    }
    // printAllJobs(jobs, jobsCount);
}
