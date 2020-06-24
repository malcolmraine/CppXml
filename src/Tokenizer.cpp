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


/******************************************************************************
 * @brief
 */
CppXml::Tokenizer::Tokenizer() {

}


/******************************************************************************
 * @brief
 */
CppXml::Tokenizer::~Tokenizer() {

}


/******************************************************************************
 * @brief
 * @return
 */
std::string CppXml::Tokenizer::consume() {
    char ch = buf[bufSize - 3];

    /* Advance the buffer   */
    for (int i = 1 ; i < bufSize; i++)
    {
        buf[i] = buf[i -1];
    }

    fileStream.get(ch);

//    if (ch == '<' && peek() == '/')
//    {
//
//    }



    fileStream.get(buf[0]);


}


/******************************************************************************
 * @brief
 * @return
 */
char CppXml::Tokenizer::peek(int n) {
    /*
     * If n == 1 then we return the next character in the buffer.
     * Otherwise, we return the 2nd to next character in the buffer.
     */
    if (n == 1)
    {
        return buf[1];
    }
    else
    {
        return buf[0];
    }
}


/******************************************************************************
 * @brief
 * @param file
 */
void CppXml::Tokenizer::loadFile(std::string file) {
    fileName = std::move(file);
    fileStream = std::fstream(fileName, std::fstream::in);

    /* Initialize the buffer with the first 3 characters. We don't want to
     * move any characters into the last buffer index because we need that
     * character still. */
    for (int i = 0; i < bufSize - 2; ++i)
    {
        buf[i] = consume();
    }
}









/**************************************************************************************************
*       END OF FILE
**************************************************************************************************/

