#include "pingudb/global.h"

/**
 * @brief
 * SYNTAX: EXPORT <relation_name>
 */

bool syntacticParseEXPORT() {
  if (tokenizedQuery.size() == 3) {
    if (tokenizedQuery[1] != "MATRIX") {
      cout << "SYNTAX ERROR" << endl;
      return false;
    }

    parsedQuery.queryType = EXPORT_MAT;
    parsedQuery.exportRelationName = tokenizedQuery[2];
  } else if (tokenizedQuery.size() == 2) {
    parsedQuery.queryType = EXPORT;
    parsedQuery.exportRelationName = tokenizedQuery[1];
  } else {
    cout << "SYNTAX ERROR" << endl;
    return false;
  }
  return true;
}

bool semanticParseEXPORT() {
  // Table should exist
  if (tableCatalogue.isTable(parsedQuery.exportRelationName))
    return true;
  cout << "SEMANTIC ERROR: No such relation exists" << endl;
  return false;
}

bool semanticParseEXPORT_MAT() {
  // Matrix should exist
  bool exists = matrixCatalogue.isMatrix(parsedQuery.exportRelationName);
  if (exists)
    return true;
  cout << "SEMANTIC ERROR: No such relation exists" << endl;
  return false;
}

void executeEXPORT() {
  Table *table = tableCatalogue.getTable(parsedQuery.exportRelationName);
  table->makePermanent();
  return;
}

void executeEXPORT_MAT() {
  Matrix *matrix = matrixCatalogue.getMatrix(parsedQuery.exportRelationName);
  matrix->makePermanent();
  return;
}
