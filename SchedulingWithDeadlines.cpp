#include "SchedulingWithDeadlines.h"
#include <algorithm>
using namespace  std;


bool feasible(const vector<int>& deadlines, const list <int>& J){
    int i = 0;
    for (int job : J) {
        if (++i > deadlines[job]) {
            return false;
        }
    }
    return true;
}
void insert(list <int>& K, list<int>& J, const vector<int>& deadlines, int toInsert){ // O(n) complexity (one for() loop)
    K.clear();
    copy(J.begin(), J.end(), back_inserter(K));     // O(n) copy; executed once
    auto it = K.end();
    auto itJ = J.end();
    int i = J.size();
    while(i > 0){
        --it;
        --itJ;
        int job = *itJ;
        if(deadlines[job] > deadlines[toInsert]){
            i--;
            continue;
        }
        else{
            K.insert(next(it), toInsert);
            return;
        }
    }
    K.push_front(toInsert);
}
void scheduleAlgorithm(const vector<int>& deadlines, list <int>& J){    /* O(n^2) complexity (one for() loop with nested
                                                                         O(n) functions) */
    J.clear();
    list <int> K;
    J.push_back(0);
    for(int i = 1; i < deadlines.size(); i++){
        insert(K, J, deadlines, i);     // O(n) function; executed n times => O(n^2)
        if(feasible(deadlines, K)){               // O(n) function; executed n times => O(n^2)
            J = K;
        }
    }
}

list<int> launchSchedule(vector<Job> jobs){
    quickSort(jobs, 0, jobs.size() - 1);    // quickSort complexity O(nlogn); see quickSort.cpp
    vector<int> deadlines;
    for(auto & job : jobs){                       // O(n) executed once
        int deadline = job.deadline;
        deadlines.push_back(deadline);
    }
    list<int> J;
    scheduleAlgorithm(deadlines, J);                 // O(n^2) executed once
    list<int> sequence;
    int total_profit = 0;
    for(auto & j: J){                             // O(n) executed once
        sequence.push_back(jobs[j].index);
        total_profit += jobs[j].profit;
    }
    cout << "\nTotal profit: " << total_profit;
    return sequence;
}










