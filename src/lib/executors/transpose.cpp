#include "pingudb/global.h"
/**
 * @brief
 * SYNTAX: PRINT relation_name
 */
bool syntacticParseTRANSPOSE() {
  if (tokenizedQuery.size() == 2) {
    parsedQuery.queryType = TRANSPOSE;
    parsedQuery.printRelationName = tokenizedQuery[1];

  } else {
    cout << "SYNTAX ERROR" << endl;
    return false;
  }

  return true;
}

bool semanticParseTRANSPOSE() {
  bool exists = matrixCatalogue.isMatrix(parsedQuery.printRelationName);
  if (!exists) {
    cout << "SEMANTIC ERROR: Matrix doesn't exist" << endl;
    return false;
  }
  return true;
}

void executeTRANSPOSE() { return; }
