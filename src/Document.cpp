/**************************************************************************************************
* File: Document.cpp
* Description:
* Author: Malcolm Hall
* Date: 6/9/20
* Version: 1
*
**************************************************************************************************/

/**************************************************************************************************
*       INCLUDES AND DECLARATIONS
**************************************************************************************************/
#include <ctime>
#include <utility>
#include "../include/Document.h"
#include "../include/helper.h"


/******************************************************************************
 * Document
 *
 * @brief
 */
CppXml::Document::Document(std::string docName) {
    name = std::move(docName);
    encoding = DEFAULT_ENCODING;
    version = 1.0;
    standalone = true;
}


/******************************************************************************
 * ~Document
 *
 * @brief
 */
CppXml::Document::~Document() {

}


/******************************************************************************
 * @brief
 * @param rootName
 */
void CppXml::Document::setRoot(std::string rootName) {
    root->name = std::move(rootName);
}


/******************************************************************************
 * addMetaData
 *
 * @brief
 */
void CppXml::Document::addMetaData() {
    auto *newElement = new Element("meta");

    if (root != nullptr) {
        newElement->parent = root;
        newElement->nestLvl = root->nestLvl + 1;
        Element *e;

        if (metadata.author) {
            e = addElement("author", newElement);
            e->textContent = "";
        }

        if (metadata.timestamp) {
            time_t now = time(nullptr);
            tm *gmtm = gmtime(&now);
            std::string dt = std::string(asctime(gmtm));
            e = addElement("created_at", newElement);
            e->textContent = dt.substr(0, dt.length() - 1);
            delete gmtm;
        }

        if (metadata.uuid) {
            e = addElement("uuid", newElement);
            e->textContent = "";
        }

        root->children.push("meta", newElement);
    }
}


/******************************************************************************
 * xmlHeader
 *
 * @brief
 * @return
 */
std::string CppXml::Document::xmlHeader() {
    return getHeader();
}


/******************************************************************************
 * getHeader
 *
 * @brief
 * @return
 */
std::string CppXml::Document::getHeader() const {
    return "<?xml version=\""
           + std::to_string(version)
           + "\" standalone=\""
           + (standalone ? "yes" : "no")
           + "\" ?>";
}


std::string CppXml::Document::toString() {
    return root->elementToString();
}

/**************************************************************************************************
*       END OF FILE
**************************************************************************************************/

