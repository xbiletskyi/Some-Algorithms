#include "Hungarian.h"

class HungarianMatrix{
public:
    vector<vector<int>> matrix;
    int size;
    vector<int> minRows;
    vector<int> minCols;
    vector<bool> coveredRows;
    vector<bool> coveredCols;

    explicit HungarianMatrix(const vector<vector<int>> &costsMatrix) {  // O(n^2) complexity
        size = costsMatrix.size();
        matrix.resize(size, vector<int>(size, 0));  // O(n) initialization
        minRows.resize(size, INT_MAX);                       // O(n) initialization
        minCols.resize(size, INT_MAX);                       // O(n) initialization
        coveredCols.resize(size, false);                     // O(n) initialization
        coveredRows.resize(size, false);                     // O(n) initialization

        for (int i = 0; i < size; i++) {        // O(n^2) complexity due to two nested for() loops
            for (int j = 0; j < size; j++) {
                matrix[i][j] = costsMatrix[i][j];
                minRows[i] = std::min(minRows[i], matrix[i][j]);
            }
        }

        for (int i = 0; i < size; i++) {        // O(n^2) complexity due to two nested for() loops
            for (int j = 0; j < size; j++) {
                matrix[i][j] -= minRows[i];
                minCols[j] = std::min(minCols[j], matrix[i][j]);
            }
        }

        for (int i = 0; i < size; i++) {        // O(n^2) complexity due to two nested for() loops
            for (int j = 0; j < size; j++) {
                matrix[i][j] -= minCols[j];
            }
        }
    }
    int maxZeros(int row, int col){     // O(n) complexity
        int vertical = 0;
        int horizontal = 0;
        for (int i = 0; i < size; i ++){        // O(n) complexity (one for() loop)
            if (matrix[row][i] == 0 && !coveredCols[i]){
                horizontal++;
            }
        }
        for (int i = 0; i < size; i++){         // O(n) complexity (one for() loop)
            if (matrix[i][col] == 0 && !coveredRows[i]){
                vertical++;
            }
        }
        return vertical > horizontal ? vertical : -horizontal;
    }
    int coverZeros(){   // O(n^2) complexity on average
        int numLines = 0;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (matrix[i][j] == 0 && !coveredRows[i] && !coveredCols[j]) {

                    int zeros = maxZeros(i, j);     // O(n) function; executed n^2 times on worst case; n times on average
                    if (zeros > 0){
                        coveredCols[j] = true;
                    }
                    else{
                        coveredRows[i] = true;
                    }
                    numLines++;
                }
            }
        }
        return numLines;
    }

    void additionalZeros(){     // O(n^2) complexity
        int minima = INT_MAX;
        for (int i = 0; i < size; i++){     // O(n^2) complexity
            if (!coveredRows[i]){
                for (int j = 0; j < size; j++){
                    if (!coveredCols[j] && matrix[i][j] < minima){
                        minima = matrix[i][j];
                    }
                }
            }
        }
        for (int i = 0; i < size; i++){     // O(n^2) complexity
            for (int j = 0; j < size; j++){
                if (!coveredRows[i] && !coveredCols[j]){
                    matrix[i][j] -= minima;
                }
                else if (coveredRows[i] && coveredCols[j]){
                    matrix[i][j] += minima;
                }
            }
        }
        coveredRows.assign(size, false);    // O(n) complexity
        coveredCols.assign(size, false);    // O(n) complexity
    }

    void countZeros(vector<int> & zerosRows, vector<int> & zerosCols, int & minRow, int & minCol){  // O(n^2) complexity
        for (int i = 0; i < size; i++){     // O(n^2) complexity (nested loop)
            for (int j = 0; j < size; j++){
                if (matrix[i][j] == 0 && !coveredCols[j] && !coveredRows[i]){
                    zerosRows[i]++;
                    zerosCols[j]++;
                }
            }
        }
        int minZeros = INT_MAX;
        for (int i = 0; i < size; i++){     // O(n^2) complexity (nested loop)
            for (int j = 0; j < size; j++){
                if (matrix[i][j] == 0 && !coveredRows[i] && !coveredCols[j] && (minZeros > zerosRows[i] || minZeros > zerosCols[j])){
                    // condition to find the element in row or column with the least possibilities to assign a worker/job
                    minZeros = min(zerosRows[i], zerosCols[j]);
                    minCol = j;
                    minRow = i;
                }
            }
        }

    }
};

vector<int> hungarianAlgorithm(const vector<vector<int>> &costsMatrix){     // O(n^3) complexity
    int size = costsMatrix.size();
    vector<int> optimalJobs;
    optimalJobs.resize(size, -1);
    HungarianMatrix hungarianMat = HungarianMatrix(costsMatrix);
    while (true) {      // the fact the loop is infinite, however it cannot have more than n iterations due to adding zeros every time
        int numLines = hungarianMat.coverZeros();   // O(n^2) complexity; executed n times
        if (numLines == size){
            vector<int> zerosRows;
            vector<int> zerosCols;
            zerosRows.resize(size, 0);      // O(n) initialization complexity; executed once
            zerosCols.resize(size, 0);      // O(n) initialization complexity; executed once
            int minCol = 0, minRow = 0;
            hungarianMat.coveredCols.assign(size, false);   // O(n) assigning complexity; executed once
            hungarianMat.coveredRows.assign(size, false);   // O(n) assigning complexity; executed once
            for (int i = 0; i < size; i++){
                hungarianMat.countZeros(zerosRows, zerosCols, minRow, minCol);  // O(n^2) complexity; executed n times
                optimalJobs[minRow] = minCol;
                hungarianMat.coveredRows[minRow] = true;
                hungarianMat.coveredCols[minCol] = true;
                zerosRows.assign(size, 0);  // O(n) assigning complexity; executed n times
                zerosCols.assign(size, 0);  // O(n) assigning complexity; executed n times
            }
            break;
        }
        hungarianMat.additionalZeros();     // O(n^2) complexity; executed n times
    }
    return optimalJobs;
}