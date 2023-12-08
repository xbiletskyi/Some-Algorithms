#include "greedy.h"
using namespace std;
int findBestJob(const vector<int>& vec, const vector<int>& takenJobs) { // O(n) complexity
    int minIndex = 0;
    int minValue = INT_MAX;

    for (int i = 0; i < vec.size(); ++i) {      // O(n) for() loop
        if (vec[i] < minValue && takenJobs[i] != 1) {
            minValue = vec[i];
            minIndex = i;
        }
    }

    return minIndex;
}
vector<int> findTasks(vector<vector<int>> &costsMatrix){        // O(n^2) complexity
    vector<int> bestJobs;
    vector<int> takenJobs(costsMatrix.size(), 0);       // O(n) complexity initialization
    for (const auto & jobs : costsMatrix){
        int bestJobIndex = findBestJob(jobs, takenJobs);    // O(n) function; executed n times
        takenJobs[bestJobIndex] = 1;
        bestJobs.push_back(bestJobIndex);
    }
    return bestJobs;
}