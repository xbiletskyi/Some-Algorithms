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
void insert(list <int>& K, list<int> J, const vector<int>& deadlines, int toInsert){
    K.clear();
    copy(J.begin(), J.end(), back_inserter(K));
    auto it = K.end();
    int i = J.size();
    while(i > 0){
        --it;
        int job = J.back();
        J.pop_back();
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
void scheduleAlgorithm(const vector<int>& deadlines, list <int>& J){
    J.clear();
    list <int> K;
    J.push_back(0);
    for(int i = 1; i < deadlines.size(); i++){
        insert(K, J, deadlines, i);
        if(feasible(deadlines, K)){
            J = K;
        }
    }
}

list<int> launchSchedule(vector<Job> jobs){
    quickSort(jobs, 0, jobs.size() - 1);
    vector<int> deadlines;
    for(auto & job : jobs){
        int deadline = job.deadline;
        deadlines.push_back(deadline);
    }
    list<int> J;
    scheduleAlgorithm(deadlines, J);
    list<int> sequence;
    int total_profit = 0;
    for(auto & j: J){
        sequence.push_back(jobs[j].index);
        total_profit += jobs[j].profit;
    }
    cout << "\nTotal profit: " << total_profit;
    return sequence;
}










