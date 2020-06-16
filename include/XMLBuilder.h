//
// Created by Malcolm Hall on 6/8/20.
//

#ifndef XMLBUILDER_XMLBUILDER_H
#define XMLBUILDER_XMLBUILDER_H

#include <string>
#include "Document.h"


namespace CppXml {
    class XMLBuilder {
    public:
        XMLBuilder();

        ~XMLBuilder();

        Document *findDocument(const std::string &docName);

        bool saveDocument(std::string docName);

        Document *newDocument(
                std::string docName,
                float version = 1.0,
                XmlEncoding_t encoding = ENCODING_UTF_8,
                bool standalone = false,
                bool metadata = false);

        void enablePrettyPrint();

        void disablePrettyPrint();

    protected:
        bool prettyPrint = true;
        std::map<std::string, Document *> _documents;
    };

}
#endif //XMLBUILDER_XMLBUILDER_H
