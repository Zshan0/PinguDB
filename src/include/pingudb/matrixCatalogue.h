#ifndef matrixCatalogue_H
#define matrixCatalogue_H
#include "matrix.h"

/**
 * @brief The TableCatalogue acts like an index of tables existing in the
 * system. Everytime a table is added(removed) to(from) the system, it needs to
 * be added(removed) to(from) the tableCatalogue.
 *
 */
class MatrixCatalogue {

  unordered_map<string, Matrix *> matrices;

public:
  MatrixCatalogue() { cout << "Matrix catalogue has been created" << endl; }
  void insertMatrix(Matrix *table);
  void deleteMatrix(string matrixName);
  Matrix *getMatrix(string matrixName);
  bool isMatrix(string matrixName);
  void print();
  // ~MatrixCatalogue();
};
#endif
