#include "ModifiedSchedulingWithDeadlines.h"

using namespace std;
class DisjointSet {
private:
    int* parent;
public:
    explicit DisjointSet(int n){
        parent = new int[n + 1];
        for (int i = 0; i <= n; i++){
            parent[i] = i;
        }
    }
    ~DisjointSet(){
        delete[] parent;
    }

    int find(int x){
        if (x == parent[x]){
            return x;
        }
        else{
            return parent[x] = find(parent[x]);
        }
    }
    void unionSets(int x, int y){
        parent[y] = x;
    }
};


int findMaxDeadline(const vector<int>& deadlines){
    int min = deadlines[0];
    for (int i = 1; i < deadlines.size(); i++){
        if(min < deadlines[i]){
            min = deadlines[i];
        }
    }
    return min;
}
bool feasible_check(const vector<int>& deadlines, const list <int>& J){
    int i = 0;
    for (int job : J) {
        if (++i > deadlines[job]) {
            return false;
        }
    }
    return true;
}
void modifiedScheduleAlgorithm(const vector<int>& deadlines, list<int>& J) {
    J.clear();
    int n = findMaxDeadline(deadlines);
    DisjointSet disjointSets(n);
    vector<int> schedule(n+1, -1);
    for (int i = 0; i < deadlines.size(); i++){
        int currentDeadline = deadlines[i];
        int free = disjointSets.find(currentDeadline);
        if (free > 0){
            int slotToMerge = disjointSets.find(free - 1);
            disjointSets.unionSets(slotToMerge, free);
            schedule[free] = i;
        }
    }
    for (int i = 1; i < schedule.size(); i++){
        if(schedule[i] == -1){
            continue;
        }
        else{
            J.push_back(schedule[i]);
        }
    }
}

list<int> launchModifiedSchedule(vector<Job> jobs){
    quickSort(jobs, 0, jobs.size() - 1);
    vector<int> deadlines;
    for(auto & job : jobs){
        int deadline = job.deadline;
        deadlines.push_back(deadline);
    }
    list<int> J;
    modifiedScheduleAlgorithm(deadlines, J);
    list<int> sequence;
    int total_profit = 0;
    for(auto & j: J){
        sequence.push_back(jobs[j].index);
        total_profit += jobs[j].profit;
    }
    if (feasible_check(deadlines, J)){
        cout << "\nThe sequence is feasible";
        cout << "\nTotal profit: " << total_profit;
    }
    else{
        cout <<"\nError";
    }
    return sequence;

}