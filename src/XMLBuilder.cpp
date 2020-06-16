//
// Created by Malcolm Hall on 6/8/20.
//

#include "../include/XMLBuilder.h"

#include <utility>


/******************************************************************************
 * XMLBuilder
 *
 * @brief
 */
CppXml::XMLBuilder::XMLBuilder() {


}


/******************************************************************************
 * ~XMLBuilder
 *
 * @brief
 */
CppXml::XMLBuilder::~XMLBuilder() {
//    auto it = _documents.begin();
//
//    while (it != _documents.end())
//    {
//        delete it->second;
//    }
}


/******************************************************************************
 * @brief
 * @param docName
 * @return
 */
CppXml::Document *CppXml::XMLBuilder::findDocument(const std::string &docName) {
    if (_documents.count(docName)) {
        return _documents[docName];
    }
    else {
        return nullptr;
    }
}


/******************************************************************************
 * newDocument
 *
 * @brief
 * @param docName
 * @param version
 * @param encoding
 * @param standalone
 * @param metadata
 * @return
 */
CppXml::Document *CppXml::XMLBuilder::newDocument(
        std::string docName,
        float version,
        XmlEncoding_t encoding,
        bool standalone,
        bool metadata
) {
    auto *doc = new Document(std::move(docName));
    doc->version = version;
    doc->encoding = std::move(encoding);
    doc->standalone = standalone;

    if (metadata) {
        doc->addMetaData();
    }
    _documents.insert(std::pair<std::string, Document *>(doc->name, doc));
    return doc;
}


bool CppXml::XMLBuilder::saveDocument(std::string docName) {
    return false;
}

/******************************************************************************
 * @brief
 */
void CppXml::XMLBuilder::enablePrettyPrint() {
    prettyPrint = true;
}


/******************************************************************************
 * @brief
 */
void CppXml::XMLBuilder::disablePrettyPrint() {
    prettyPrint = false;
}





