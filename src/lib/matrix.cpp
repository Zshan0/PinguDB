#include "pingudb/global.h"

/**
 * @brief Construct a new Matrix :: Matrix object used in the case where the
 * data file is available and LOAD command has been called. This command should
 * be followed by calling the load function;
 *
 * @param matrixName
 */
Matrix::Matrix(string matrixName) {
  this->sourceFileName = "../data/" + matrixName + ".csv";
  this->matrixName = matrixName;
}

/**
 * @brief The load function is used when the LOAD command is encountered. It
 * reads data from the source file, splits it into blocks and updates matrix
 * statistics.
 *
 * @return true if the matrix has been successfully loaded
 * @return false if an error occurred
 */
bool Matrix::load() {
  return (this->sizeSetup() and this->isSparse() and this->blockify());
}
/**
 * @brief Reads the whole file and checks if the matrix is
 *        sparse.
 *
 *
 * @return true if more than 60% of the matrix is zeros
 * @return false otherwise
 */
bool Matrix::isSparse() {

  ifstream fin(this->sourceFileName, ios::in);
  string line, word;

  long long int num;
  long long int nonZeros = 0;
  long long total = 0;

  while (getline(fin, line)) {
    stringstream s(line);
    for (int columnCounter = 0; columnCounter < this->columnCount;
         columnCounter++) {
      if (!getline(s, word, ','))
        return false;
      num = stoi(word);
      nonZeros += (int)(num != 0);
      total += 1;
    }
  }

  this->sparse = nonZeros <= 0.4 * total;
  this->nonZeroElements = nonZeros;

  if (this->sparse) {
    this->maxRowsPerBlock =
        (long long int)((BLOCK_SIZE * 1000) / (sizeof(long long int) * 3));
    return true;
  }

  this->maxRowsPerBlock =
      (long long int)((BLOCK_SIZE * 1000) / (sizeof(int) * this->columnCount));

  return true;
}

/**
 * @brief Set the blocksize and the column size
 *
 *
 * @return true if size successfully extracted and not 0
 * @return false otherwise
 */
bool Matrix::sizeSetup() {
  /*
   * checking the size of the first line to get the columnCount
   * CAN BE BETTER
   */

  fstream fin(this->sourceFileName, ios::in);
  string line;
  if (!getline(fin, line)) {
    fin.close();
    return false;
  }
  string word;
  stringstream s(line);
  int colCount = 0;
  while (getline(s, word, ',')) {
    colCount++;
  }

  if (colCount == 0) {
    return false;
  }

  this->columnCount = colCount;

  return true;
}

/**
 * @brief This function splits all the rows and stores them in multiple files of
 * one block size.
 *
 * @return true if successfully blockified
 * @return false otherwise
 */
bool Matrix::blockify() {
  /*
    NEED TO FIX -> ADD SUPPORT FOR COLUMNS > BLOCK SIZE
  */
  if (not this->sparse) {

    ifstream fin(this->sourceFileName, ios::in);
    string line, word;
    vector<int> row(this->columnCount, 0);
    vector<vector<int>> rowsInPage(this->maxRowsPerBlock, row);

    int pageCounter = 0;

    while (getline(fin, line)) {

      stringstream s(line);
      for (int columnCounter = 0; columnCounter < this->columnCount;
           columnCounter++) {
        if (!getline(s, word, ','))
          return false;

        row[columnCounter] = stoi(word);
        rowsInPage[pageCounter][columnCounter] = row[columnCounter];
      }

      pageCounter++;
      this->updateStatistics(row);

      if (pageCounter == this->maxRowsPerBlock) {

        bufferManager.writePage(this->matrixName, this->blockCount, rowsInPage,
                                pageCounter);

        this->blockCount++;
        this->rowsPerBlockCount.emplace_back(pageCounter);
        pageCounter = 0;
      }
    }

    // if anything is remaining
    if (pageCounter) {

      bufferManager.writePage(this->matrixName, this->blockCount, rowsInPage,
                              pageCounter);
      this->blockCount++;
      this->rowsPerBlockCount.emplace_back(pageCounter);
      pageCounter = 0;
    }
    return this->rowCount != 0;
  } else {
    /* Need to store in sparse format */

    ifstream fin(this->sourceFileName, ios::in);
    string line, word;
    vector<int> row(3, 0);
    vector<vector<int>> rowsInPage(this->maxRowsPerBlock, row);

    int i = 0, j = 0;
    int pageCounter = 0;

    while (getline(fin, line)) {
      j = 0;
      stringstream s(line);

      for (int columnCounter = 0; columnCounter < this->columnCount;
           columnCounter++) {
        if (!getline(s, word, ','))
          return false;

        int num = stoi(word);
        if (num != 0) {
          row[0] = i; row[1] = j; row[2] = num;
          rowsInPage[pageCounter][0] = i;
          rowsInPage[pageCounter][1] = j;
          rowsInPage[pageCounter][2] = num;
          pageCounter++;
          this->updateStatistics(row);
        }
        j++;
      }

      if (pageCounter == this->maxRowsPerBlock) {
        bufferManager.writePage(this->matrixName, this->blockCount, rowsInPage,
                                pageCounter);
        this->blockCount++;
        this->rowsPerBlockCount.emplace_back(pageCounter);
        pageCounter = 0;
      }
      i++;
    }

    // if anything is remaining
    if (pageCounter) {
      bufferManager.writePage(this->matrixName, this->blockCount, rowsInPage,
                              pageCounter);
      this->blockCount++;
      this->rowsPerBlockCount.emplace_back(pageCounter);
      pageCounter = 0;
    }
    return this->rowCount != 0;
  }
}

/**
 * @brief Given a row of values, this function will update the statistics it
 * stores
 * @param row
 */
void Matrix::updateStatistics(vector<int> row) {
  this->rowCount++;
}

/**
 * @brief Function prints the first few rows of the matrix. If the matrix
 * contains more rows than PRINT_COUNT, exactly PRINT_COUNT rows are printed,
 * else all the rows are printed.
 *
 */
void Matrix::print() {
  long long int count = min((long long int)PRINT_COUNT, this->rowCount);

  if (not this->sparse) {
    Cursor cursor(this->matrixName, 0, false);
    vector<int> row;
    for (long long int rowCounter = 0; rowCounter < count; rowCounter++) {
      row = cursor.getNext(false);
      this->writeRow(row, cout);
    }
    printRowCount(this->rowCount);
  } else {
    /* sparse matrix */
    Cursor cursor(this->matrixName, 0, false);
    vector<int> row;

    for (long long int rowCounter = 0; rowCounter < count; rowCounter++) {
      row = cursor.getNext(false);
      this->writeRow(row, cout);
    }
    printRowCount(this->rowCount);
  }
}

/**
 * @brief This function returns one row of the matrix using the cursor object.
 * It returns an empty row is all rows have been read.
 *
 * @param cursor
 * @return vector<int>
 */
void Matrix::getNextPage(Cursor *cursor) {
  if (cursor->pageIndex < this->blockCount - 1) {
    cursor->nextPage(cursor->pageIndex + 1, false);
  }
}

/**
 * @brief called when EXPORT command is invoked to move source file to "data"
 * folder.
 *
 */
void Matrix::makePermanent() {

  if (!this->isPermanent())
    bufferManager.deleteFile(this->sourceFileName);

  string newSourceFile = "../data/" + this->matrixName + ".csv";
  ofstream fout(newSourceFile, ios::out);
  Cursor cursor(this->matrixName, 0, false);

  vector<int> row;
  for (long long int rowCounter = 0; rowCounter < this->rowCount;
       rowCounter++) {
    row = cursor.getNext(false);
    this->writeRow(row, fout);
  }

  fout.close();
}

/**
 * @brief Function to check if matrix is already exported
 *
 * @return true if exported
 * @return false otherwise
 */
bool Matrix::isPermanent() {
  return (this->sourceFileName == "../data/" + this->matrixName + ".csv");
}

/**
 * @brief The unload function removes the matrix from the database by deleting
 * all temporary files created as part of this matrix
 *
 */
void Matrix::unload() {
  for (long long int pageCounter = 0; pageCounter < this->blockCount;
       pageCounter++)
    bufferManager.deleteFile(this->matrixName, pageCounter);
  if (!isPermanent())
    bufferManager.deleteFile(this->sourceFileName);
}

/**
 * @brief Function that returns a cursor that reads rows from this matrix
 *
 * @return Cursor
 */
Cursor Matrix::getCursor() {
  Cursor cursor(this->matrixName, 0, false);
  return cursor;
}
