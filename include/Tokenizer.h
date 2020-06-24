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
    typedef struct {

    } Token_t;

    const unsigned int bufSize = 5;

    class Tokenizer {
    public:
        Tokenizer();
        ~Tokenizer();
        std::string consume();
        std::string peek(int n = 1);
        void loadFile(std::string file);

    protected:
        std::string fileName;
        std::fstream fileStream;
        char lastTok;
        char buf[bufSize] = {'\0', '\0', '\0', '\0', '\0'};
    };
}

#endif //XMLBUILDER_TOKENIZER_H
/**************************************************************************************************
*       END OF FILE
**************************************************************************************************/