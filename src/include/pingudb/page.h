#ifndef page_H
#define page_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <sys/stat.h>
#include <sstream>
#include <regex>

using namespace std;

/**
 * @brief The Page object is the main memory representation of a physical page
 * (equivalent to a block). The page class and the page.h header file are at the
 * bottom of the dependency tree when compiling files.
 *<p>
 * Do NOT modify the Page class. If you find that modifications
 * are necessary, you may do so by posting the change you want to make on Moodle
 * or Teams with justification and gaining approval from the TAs.
 *</p>
 */
class Page {
  string constructName;
  string pageIndex;
  int columnCount;
  int rowCount;
  vector<vector<int>> rows;

public:
  string pageName = "";
  Page();
  Page(string tableName, int pageIndex, bool isTable = true);
  Page(string tableName, int pageIndex, vector<vector<int>> rows, int rowCount);
  vector<int> getRow(int rowIndex);
  void writePage();
};
#endif
