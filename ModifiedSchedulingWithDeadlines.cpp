#include "ModifiedSchedulingWithDeadlines.h"

using namespace std;
class DisjointSet {
private:
    int* parent;
public:
    explicit DisjointSet(int n){        // O(n) complexity
        parent = new int[n + 1];
        for (int i = 0; i <= n; i++){
            parent[i] = i;
        }
    }
    ~DisjointSet(){             // O(1) complexity
        delete[] parent;
    }

    int find(int x){            // O(logn) complexity on average, O(n) worst-case; n - length of parent[]
        if (x == parent[x]){
            return x;
        }
        else{
            return parent[x] = find(parent[x]);
        }
    }
    void unionSets(int x, int y){   // O(1) complexity
        parent[y] = x;
    }
};


int findMaxDeadline(const vector<int>& deadlines){  // O(n) complexity
    int min = deadlines[0];
    for (int i = 1; i < deadlines.size(); i++){
        if(min < deadlines[i]){
            min = deadlines[i];
        }
    }
    return min;
}
bool feasible_check(const vector<int>& deadlines, const list <int>& J){     // is not a part of the algorithm itself
    int i = 0;
    for (int job : J) {
        if (++i > deadlines[job]) {
            return false;
        }
    }
    return true;
}
void modifiedScheduleAlgorithm(const vector<int>& deadlines, list<int>& J) {    // O(nlogm) complexity; n - deadlines.size(), m - max(deadlines)
    J.clear();
    int n = findMaxDeadline(deadlines);     // O(n) complexity; executed once
    DisjointSet disjointSets(n);            // O(n) complexity; executed once
    vector<int> schedule(n+1, -1);  // O(n) complexity; executed once
    for (int i = 0; i < deadlines.size(); i++){
        int currentDeadline = deadlines[i];
        int free = disjointSets.find(currentDeadline);      // O(logm) function; executed n times; m - max(deadlines)
        if (free > 0){
            int slotToMerge = disjointSets.find(free - 1);      // O(logm) function; executed n times; m - max(deadlines)
            disjointSets.unionSets(slotToMerge, free);       // O(1) function; executed n times
            schedule[free] = i;
        }
    }
    for (int i = 1; i < schedule.size(); i++){      // O(n) for() loop; executed once
        if(schedule[i] == -1){
            continue;
        }
        else{
            J.push_back(schedule[i]);
        }
    }
}

list<int> launchModifiedSchedule(vector<Job> jobs){
    quickSort(jobs, 0, jobs.size() - 1);        // O(nlogn) function; executed once
    vector<int> deadlines;
    for(auto & job : jobs){                           // O(n) function; executed once
        int deadline = job.deadline;
        deadlines.push_back(deadline);
    }
    list<int> J;
    modifiedScheduleAlgorithm(deadlines, J);            // O(nlogm) function; executed once; m - max(deadlines), n - deadlines.size()
    list<int> sequence;
    int total_profit = 0;
    for(auto & j: J){                                // O(m) function; executed once
        sequence.push_back(jobs[j].index);
        total_profit += jobs[j].profit;
    }
    if (feasible_check(deadlines, J)){                     // solution check (optional); O(n) complexity
        cout << "\nThe sequence is feasible";
        cout << "\nTotal profit: " << total_profit;
    }
    else{
        cout <<"\nError";
    }
    return sequence;

}