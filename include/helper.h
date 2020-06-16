//
// Created by Malcolm Hall on 6/8/20.
//

#ifndef XMLBUILDER_HELPER_H
#define XMLBUILDER_HELPER_H

#include <string>


#define XML_ESC_RIGHT_CARAT      "&gt;"
#define XML_ESC_LEFT_CARAT       "&lt;"
#define XML_ESC_AMP              "&amp;"
#define XML_ESC_SINGLE_QUOTE     "&apos;"
#define XML_ESC_DBL_QUOTE        "&quot;"


namespace CppXml {
    inline std::string escape(char symbol);

    std::string escapeString(const std::string& x);

    std::string uuid();

    inline std::string stripSubstring(std::string x, const std::string& substring);

    std::string to_hashstring(std::string x);   // Generate a hash string from a plain string

}
#endif //XMLBUILDER_HELPER_H
