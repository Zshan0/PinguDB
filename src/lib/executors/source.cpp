#include "pingudb/global.h"
/**
 * @brief
 * SYNTAX: SOURCE filename
 */
bool syntacticParseSOURCE() {
  if (tokenizedQuery.size() != 2) {
    cout << "SYNTAX ERROR" << endl;
    return false;
  }
  parsedQuery.queryType = SOURCE;
  parsedQuery.sourceFileName = tokenizedQuery[1];
  return true;
}

bool semanticParseSOURCE() {
  if (!isQueryFile(parsedQuery.sourceFileName)) {
    cout << "SEMANTIC ERROR: File doesn't exist" << endl;
    return false;
  }
  return true;
}

void executeSOURCE() { return; }
