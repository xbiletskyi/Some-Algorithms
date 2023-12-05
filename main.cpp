#include <iostream>
#include <ctime>
#include "SchedulingWithDeadlines.h"
#include "ModifiedSchedulingWithDeadlines.h"
#include "greedy.h"
#include "Hungarian.h"
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


//    vector<vector<int>> assigning = {
//            {10, 5, 5},
//            {2, 4, 10},
//            {5, 1, 7}
//    };
//    vector<int> bestTasks = findTasks(assigning);
//    for (auto & jobs : assigning){
//        for (auto & job : jobs){
//            cout << " " << job << " ";
//        }
//        cout << "\n";
//    }
//    for (int i = 0; i < bestTasks.size(); i++){
////        cout << "For worker " << i + 1 << " best work is: " << bestTasks[i] + 1 << "\n";
//        for(int j = 0; j < bestTasks.size(); j++){
//            if (j != bestTasks[i]){
//                cout << " . ";
//            }
//            else{
//                cout << " x ";
//            }
//        }
//        cout << "\n";
//    }
//    cout << "\n";
//    return 0;
//    vector<vector<int>> assigning = {
//            {88, 55, 92, 14},
//            {66, 98, 86, 31},
//            {97, 22, 9, 49},
//            {15, 44, 25, 18}
//    };
    vector<vector<int>> assigning = {
            {90, 25, 88, 66, 4, 55, 81, 66, 74, 22},
            {25, 44, 36, 99, 97, 31, 51, 19, 2, 69},
            {71, 75, 46, 50, 2, 12, 87, 47, 45, 90},
            {10, 92, 24, 46, 14, 1, 87, 40, 89, 22},
            {3, 90, 82, 36, 11, 46, 14, 93, 83, 2},
            {14, 44, 24, 78, 9, 91, 17, 56, 40, 36},
            {32, 26, 74, 31, 93, 91, 7, 44, 72, 36},
            {84, 3, 86, 50, 50, 73, 36, 76, 61, 72},
            {97, 13, 83, 49, 87, 36, 62, 54, 51, 41},
            {67, 74, 75, 97, 5, 43, 77, 59, 34, 6}
    };
//    vector<vector<int>> assigning = {
//            {10, 5, 5},
//            {2, 4, 10},
//            {5, 1, 7}
//    };
    vector<int> optimalJobs =  hungarianAlgorithm(assigning);
    int totalCost = 0;
    for (int i = 0; i < optimalJobs.size(); i++){
        for(int j = 0; j < optimalJobs.size(); j++){
            if (j != optimalJobs[i]){
                cout << " . ";
            }
            else{
                totalCost += assigning[i][j];
                cout << " x ";
            }
        }
        cout << "\n";
    }
    cout << totalCost <<"\n";
}