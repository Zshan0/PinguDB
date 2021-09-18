#include "pingudb/global.h"

void TableCatalogue::insertTable(Table *table) {
  this->tables[table->tableName] = table;
}

void TableCatalogue::deleteTable(string tableName) {
  this->tables[tableName]->unload();
  delete this->tables[tableName];
  this->tables.erase(tableName);
}

Table *TableCatalogue::getTable(string tableName) {
  Table *table = this->tables[tableName];
  return table;
}

bool TableCatalogue::isTable(string tableName) {
  if (this->tables.count(tableName))
    return true;
  return false;
}

bool TableCatalogue::isColumnFromTable(string columnName, string tableName) {
  if (this->isTable(tableName)) {
    Table *table = this->getTable(tableName);
    if (table->isColumn(columnName))
      return true;
  }
  return false;
}

void TableCatalogue::print() {
  cout << "\nRELATIONS" << endl;

  int rowCount = 0;
  for (auto rel : this->tables) {
    cout << rel.first << endl;
    rowCount++;
  }
  printRowCount(rowCount);
}

TableCatalogue::~TableCatalogue() {
  for (auto table : this->tables) {
    table.second->unload();
    delete table.second;
  }
}
