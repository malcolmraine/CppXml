//
// Created by Malcolm Hall on 6/8/20.
//

#ifndef XMLBUILDER_XMLBUILDER_H
#define XMLBUILDER_XMLBUILDER_H


#include <string>
#include "Document.h"


#define XML_ESC_RIGHT_CARAT      "&gt;"
#define XML_ESC_LEFT_CARAT       "&lt;"
#define XML_ESC_AMP              "&amp;"
#define XML_ESC_SINGLE_QUOTE     "&apos;"
#define XML_ESC_DBL_QUOTE        "&quot;"



inline std::string escape(char symbol)
{
    switch (symbol) {
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
            return std::string(1, symbol);
    }
}


class XMLBuilder {
public:
    XMLBuilder();
    ~XMLBuilder();

    Document* findDocument(const std::string& docName);
    bool saveDocument(std::string docName);
    Document* newDocument(
            std::string docName,
            float version=1.0,
            XmlEncoding_t encoding=ENCODING_UTF_8,
            bool standalone=false,
            bool metadata=false);

    void enablePrettyPrint();
    void disablePrettyPrint();

private:
    bool prettyPrint = true;
    std::map<std::string, Document*>_documents;

};


#endif //XMLBUILDER_XMLBUILDER_H
