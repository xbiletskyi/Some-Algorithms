#include "quickSort.h"
// FUNCTION IMPLEMENTATION AND ANALYSIS WERE TAKEN FROM https://www.geeksforgeeks.org/quick-sort/

/*
 * Best Case: Ω (N log (N))
 * The best-case scenario for quicksort occur when the pivot chosen at the each step divides the array into roughly equal halves.
 * In this case, the algorithm will make balanced partitions, leading to efficient Sorting.
 *
 * Average Case: θ ( N log (N))
 * Quicksort’s average-case performance is usually very good in practice, making it one of the fastest sorting Algorithm.
 *
 * Worst Case: O(N2)
 * The worst-case Scenario for Quicksort occur when the pivot at each step consistently results in highly unbalanced
 * partitions. When the array is already sorted and the pivot is always chosen as the smallest or largest element. To
 * mitigate the worst-case Scenario, various techniques are used such as choosing a good pivot (e.g., median of three)
 * and using Randomized algorithm (Randomized Quicksort ) to shuffle the element before sorting.
 */
using namespace  std;
int partition(vector<Job>& jobs, int start, int end)    //
{
    int pivotElement = jobs[end].profit;
    int i = start - 1;

    for (int j = start; j < end; j++)
    {
        if (jobs[j].profit > pivotElement)
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