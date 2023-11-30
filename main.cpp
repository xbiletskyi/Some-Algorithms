#include <iostream>
#include <ctime>
#include "SchedulingWithDeadlines.h"
#include "ModifiedSchedulingWithDeadlines.h"
#include "greedy.h"
using namespace std;

vector<Job> generateJobs(int n) {
    vector<Job> jobs;
    srand(static_cast<unsigned>(time(nullptr)));

    for (int i = 1; i <= n; i++) {
        int deadline = rand() % (n/3) + 1;
//        int deadline = rand() % n + 1;
        int profit = rand() % (n*2) + 1;

        jobs.push_back({i, deadline, profit});
    }

    return jobs;
}



int main() {
//    vector<Job> jobs = {
//            {1, 2, 40},
//            {2, 4, 15},
//            {3, 3, 60},
//            {4, 2, 20},
//            {5, 3, 10},
//            {6, 1, 45},
//            {7, 1, 55},
//    };
//    vector<Job> jobs = generateJobs(100);
//    clock_t start = clock();
//    list<int> sequence = launchModifiedSchedule(jobs);
//    clock_t end = clock();
//    cout << "\n" << "Elapsed time" << double(end - start) / CLOCKS_PER_SEC << " seconds" << "\n";
//    for(const int& num : sequence){
//        cout << num << " ";
//    }
//    jobs = generateJobs(10000);
//    start = clock();
//    sequence = launchSchedule(jobs);
//    end = clock();
//    cout << "\n" << "Elapsed time" << double(end - start) / CLOCKS_PER_SEC << " seconds" << "\n";
//    for(const int& num : sequence){
//        cout << num << " ";
//    }


    vector<vector<int>> assigning = {
            {10, 5, 5},
            {2, 4, 10},
            {5, 1, 7}
    };
    vector<int> bestTasks = findTasks(assigning);
    for (auto & jobs : assigning){
        for (auto & job : jobs){
            cout << " " << job << " ";
        }
        cout << "\n";
    }
    for (int i = 0; i < bestTasks.size(); i++){
//        cout << "For worker " << i + 1 << " best work is: " << bestTasks[i] + 1 << "\n";
        for(int j = 0; j < bestTasks.size(); j++){
            if (j != bestTasks[i]){
                cout << " . ";
            }
            else{
                cout << " x ";
            }
        }
        cout << "\n";
    }
    cout << "\n";
    return 0;
}