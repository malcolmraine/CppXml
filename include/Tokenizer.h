/**************************************************************************************************
* File: Tokenizer.h
* Description:
* Author: Malcolm Hall
* Date: 6/10/20
* Version: 1
*
**************************************************************************************************/
#ifndef XMLBUILDER_TOKENIZER_H
#define XMLBUILDER_TOKENIZER_H

/**************************************************************************************************
*       INCLUDES AND DECLARATIONS
**************************************************************************************************/
#include <string>
#include <fstream>

namespace CppXml {
    class Tokenizer {
    public:
        Tokenizer();
        ~Tokenizer();
        char consume();
        void loadFile(std::string file);

    protected:
        std::string fileName;
        std::fstream fileStream;
        char lastTok;
    };
}

#endif //XMLBUILDER_TOKENIZER_H
/**************************************************************************************************
*       END OF FILE
**************************************************************************************************/