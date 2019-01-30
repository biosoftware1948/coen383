# include <assert.h>
# include "../CPU.h"
# include "../Job.h"
# include "../queue.h"
# include "RR.h"

void RunRR(CPU *cpu, Job *jobs, unsigned jobsCount){
    int completed = 0, i = 0;
    unsigned slice = 1;

    sort_by_arrival_time(jobs, jobsCount);

    Queue * queue = createQueue();

    while(cpu->global_time < 100 && completed < jobsCount){

        // update queue with jobs that have arrived
        while(jobs[i].arrival_time <= cpu->global_time)
            enQueue(queue, &jobs[i++]);

        // if anything in the queue
        while(!isEmpty(queue)){

            // get job at front of queue and remove it
            Job *job = getFrontQueueElement(queue);
            deQueue(queue);

            // run job for 1 slice of quanta
            giveCPUJob(cpu, job);
            runCurrentJob(cpu, slice);

            // put job back in queue if still not completed
            if (job->remaining_service_time > 0)
                enQueue(queue, &job);
            else
                completed++;

            // update the queue with jobs that may have arrived in the meantime
            while(jobs[i].arrival_time <= cpu->global_time)
                enQueue(queue, &jobs[i++]);
        }
        // run idle until next job arrives
        runIdle(cpu, jobs[i].arrival_time - cpu->global_time);
    }
}
