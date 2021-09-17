#include "pingudb/global.h"

void executeCommand() {

  switch (parsedQuery.queryType) {
  case CLEAR:
    executeCLEAR();
    break;
  case CROSS:
    executeCROSS();
    break;
  case DISTINCT:
    executeDISTINCT();
    break;
  case EXPORT:
    executeEXPORT();
    break;
  case INDEX:
    executeINDEX();
    break;
  case JOIN:
    executeJOIN();
    break;
  case LIST:
    executeLIST();
    break;
  case LOAD:
    executeLOAD();
    break;
  case PRINT:
    executePRINT();
    break;
  case PROJECTION:
    executePROJECTION();
    break;
  case RENAME:
    executeRENAME();
    break;
  case SELECTION:
    executeSELECTION();
    break;
  case SORT:
    executeSORT();
    break;
  case SOURCE:
    executeSOURCE();
    break;
  // new functions
  case PRINT_MAT:
    executePRINT_MAT();
    break;
  case TRANSPOSE:
    executeTRANSPOSE();
    break;
  case LOAD_MAT:
    executeLOAD_MAT();
    break;
  case EXPORT_MAT:
    executeEXPORT_MAT();
    break;
  default:
    cout << "PARSING ERROR" << endl;
  }

  return;
}

void printRowCount(int rowCount) {
  cout << "\n\nRow Count: " << rowCount << endl;
  return;
}
