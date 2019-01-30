# include <assert.h>
# include "../CPU.h"
# include "../Job.h"
# include "../queue.h"
# include "FCFS.h"

void RunFCFS(CPU *cpu, Job *jobs, unsigned jobsCount){

    int completed = 0, i = 0;
    Queue *q = createQueue();

    sort_by_arrival_time(jobs, jobsCount);

    while(cpu->global_time < 100 && completed < jobsCount){

        while(jobs[i].arrival_time <= cpu->global_time && i < jobsCount)
            enQueue(q, &jobs[i++]);

        if(isEmpty(q)){
            if(i >= jobsCount) break;
            runIdle(cpu, jobs[i].arrival_time - cpu->global_time);

        } else {
            while(!isEmpty(q)){
                Job *j = getFrontQueueElement(q);
                deQueue(q);

                giveCPUJob(cpu, j);
                j->start_time = cpu->global_time;
                runCurrentJob(cpu, j->remaining_service_time);
                j->finish_time = cpu->global_time;
                completed++;
            }
        }
    }
    // printAllJobs(jobs, jobsCount);
}
