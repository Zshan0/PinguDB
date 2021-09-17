#include "pingudb/global.h"

bool semanticParse() {
  logger.log("semanticParse");
  switch (parsedQuery.queryType) {
  case CLEAR:
    return semanticParseCLEAR();
  case CROSS:
    return semanticParseCROSS();
  case DISTINCT:
    return semanticParseDISTINCT();
  case EXPORT:
    return semanticParseEXPORT();
  case INDEX:
    return semanticParseINDEX();
  case JOIN:
    return semanticParseJOIN();
  case LIST:
    return semanticParseLIST();
  case LOAD:
    return semanticParseLOAD();
  case PRINT:
    return semanticParsePRINT();
  case PROJECTION:
    return semanticParsePROJECTION();
  case RENAME:
    return semanticParseRENAME();
  case SELECTION:
    return semanticParseSELECTION();
  case SORT:
    return semanticParseSORT();
  case SOURCE:
    return semanticParseSOURCE();
  // new functions
  case LOAD_MAT:
    return semanticParseLOAD_MAT();
  case PRINT_MAT:
    return semanticParsePRINT_MAT();
  case TRANSPOSE:
    return semanticParseTRANSPOSE();
  case EXPORT_MAT:
    return semanticParseEXPORT_MAT();
  default:
    cout << "SEMANTIC ERROR" << endl;
  }

  return false;
}
