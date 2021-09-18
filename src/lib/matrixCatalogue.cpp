#include "pingudb/global.h"

void MatrixCatalogue::insertMatrix(Matrix *matrix) {
  this->matrices[matrix->matrixName] = matrix;
}

void MatrixCatalogue::deleteMatrix(string matrixName) {
  this->matrices[matrixName]->unload();
  delete this->matrices[matrixName];
  this->matrices.erase(matrixName);
}

Matrix *MatrixCatalogue::getMatrix(string matrixName) {
  Matrix *matrix = this->matrices[matrixName];
  return matrix;
}

bool MatrixCatalogue::isMatrix(string matrixName) {
  return (bool)this->matrices.count(matrixName);
}

void MatrixCatalogue::print() {
  cout << "\nMATRICES" << endl;

  int rowCount = 0;
  for (auto m : this->matrices) {
    cout << m.second->matrixName << endl;
    rowCount++;
  }
  printRowCount(rowCount);
}
