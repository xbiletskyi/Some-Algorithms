#include "Hungarian.h"


class HungarianMatrix{
public:
    vector<vector<int>> matrix;
    int size;
    vector<int> minRows;
    vector<int> minCols;
    vector<bool> coveredRows;
    vector<bool> coveredCols;
    vector<int> zerosQuantityRows;
    vector<int> zerosQuantityCols;

    HungarianMatrix firstStep(const vector<vector<int>> &costsMatrix) {
        size = costsMatrix.size();
        matrix.resize(size, std::vector<int>(size, 0));
        minRows.resize(size, INT_MAX);
        minCols.resize(size, INT_MAX);
        coveredCols.resize(size, false);
        coveredRows.resize(size, false);
        zerosQuantityRows.resize(size, 0);
        zerosQuantityCols.resize(size, 0);

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
                if (matrix[i][j] == 0){
                    zerosQuantityCols[j]++;
                    zerosQuantityRows[i]++;
                }
            }
        }
        return *this;
    }

    int coverZeros(){
        int numLines = 0;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (matrix[i][j] == 0 && !coveredRows[i] && !coveredCols[j]) {
                    if (zerosQuantityCols[j] > zerosQuantityRows[i]){
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
};
vector<int> hungarianAlgorithm(vector<vector<int>> &costsMatrix){
    vector<int> optimalJobs;
    HungarianMatrix hungarianMat;
    hungarianMat.firstStep(costsMatrix);
    int coveredLines = hungarianMat.coverZeros();
    cout << coveredLines << endl;
    for (int i = 0; i < hungarianMat.size; i++){
        if (hungarianMat.coveredCols[i]){
            cout << "Col " << i << " is covered" << "\n";
        }
        if (hungarianMat.coveredRows[i]){
            cout << "Row " << i << " is covered" << "\n";
        }
    }
    for (auto & rows : hungarianMat.matrix){
        for (auto & element : rows){
            cout << " " << element << " ";
        }
        cout << "\n";
    }
    return optimalJobs;
}