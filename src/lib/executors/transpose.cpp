#include "global.h"
/**
 * @brief 
 * SYNTAX: PRINT relation_name
 */
bool syntacticParseTRANSPOSE()
{
    logger.log("syntacticParseTRANSPOSE");

    if(tokenizedQuery.size() == 2) {
        parsedQuery.queryType = TRANSPOSE;
        parsedQuery.printRelationName = tokenizedQuery[1];

    } else {
        cout << "SYNTAX ERROR" << endl;
        return false;
    }

    return true;
}

bool semanticParseTRANSPOSE() {
    logger.log("semanticParseTRANSPOSE");
    bool exists = false; // need to make matrixCatalogue
    if (!exists) {
        cout << "SEMANTIC ERROR: Matrix doesn't exist" << endl;
        return false;
    }
    return true;
}

void executeTRANSPOSE()
{
    logger.log("executeTRANSPOSE");
    // to add matrix catalogue
    return;
}
