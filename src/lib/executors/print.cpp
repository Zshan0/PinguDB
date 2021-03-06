#include "pingudb/global.h"
/**
 * @brief
 * SYNTAX: PRINT relation_name
 */
bool syntacticParsePRINT() {
  if (tokenizedQuery.size() == 3) {
    if (tokenizedQuery[1] != "MATRIX") {
      cout << "SYNTAX ERROR" << endl;
      return false;
    }
    parsedQuery.queryType = PRINT_MAT;
    parsedQuery.printRelationName = tokenizedQuery[2];

  } else if (tokenizedQuery.size() == 2) {
    parsedQuery.queryType = PRINT;
    parsedQuery.printRelationName = tokenizedQuery[1];
  } else {
    cout << "SYNTAX ERROR" << endl;
    return false;
  }

  return true;
}

bool semanticParsePRINT_MAT() {
  // need to make matrixCatalogue
  bool exists = matrixCatalogue.isMatrix(parsedQuery.printRelationName);
  if (!exists) {
    cout << "SEMANTIC ERROR: Matrix doesn't exist" << endl;
    return false;
  }
  return true;
}

bool semanticParsePRINT() {
  if (!tableCatalogue.isTable(parsedQuery.printRelationName)) {
    cout << "SEMANTIC ERROR: Relation doesn't exist" << endl;
    return false;
  }
  return true;
}

void executePRINT() {
  Table *table = tableCatalogue.getTable(parsedQuery.printRelationName);
  table->print();
  return;
}

void executePRINT_MAT() {
  Matrix *matrix = matrixCatalogue.getMatrix(parsedQuery.printRelationName);
  matrix->print();
  return;
}
