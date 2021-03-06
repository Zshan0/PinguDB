#include "pingudb/global.h"
/**
 * @brief Construct a new Page object. Never used as part of the code
 *
 */
Page::Page() {
  pageName = "";
  constructName = "";
  this->pageIndex = -1;
  this->rowCount = 0;
  this->columnCount = 0;
  this->rows.clear();
}

/**
 * @brief Construct a new Page:: Page object given the table name and page
 * index. When tables are loaded they are broken up into blocks of BLOCK_SIZE
 * and each block is stored in a different file named
 * "<constructName>_Page<pageindex>". For example, If the Page being loaded is
 * of table "R" and the pageIndex is 2 then the file name is "R_Page2". The page
 * loads the rows (or tuples) into a vector of rows (where each row is a vector
 * of integers).
 *
 * @param constructName
 * @param pageIndex
 */
Page::Page(string constructName, int pageIndex, bool isTable) {
  if (isTable) {
    this->constructName = constructName;
    this->pageIndex = pageIndex;
    this->pageName =
        "../data/temp/" + this->constructName + "_Page" + to_string(pageIndex);
    Table table = *tableCatalogue.getTable(constructName);
    this->columnCount = table.columnCount;
    uint maxRowCount = table.maxRowsPerBlock;
    vector<int> row(this->columnCount, 0);
    this->rows.assign(maxRowCount, row);

    ifstream fin(pageName, ios::in);
    this->rowCount = table.rowsPerBlockCount[pageIndex];
    int number;
    for (uint rowCounter = 0; rowCounter < this->rowCount; rowCounter++) {
      for (int columnCounter = 0; columnCounter < this->columnCount;
           columnCounter++) {
        fin >> number;
        this->rows[rowCounter][columnCounter] = number;
      }
    }
    fin.close();
  } else {
    /* matrix section */
    this->constructName = constructName;
    this->pageIndex = pageIndex;
    this->pageName =
        "../data/temp/" + this->constructName + "_Page" + to_string(pageIndex);
    Matrix matrix = *matrixCatalogue.getMatrix(constructName);

    if(matrix.sparse) {
      this->columnCount = 3;
    } else {
      this->columnCount = matrix.columnCount;
    }
    uint maxRowCount = matrix.maxRowsPerBlock;
    vector<int> row(this->columnCount, 0);
    this->rows.assign(maxRowCount, row);

    ifstream fin(pageName, ios::in);
    this->rowCount = matrix.rowsPerBlockCount[pageIndex];
    int number;
    for (uint rowCounter = 0; rowCounter < this->rowCount; rowCounter++) {
      for (int columnCounter = 0; columnCounter < this->columnCount;
           columnCounter++) {
        fin >> number;
        this->rows[rowCounter][columnCounter] = number;
      }
    }
    fin.close();
  }
}

/**
 * @brief Get row from page indexed by rowIndex
 *
 * @param rowIndex
 * @return vector<int>
 */
vector<int> Page::getRow(int rowIndex) {
  vector<int> result;
  result.clear();
  if (rowIndex >= this->rowCount)
    return result;
  return this->rows[rowIndex];
}

Page::Page(string constructName, int pageIndex, vector<vector<int>> rows,
           int rowCount) {
  this->constructName = constructName;
  this->pageIndex = pageIndex;
  this->rows = rows;
  this->rowCount = rowCount;
  this->columnCount = rows[0].size();
  this->pageName =
      "../data/temp/" + this->constructName + "_Page" + to_string(pageIndex);
}

/**
 * @brief writes current page contents to file.
 *
 */
void Page::writePage() {
  ofstream fout(this->pageName, ios::trunc);
  for (int rowCounter = 0; rowCounter < this->rowCount; rowCounter++) {
    for (int columnCounter = 0; columnCounter < this->columnCount;
         columnCounter++) {
      if (columnCounter != 0)
        fout << " ";
      fout << this->rows[rowCounter][columnCounter];
    }
    fout << endl;
  }
  fout.close();
}
