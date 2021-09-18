#include "pingudb/global.h"
/**
 * @brief
 * SYNTAX: LOAD relation_name
 */
bool syntacticParseLOAD() {
  if (tokenizedQuery.size() == 3) {
    if (tokenizedQuery[1] != "MATRIX") {
      cout << "SYNTAX ERROR" << endl;
      return false;
    }
    parsedQuery.queryType = LOAD_MAT;
    parsedQuery.loadRelationName = tokenizedQuery[2];
  } else if (tokenizedQuery.size() == 2) {
    parsedQuery.queryType = LOAD;
    parsedQuery.loadRelationName = tokenizedQuery[1];
  } else {
    cout << "SYNTAX ERROR" << endl;
    return false;
  }
  return true;
}

bool semanticParseLOAD() {
  if (tableCatalogue.isTable(parsedQuery.loadRelationName)) {
    cout << "SEMANTIC ERROR: Relation already exists" << endl;
    return false;
  }

  if (!isFileExists(parsedQuery.loadRelationName)) {
    cout << "SEMANTIC ERROR: Data file doesn't exist" << endl;
    return false;
  }
  return true;
}

bool semanticParseLOAD_MAT() {
  bool matrixExists = matrixCatalogue.isMatrix(parsedQuery.loadRelationName);

  if (matrixExists) {
    cout << "SEMANTIC ERROR: Matrix already exists" << endl;
    return false;
  }

  bool dataExists = isFileExists(parsedQuery.loadRelationName);
  if (!dataExists) {
    cout << "SEMANTIC ERROR: Data file doesn't exist" << endl;
    return false;
  }
  return true;
}

void executeLOAD() {
  Table *table = new Table(parsedQuery.loadRelationName);
  if (table->load()) {
    tableCatalogue.insertTable(table);
    cout << "Loaded Table. Column Count: " << table->columnCount
         << " Row Count: " << table->rowCount << endl;
  }
  return;
}

void executeLOAD_MAT() {
  Matrix *matrix = new Matrix(parsedQuery.loadRelationName);
  if (matrix->load()) {
    matrixCatalogue.insertMatrix(matrix);
    cout << "Loaded Matrix. Column Count: " << matrix->columnCount
         << " Row Count: " << matrix->rowCount << endl;
  }
  return;
}
