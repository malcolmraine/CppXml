/**************************************************************************************************
* File: Tokenizer.cpp
* Description:
* Author: Malcolm Hall
* Date: 6/10/20
* Version: 1
*
**************************************************************************************************/

/**************************************************************************************************
*       INCLUDES AND DECLARATIONS
**************************************************************************************************/
#include <fstream>
#include <utility>
#include "../include/Tokenizer.h"



CppXml::Tokenizer::Tokenizer() {

}

CppXml::Tokenizer::~Tokenizer() {

}


char CppXml::Tokenizer::consume() {
    char ch;
    long long loopCnt = 0;  // Counter so we can prevent infinite loops

    while (loopCnt < 4294967295)
    {
        fileStream.get(ch);
        if ((ch != '\n') && (ch != '\t') && !(ch == ' ' && lastTok == ' '))
        {
            break;
        }
        loopCnt++;
    }
    if (ch)
    {
        lastTok = ch;
        return ch;
    }
    else
    {
        return '\0';
    }
}


void CppXml::Tokenizer::loadFile(std::string file) {
    fileName = std::move(file);
    fileStream = std::fstream(fileName, std::fstream::in);
}



/**************************************************************************************************
*       END OF FILE
**************************************************************************************************/

