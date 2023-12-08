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
        int profit = rand() % (n*2) + 1;

        jobs.push_back({i, deadline, profit});
    }

    return jobs;
}

void launch_basic_schedule(){
    cout << "1. Use an example" << endl;
    cout << "2. Manual input" << endl;
    cout << "3. Random generating" << endl;
    int choice;
    cin >> choice;
    vector<Job> jobs;
    clock_t start;
    clock_t end;
    list<int> sequence;
    int index;
    switch(choice){
        case 1: {
            jobs = {
                    {1, 2, 40},
                    {2, 4, 15},
                    {3, 3, 60},
                    {4, 2, 20},
                    {5, 3, 10},
                    {6, 1, 45},
                    {7, 1, 55},
            };
            start = clock();
            sequence = launchSchedule(jobs);
            end = clock();
            cout << "\n" << "Elapsed time" << double(end - start) / CLOCKS_PER_SEC << " seconds" << "\n";
            for (const int &num: sequence) {
                cout << num << " ";
            }
            cout << endl;
            return;
        }
        case 2: {
            cout << "Enter -1 to stop" << endl;
            index = 1;
            while (true) {
                Job job{};
                job.index = index++;
                cout << "Enter job's deadline: ";
                cin >> job.deadline;
                cout << "Enter job's profit: ";
                cin >> job.profit;
                if (job.deadline == -1 || job.profit == -1) {
                    break;
                } else {
                    jobs.push_back(job);
                }
            }
            start = clock();
            sequence = launchSchedule(jobs);
            end = clock();
            cout << "\n" << "Elapsed time" << double(end - start) / CLOCKS_PER_SEC << " seconds" << "\n";
            for (const int &num: sequence) {
                cout << num << " ";
            }
            cout << endl;
            return;
        }
        case 3: {
            cout << "Enter number of jobs to be generated: " << endl;
            int quantity;
            cin >> quantity;
            jobs = generateJobs(quantity);
            start = clock();
            sequence = launchSchedule(jobs);
            end = clock();
            cout << "\n" << "Elapsed time" << double(end - start) / CLOCKS_PER_SEC << " seconds" << "\n";
            for (const int &num: sequence) {
                cout << num << " ";
            }
            cout << endl;
            return;
        }
    }
}

void launch_modified_schedule(){
    cout << "1. Use an example" << endl;
    cout << "2. Manual input" << endl;
    cout << "3. Random generating" << endl;
    int choice;
    cin >> choice;
    vector<Job> jobs;
    clock_t start;
    clock_t end;
    list<int> sequence;
    int index;
    switch(choice){
        case 1: {
            jobs = {
                    {1, 2, 40},
                    {2, 4, 15},
                    {3, 3, 60},
                    {4, 2, 20},
                    {5, 3, 10},
                    {6, 1, 45},
                    {7, 1, 55},
            };
            start = clock();
            sequence = launchModifiedSchedule(jobs);
            end = clock();
            cout << "\n" << "Elapsed time" << double(end - start) / CLOCKS_PER_SEC << " seconds" << "\n";
            for (const int &num: sequence) {
                cout << num << " ";
            }
            cout << endl;
            return;
        }
        case 2: {
            cout << "Enter -1 to stop";
            index = 1;
            while (true) {
                Job job{};
                job.index = index++;
                cout << "Enter job's deadline: ";
                cin >> job.deadline;
                cout << "Enter job's profit: ";
                cin >> job.profit;
                if (job.deadline == -1 || job.profit == -1) {
                    break;
                } else {
                    jobs.push_back(job);
                }
            }
            start = clock();
            sequence = launchModifiedSchedule(jobs);
            end = clock();
            cout << "\n" << "Elapsed time" << double(end - start) / CLOCKS_PER_SEC << " seconds" << "\n";
            for (const int &num: sequence) {
                cout << num << " ";
            }
            cout << endl;
            return;
        }
        case 3: {
            cout << "Enter number of jobs to be generated: " << endl;
            int quantity;
            cin >> quantity;
            jobs = generateJobs(quantity);
            start = clock();
            sequence = launchModifiedSchedule(jobs);
            end = clock();
            cout << "\n" << "Elapsed time" << double(end - start) / CLOCKS_PER_SEC << " seconds" << "\n";
            for (const int &num: sequence) {
                cout << num << " ";
            }
            cout << endl;
            return;
        }
    }
}


void launch_greedy_assigning(){
    cout << "1. Example" << endl;
    cout << "2. Manual input" << endl;
    vector<vector<int>> assigning;
    vector<int> bestTasks;
    int totalCost = 0;
    int choice;
    cin >> choice;
    clock_t start;
    clock_t end;
    switch(choice){
        case 1: {
            assigning = {
                    {10, 5, 5},
                    {2,  4, 10},
                    {5,  1, 7}
            };
            start = clock();
            bestTasks = findTasks(assigning);
            end = clock();
            cout << "\n" << "Elapsed time" << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
            for (auto &jobs: assigning) {
                for (auto &job: jobs) {
                    cout << " " << job << " ";
                }
                cout << endl;
            }
            cout << endl;
            for (int i = 0; i < bestTasks.size(); i++) {
                for (int j = 0; j < bestTasks.size(); j++) {
                    if (j != bestTasks[i]) {
                        cout << " . ";
                    } else {
                        totalCost += assigning[i][j];
                        cout << " x ";
                    }
                }
                cout << endl;
            }
            cout << "Total profit is: " << totalCost << endl;
            cout << endl;
            return;
        }
        case 2: {
            cout << "Enter the size of the matrix: " << endl;
            int size;
            cin >> size;
            cout << "Enter profit matrix" << endl;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    cin >> assigning[i][j];
                }
            }
            start = clock();
            bestTasks = findTasks(assigning);
            end = clock();
            cout << "\n" << "Elapsed time" << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
            for (auto &jobs: assigning) {
                for (auto &job: jobs) {
                    cout << " " << job << " ";
                }
                cout << endl;
            }
            cout << endl;
            for (int i = 0; i < bestTasks.size(); i++) {
                for (int j = 0; j < bestTasks.size(); j++) {
                    if (j != bestTasks[i]) {
                        cout << " . ";
                    } else {
                        totalCost += assigning[i][j];
                        cout << " x ";
                    }
                }
                cout << endl;
            }
            cout << "Total profit is: " << totalCost << endl;
            cout << endl;
            return;
        }
    }
}

void launch_hungarian(){
    cout << "1. Example" << endl;
    cout << "2. Manual input" << endl;
    vector<vector<int>> assigning;
    vector<int> bestTasks;
    int totalCost = 0;
    int choice;
    cin >> choice;
    clock_t start;
    clock_t end;
    switch(choice){
        case 1: {
            assigning = {
                    {10, 5, 5},
                    {2,  4, 10},
                    {5,  1, 7}
            };
            start = clock();
            bestTasks = hungarianAlgorithm(assigning);
            end = clock();
            cout << "\n" << "Elapsed time" << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
            for (auto &jobs: assigning) {
                for (auto &job: jobs) {
                    cout << " " << job << " ";
                }
                cout << endl;
            }
            cout << endl;
            for (int i = 0; i < bestTasks.size(); i++) {
                for (int j = 0; j < bestTasks.size(); j++) {
                    if (j != bestTasks[i]) {
                        cout << " . ";
                    } else {
                        totalCost += assigning[i][j];
                        cout << " x ";
                    }
                }
                cout << endl;
            }
            cout << "Total profit is: " << totalCost << endl;
            cout << endl;
            return;
        }
        case 2: {
            cout << "Enter the size of the matrix: " << endl;
            int size;
            cin >> size;
            cout << "Enter profit matrix" << endl;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    cin >> assigning[i][j];
                }
            }
            start = clock();
            bestTasks = hungarianAlgorithm(assigning);
            end = clock();
            cout << "\n" << "Elapsed time" << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
            for (auto &jobs: assigning) {
                for (auto &job: jobs) {
                    cout << " " << job << " ";
                }
                cout << endl;
            }
            cout << endl;
            for (int i = 0; i < bestTasks.size(); i++) {
                for (int j = 0; j < bestTasks.size(); j++) {
                    if (j != bestTasks[i]) {
                        cout << " . ";
                    } else {
                        totalCost += assigning[i][j];
                        cout << " x ";
                    }
                }
                cout << endl;
            }
            cout << "Total profit is: " << totalCost << endl;
            cout << endl;
            return;
        }
    }
}

int main() {
    while(true){
        cout << "1. Basic scheduling with deadlines algorithm" << endl;
        cout << "2. Modified scheduling with deadlines algorithm" << endl;
        cout << "3. Assigning problem greedy approach" << endl;
        cout << "4. Assigning problem Hungarian algorithm" << endl;
        cout << "5. Close the program" << endl;
        int choice;
        cin >> choice;
        switch (choice){
            case 1:
                launch_basic_schedule();
                break;
            case 2:
                launch_modified_schedule();
                break;
            case 3:
                launch_greedy_assigning();
                break;
            case 4:
                launch_hungarian();
                break;
            case 5:
                return 0;
            default:
                continue;
        }
    }
}