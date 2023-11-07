#include <iostream>
#include <vector>
#include <list>
using namespace std;
bool feasible(const vector<int>& deadlines, list <int> J){
    int i = 1;
    int job;
    int n = J.size();
    while(i <= n){
        job = J.front();
        J.pop_front();
        if(i > deadlines[job-1]){
            return false;
        }
        i++;
    }
    return true;
}

void schedule(int n, const vector<int>& deadlines, list <int>& J){
    J.clear();
//    list <int> K;
    J.push_back(0);
    for(int i = 1; i < n; i++){
        J.push_back(i);

    }
}

int main() {
    vector<int> deadlines = {3, 1, 1, 3, 1, 3, 2};
    list<int> J;
    J.push_back(2);
    J.push_back(7);
    J.push_back(1);
    J.push_back(4);
    cout << feasible(deadlines, J);
    return 0;
}
