//
// Created by Malcolm Hall on 6/8/20.
//

#include <iostream>
#include "../include/helper.h"


/******************************************************************************
 * @brief
 * @param c
 * @return
 */
std::string CppXml::escape(char c) {
    switch (c) {
        case '<':
            return XML_ESC_LEFT_CARAT;
        case '>':
            return XML_ESC_RIGHT_CARAT;
        case '&':
            return XML_ESC_AMP;
        case '\'':
            return XML_ESC_SINGLE_QUOTE;
        case '\"':
            return XML_ESC_DBL_QUOTE;
        default:
            return std::string(1, c);
    }
}


/******************************************************************************
 * @brief
 * @param x
 * @return
 */
std::string CppXml::escapeString(const std::string& x) {
    std::string escapedString;
    for (char c : x) {
        escapedString += CppXml::escape(c);
    }
    return escapedString;
}


/******************************************************************************
 * @brief
 * @return
 */
std::string CppXml::uuid() {
    return std::string();
}


