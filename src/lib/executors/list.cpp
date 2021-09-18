#include "pingudb/global.h"
/**
 * @brief
 * SYNTAX: LIST TABLES
 */
bool syntacticParseLIST() {
  if (tokenizedQuery.size() != 2 || tokenizedQuery[1] != "TABLES") {
    cout << "SYNTAX ERROR" << endl;
    return false;
  }
  parsedQuery.queryType = LIST;
  return true;
}

bool semanticParseLIST() { return true; }

void executeLIST() {
  tableCatalogue.print();
  matrixCatalogue.print();
}
