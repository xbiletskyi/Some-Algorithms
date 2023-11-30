#include "quickSort.h"

using namespace  std;
int partition(vector<Job>& jobs, int start, int end)
{
    int pivotElement = jobs[end].profit;
    int i = start - 1;  // Index of smaller element

    for (int j = start; j < end; j++)
    {
        if (jobs[j].profit > pivotElement)  // Change the comparison condition
        {
            i++;
            swap(jobs[i], jobs[j]);
        }
    }

    swap(jobs[i + 1], jobs[end]);
    return i + 1;
}

void quickSort(vector<Job>& jobs, int start, int end)
{
    if (start < end)
    {
        int partitionIndex = partition(jobs, start, end);
        quickSort(jobs, start, partitionIndex - 1);
        quickSort(jobs, partitionIndex + 1, end);
    }
}