/**************************************************************************************************
* File: Document.h
* Description:
* Author: Malcolm Hall
* Date: 6/9/20
* Version: 1
*
**************************************************************************************************/
#ifndef XMLBUILDER_DOCUMENT_H
#define XMLBUILDER_DOCUMENT_H

/**************************************************************************************************
*       INCLUDES AND DECLARATIONS
**************************************************************************************************/
#include "Tree.h"


typedef std::string XmlEncoding_t;

const XmlEncoding_t ENCODING_UTF_8 = "UTF-8";
const XmlEncoding_t ENCODING_UTF_16 = "UTF-16";
const XmlEncoding_t ENCODING_ISO_10646_UCS_2 = "ISO-10646-UCS-2";
const XmlEncoding_t ENCODING_ISO_10646_UCS_4 = "ISO-10646-UCS-4";

#define DEFAULT_ENCODING ENCODING_UTF_8

typedef struct {
    bool author = true;
    bool timestamp = true;
    bool uuid = true;
} Metadata_t;


class Document : public Tree {
public:
    Document(std::string docName);
    ~Document();
    void addMetaData();
    std::string xmlHeader();

    std::string name;
    XmlEncoding_t encoding;
    float version;
    bool standalone;
    Metadata_t metadata;

protected:
    std::string getHeader() const;
};




#endif //XMLBUILDER_DOCUMENT_H
/**************************************************************************************************
*       END OF FILE
**************************************************************************************************/