# include <iostream>
# include <stdlib.h>
# include <time.h>
# include "CPU.h"
# include "Process.h"

extern const unsigned RUN_TIME = 60000; // milliseconds
extern const unsigned JOB_COUNT = 150;
extern const unsigned NUM_PAGES = 100;

int main() {
    srand(time(NULL));

    std::cout << "running" << std::endl;
    // generate processes
    CPU();
}
