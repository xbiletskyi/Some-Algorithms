#include "greedy.h"
using namespace std;
int findBestJob(const vector<int>& vec, const vector<int>& takenJobs) {
    int minIndex = 0;
    int minValue = INT_MAX;

    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] < minValue && takenJobs[i] != 1) {
            minValue = vec[i];
            minIndex = i;
        }
    }

    return minIndex;
}
vector<int> findTasks(vector<vector<int>> &costsMatrix){
    vector<int> bestJobs;
    vector<int> takenJobs(costsMatrix.size(), 0);
    for (const auto & jobs : costsMatrix){
        int bestJobIndex = findBestJob(jobs, takenJobs);
        takenJobs[bestJobIndex] = 1;
        bestJobs.push_back(bestJobIndex);
    }
    return bestJobs;
}