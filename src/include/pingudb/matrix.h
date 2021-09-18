#ifndef matrix_H
#define matrix_H

#include "cursor.h"

/**
 * @brief The Matrix class holds all information related to a loaded matrix. It
 * also implements methods that interact with the parsers, executors, cursors
 * and the buffer manager. There are typically 2 ways a table object gets
 * created through the course of the workflow - the first is by using the LOAD
 * command and is using the TRANSPOSE operation.
 *
 */
class Matrix {

public:
  string sourceFileName = "";
  string matrixName = "";
  long long int columnCount = 0;
  long long int rowCount = 0;
  long long int blockCount = 0;
  long long int maxRowsPerBlock = 0;
  long long int nonZeroElements = 0;
  vector<long long int> rowsPerBlockCount;
  bool sparse = false;

  bool blockify();
  Matrix();
  Matrix(string tableName);
  bool sizeSetup();
  void updateStatistics(vector<int> row);
  bool isSparse();
  bool load();
  void print();
  void makePermanent();
  bool isPermanent();
  void getNextPage(Cursor *cursor);
  Cursor getCursor();
  void unload();

  template <typename T>
  void writeRow(vector<T> row, ostream &fout) {
    for (int columnCounter = 0; columnCounter < row.size(); columnCounter++) {
      if (columnCounter != 0)
        fout << ", ";
      fout << row[columnCounter];
    }
    fout << endl;
  }

  /**
   * @brief Static function that takes a vector of valued and prints them out in
   * a comma seperated format.
   *
   * @tparam T current usaages include int and string
   * @param row
   */
  template <typename T>
  void writeRow(vector<T> row) {
    ofstream fout(this->sourceFileName, ios::app);
    this->writeRow(row, fout);
    fout.close();
  }
};
#endif
