# include <assert.h>
#include <stdbool.h>
# include "../CPU.h"
# include "../Job.h"
# include "../queue.h"
# include "HPFNP.h"

bool isComplete(
        struct Queue *p1, struct Queue *p2, struct Queue *p3, struct Queue *p4) {
    return isEmpty(p1) && isEmpty(p2) && isEmpty(p3) && isEmpty(p4);
}

int getMinArrival(int a, int b) {
    if (a == -1) return b;
    return a < b ? a : b;
}

Job *getNextJob(
        CPU *cpu, struct Queue *p1, struct Queue *p2, struct Queue *p3, struct Queue *p4) {
    if (!isEmpty(p1) && cpu->global_time <= getFrontQueueElement(p1)->arrival_time)
        return deQueue(p1);
    if (!isEmpty(p2) && cpu->global_time <= getFrontQueueElement(p2)->arrival_time)
        return deQueue(p2);
    if (!isEmpty(p3) && cpu->global_time <= getFrontQueueElement(p3)->arrival_time)
        return deQueue(p3);
    if (!isEmpty(p4) && cpu->global_time <= getFrontQueueElement(p4)->arrival_time)
        return deQueue(p4);

    Job *j1 = NULL, *j2 = NULL, *j3 = NULL, *j4 = NULL;
    if (!isEmpty(p1)) j1 = (getFrontQueueElement(p1));
    if (!isEmpty(p2)) j2 = (getFrontQueueElement(p2));
    if (!isEmpty(p3)) j3 = (getFrontQueueElement(p3));
    if (!isEmpty(p4)) j4 = (getFrontQueueElement(p4));

    int min_arrival = -1;
    if (j1 != NULL) min_arrival = getMinArrival(min_arrival, j1->arrival_time);
    if (j2 != NULL) min_arrival = getMinArrival(min_arrival, j2->arrival_time);
    if (j3 != NULL) min_arrival = getMinArrival(min_arrival, j3->arrival_time);
    if (j4 != NULL) min_arrival = getMinArrival(min_arrival, j4->arrival_time);
    assert(min_arrival != -1);

    if (j1->arrival_time == min_arrival) return deQueue(p1);
    if (j2->arrival_time == min_arrival) return deQueue(p2);
    if (j3->arrival_time == min_arrival) return deQueue(p3);
    if (j4->arrival_time == min_arrival) return deQueue(p4);
    assert(0);
    return NULL;
}

unsigned timeToIdle(
        CPU *cpu, struct Queue *p1, struct Queue *p2, struct Queue *p3, struct Queue *p4) {
    Job *nextJob = getNextJob(cpu, p1, p2, p3, p4);
    printf("Next job id: %d\n", nextJob->pid);
    printf("Arrival time: %d\n", nextJob->arrival_time);
    printf("Global time: %d\n", cpu->global_time);
    return cpu->global_time >= nextJob->arrival_time
        ? 0
        : nextJob->arrival_time - cpu->global_time;
}

void RunHPFNP(CPU *cpu, Job *jobs, unsigned jobsCount) {
    sort_by_arrival_time(jobs, jobsCount);

    Queue *priority1 = createQueue();
    Queue *priority2 = createQueue();
    Queue *priority3 = createQueue();
    Queue *priority4 = createQueue();

    for (int i = 0; i < jobsCount; i++) {
        switch(jobs[i].priority) {
            case 1:
                enQueue(priority1, jobs[i]);
                break;
            case 2:
                enQueue(priority2, jobs[i]);
                break;
            case 3:
                enQueue(priority3, jobs[i]);
                break;
            case 4:
                enQueue(priority4, jobs[i]);
                break;
            default:
                assert(0);
                break;
        }
    }

    while (!isEmpty(priority1)) {
        Job *j = getFrontQueueElement(priority1);
        deQueue(priority1);
        jobInfo(*j);
    }

    /*while (cpu->global_time < 100 &&
            !isComplete(priority1, priority2, priority3, priority4)) {
        printf("STARTING WHILE LOOP\n");
        int tti = timeToIdle(cpu, priority1, priority2, priority3, priority4);
        printf("TIME TO IDLE = %d\n", tti);
        runIdle(cpu, tti);
        Job *next = getNextJob(cpu, priority1, priority2, priority3, priority4);
    }*/
}
