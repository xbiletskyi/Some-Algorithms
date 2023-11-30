#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>
struct Job {
    int index;
    int deadline;
    int profit;
};

void quickSort(std::vector<Job>& jobs, int start, int end);

#endif // QUICKSORT_H
