#include "pingudb/global.h"
/**
 * @brief
 * SYNTAX: RENAME column_name TO column_name FROM relation_name
 */
bool syntacticParseRENAME() {
  if (tokenizedQuery.size() != 6 || tokenizedQuery[2] != "TO" ||
      tokenizedQuery[4] != "FROM") {
    cout << "SYNTAX ERROR" << endl;
    return false;
  }
  parsedQuery.queryType = RENAME;
  parsedQuery.renameFromColumnName = tokenizedQuery[1];
  parsedQuery.renameToColumnName = tokenizedQuery[3];
  parsedQuery.renameRelationName = tokenizedQuery[5];
  return true;
}

bool semanticParseRENAME() {
  if (!tableCatalogue.isTable(parsedQuery.renameRelationName)) {
    cout << "SEMANTIC ERROR: Relation doesn't exist" << endl;
    return false;
  }

  if (!tableCatalogue.isColumnFromTable(parsedQuery.renameFromColumnName,
                                        parsedQuery.renameRelationName)) {
    cout << "SEMANTIC ERROR: Column doesn't exist in relation" << endl;
    return false;
  }

  if (tableCatalogue.isColumnFromTable(parsedQuery.renameToColumnName,
                                       parsedQuery.renameRelationName)) {
    cout << "SEMANTIC ERROR: Column with name already exists" << endl;
    return false;
  }
  return true;
}

void executeRENAME() {
  Table *table = tableCatalogue.getTable(parsedQuery.renameRelationName);
  table->renameColumn(parsedQuery.renameFromColumnName,
                      parsedQuery.renameToColumnName);
  return;
}
