#include "Hungarian.h"


class HungarianMatrix{
public:
    vector<vector<int>> matrix;
    int size;
    vector<int> minRows;
    vector<int> minCols;
    vector<bool> coveredRows;
    vector<bool> coveredCols;
    vector<vector<int>> zerosArr;

    explicit HungarianMatrix(const vector<vector<int>> &costsMatrix) {
        size = costsMatrix.size();
        matrix.resize(size, vector<int>(size, 0));
        minRows.resize(size, INT_MAX);
        minCols.resize(size, INT_MAX);
        coveredCols.resize(size, false);
        coveredRows.resize(size, false);
        zerosArr.resize(size, vector<int>(size, 0));

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrix[i][j] = costsMatrix[i][j];
                minRows[i] = std::min(minRows[i], matrix[i][j]);
            }
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrix[i][j] -= minRows[i];
                minCols[j] = std::min(minCols[j], matrix[i][j]);
            }
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrix[i][j] -= minCols[j];
            }
        }
    }
    int maxZeros(int row, int col){
        int vertical = 0;
        int horizontal = 0;
        for (int i = 0; i < size; i ++){
            if (matrix[row][i] == 0){
                horizontal++;
            }
        }
        for (int i = 0; i < size; i++){
            if (matrix[i][col] == 0){
                vertical++;
            }
        }
        return vertical > horizontal ? vertical : -horizontal;
    }
    int coverZeros(){
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                if (matrix[i][j] == 0){
                    zerosArr[i][j] = maxZeros(i, j);
                }
            }
        }
        int numLines = 0;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (matrix[i][j] == 0 && !coveredRows[i] && !coveredCols[j]) {
                    if (zerosArr[i][j] > 0){
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

    void additionalZeros(){
        int minima = INT_MAX;
        for (int i = 0; i < size; i++){
            if (!coveredRows[i]){
                for (int j = 0; j < size; j++){
                    if (!coveredCols[j] && matrix[i][j] < minima){
                        minima = matrix[i][j];
                    }
                }
            }
        }
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                if (!coveredRows[i] && !coveredCols[j]){
                    matrix[i][j] -= minima;
                }
                else if (coveredRows[i] && coveredCols[j]){
                    matrix[i][j] += minima;
                }
            }
        }
        coveredRows.assign(size, false);
        coveredCols.assign(size, false);
        zerosArr.assign(size, vector<int>(size, 0));
    }

    void countZeros(vector<int> & zerosRows, vector<int> & zerosCols, int & minRow, int & minCol){
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                if (matrix[i][j] == 0 && !coveredCols[j] && !coveredRows[i]){
                    zerosRows[i]++;
                    zerosCols[j]++;
                }
            }
        }
        int minZeros = INT_MAX;
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                if (matrix[i][j] == 0 && !coveredRows[i] && !coveredCols[j] && (minZeros > zerosRows[i] || minZeros > zerosCols[j])){
                    minZeros = min(zerosRows[i], zerosCols[j]);
                    minCol = j;
                    minRow = i;
                }
            }
        }

    }
};
vector<int> hungarianAlgorithm(const vector<vector<int>> &costsMatrix){
    int size = costsMatrix.size();
    vector<int> optimalJobs;
    optimalJobs.resize(size, -1);
    HungarianMatrix hungarianMat = HungarianMatrix(costsMatrix);
    while (true) {
        int numLines = hungarianMat.coverZeros();
        if (numLines == size){
            for (auto & row : hungarianMat.matrix){
                for (auto & item : row){
                    cout << item << " ";
                }
                cout << endl;
            }

            vector<int> zerosRows;
            vector<int> zerosCols;
            zerosRows.resize(size, 0);
            zerosCols.resize(size, 0);
            int minCol = 0, minRow = 0;
            hungarianMat.coveredCols.assign(size, false);
            hungarianMat.coveredRows.assign(size, false);
            for (int i = 0; i < size; i++){
                hungarianMat.countZeros(zerosRows, zerosCols, minRow, minCol);
                optimalJobs[minRow] = minCol;
                hungarianMat.coveredRows[minRow] = true;
                hungarianMat.coveredCols[minCol] = true;
                zerosRows.assign(size, 0);
                zerosCols.assign(size, 0);
            }
            break;
        }
        hungarianMat.additionalZeros();
    }
    return optimalJobs;
}