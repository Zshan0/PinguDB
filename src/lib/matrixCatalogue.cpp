#include "global.h"

void MatrixCatalogue::insertMatrix(Matrix *matrix) {
  logger.log("MatrixCatalogue::~insertMatrix");
  this->matrices[matrix->matrixName] = matrix;
}

void MatrixCatalogue::deleteMatrix(string matrixName) {
  logger.log("MatrixCatalogue::deleteMatrix");
  this->matrices[matrixName]->unload();
  delete this->matrices[matrixName];
  this->matrices.erase(matrixName);
}

Matrix *MatrixCatalogue::getMatrix(string matrixName) {
  logger.log("MatrixCatalogue::getMatrix");
  Matrix *matrix = this->matrices[matrixName];
  return matrix;
}

bool MatrixCatalogue::isMatrix(string matrixName) {
  logger.log("MatrixCatalogue::isMatrix");
  return (bool)this->matrices.count(matrixName);
}

void MatrixCatalogue::print() {
  logger.log("MatrixCatalogue::print");
  cout << "\nMATRICES" << endl;

  int rowCount = 0;
  for (auto m: this->matrices) {
    cout << m.second->matrixName << endl;
    rowCount++;
  }
  printRowCount(rowCount);
}
