// Server Code
#include "pingudb/global.h"
#include "pingudb/bufferManager.h"

using namespace std;

float BLOCK_SIZE = 1;
uint BLOCK_COUNT = 2;
uint PRINT_COUNT = 20;
vector<string> tokenizedQuery;
ParsedQuery parsedQuery;
TableCatalogue tableCatalogue;
MatrixCatalogue matrixCatalogue;
BufferManager bufferManager;

void doCommand() {
  if (syntacticParse() && semanticParse())
    executeCommand();
}

int main(void) {
  regex delim("[^\\s,]+");
  string command;
  system("rm -rf ../data/temp");
  system("mkdir ../data/temp");

  while (!cin.eof()) {
    cout << "\n> ";
    tokenizedQuery.clear();
    parsedQuery.clear();
    getline(cin, command);

    auto words_begin =
        std::sregex_iterator(command.begin(), command.end(), delim);
    auto words_end = std::sregex_iterator();
    for (std::sregex_iterator i = words_begin; i != words_end; ++i)
      tokenizedQuery.emplace_back((*i).str());

    if (tokenizedQuery.size() == 1 && tokenizedQuery.front() == "QUIT") {
      break;
    }

    if (tokenizedQuery.empty()) {
      continue;
    }

    if (tokenizedQuery.size() == 1) {
      cout << "SYNTAX ERROR" << endl;
      continue;
    }

    doCommand();
  }
}
