# include <assert.h>
#include <stdbool.h>
# include "../CPU.h"
# include "../Job.h"
# include "../queue.h"
# include "HPFNP.h"

static bool isComplete(
        struct Queue *p1, struct Queue *p2, struct Queue *p3, struct Queue *p4) {
    return isEmpty(p1) && isEmpty(p2) && isEmpty(p3) && isEmpty(p4);
}

static int getMinArrival(int a, int b) {
    if (a == -1) return b;
    return a < b ? a : b;
}

static Job *getNextJob(
        CPU *cpu, struct Queue *p1, struct Queue *p2, struct Queue *p3, struct Queue *p4) {
    Job *j1 = NULL, *j2 = NULL, *j3 = NULL, *j4 = NULL;
    if (!isEmpty(p1)) j1 = (getFrontQueueElement(p1));
    if (!isEmpty(p2)) j2 = (getFrontQueueElement(p2));
    if (!isEmpty(p3)) j3 = (getFrontQueueElement(p3));
    if (!isEmpty(p4)) j4 = (getFrontQueueElement(p4));

    if (j1 != NULL && j1->arrival_time <= cpu->global_time) return deQueue(p1);
    if (j2 != NULL && j2->arrival_time <= cpu->global_time) return deQueue(p2);
    if (j3 != NULL && j3->arrival_time <= cpu->global_time) return deQueue(p3);
    if (j4 != NULL && j4->arrival_time <= cpu->global_time) return deQueue(p4);

    int min_arrival = -1;
    if (j1 != NULL) min_arrival = getMinArrival(min_arrival, j1->arrival_time);
    if (j2 != NULL) min_arrival = getMinArrival(min_arrival, j2->arrival_time);
    if (j3 != NULL) min_arrival = getMinArrival(min_arrival, j3->arrival_time);
    if (j4 != NULL) min_arrival = getMinArrival(min_arrival, j4->arrival_time);
    assert(min_arrival != -1);

    if (j1 != NULL && j1->arrival_time == min_arrival) return deQueue(p1);
    if (j2 != NULL && j2->arrival_time == min_arrival) return deQueue(p2);
    if (j3 != NULL && j3->arrival_time == min_arrival) return deQueue(p3);
    if (j4 != NULL && j4->arrival_time == min_arrival) return deQueue(p4);
    assert(0);
    return NULL;
}

static unsigned timeToIdle(CPU *cpu, Job *nextJob) {
    return cpu->global_time >= nextJob->arrival_time
        ? 0
        : nextJob->arrival_time - cpu->global_time;
}

void RunHPFNP(CPU *cpu, Job *jobs, unsigned jobsCount, int output) {
    sort_by_arrival_time(jobs, jobsCount);

    Queue *priority1 = createQueue();
    Queue *priority2 = createQueue();
    Queue *priority3 = createQueue();
    Queue *priority4 = createQueue();

    for (int i = 0; i < jobsCount; i++) {
        switch(jobs[i].priority) {
            case 1:
                enQueue(priority1, &jobs[i]);
                break;
            case 2:
                enQueue(priority2, &jobs[i]);
                break;
            case 3:
                enQueue(priority3, &jobs[i]);
                break;
            case 4:
                enQueue(priority4, &jobs[i]);
                break;
            default:
                assert(0);
                break;
        }
    }

    while (cpu->global_time < 100 &&
            !isComplete(priority1, priority2, priority3, priority4)) {
        Job *next = getNextJob(cpu, priority1, priority2, priority3, priority4);
        int tti = timeToIdle(cpu, next);
        runIdle(cpu, tti, output);
        giveCPUJob(cpu, next);
        runCurrentJob(cpu, cpu->job->service_time, output);
    }
}
