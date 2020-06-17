//
// Created by Malcolm Hall on 6/8/20.
//

#include "../include/Element.h"
#include <iostream>
#include <utility>
#include "../include/helper.h"

#define CLOSING_TAG(x)    "<\\" + x + ">"
#define OPENING_TAG(name, attributes)   "<" + name + attributes + ">"
#define SELFCLOSING_TAG(name, attributes)   "<" + name + attributes + "\\>"
#define ATTRIBUTE(x, y)   " " + x + "=" + "\"" + y + "\""
#define TABS(n)           std::string(n, '\t')


/******************************************************************************
 * @brief
 * @param elementName
 */
CppXml::Element::Element(std::string elementName) {
    name = std::move(elementName);
    parent = nullptr;
}


/******************************************************************************
 * @brief
 */
CppXml::Element::~Element() {
    freeChildren(this);
}


/******************************************************************************
 * @brief
 * @param attributeName
 * @param value
 */
CppXml::Element *CppXml::Element::addAttribute(std::string attributeName, std::string value) {
    auto *attribute = new Attribute_t;

    attribute->name = std::move(attributeName);
    attribute->type = STRING;
    attribute->value = std::move(value);
    attributes.push(attribute->name, attribute);

    return this;
}


/******************************************************************************
 * @brief
 * @param attributeName
 * @param value
 */
CppXml::Element *CppXml::Element::addAttribute(std::string attributeName, char value) {
    auto *attribute = new Attribute_t;

    attribute->name = std::move(attributeName);
    attribute->type = CHAR;
    attribute->value = std::to_string(value);
    attributes.push(attribute->name, attribute);

    return this;
}


/******************************************************************************
 * addAttribute
 *
 * @brief
 * @param attributeName
 * @param value
 */
CppXml::Element *CppXml::Element::addAttribute(std::string attributeName, unsigned char value) {
    auto *attribute = new Attribute_t;

    attribute->name = std::move(attributeName);
    attribute->type = UCHAR;
    attribute->value = std::to_string(value);
    attributes.push(attribute->name, attribute);

    return this;
}


/******************************************************************************
 * addAttribute
 *
 * @brief
 * @param attributeName
 * @param value
 */
CppXml::Element *CppXml::Element::addAttribute(std::string attributeName, float value) {
    auto *attribute = new Attribute_t;

    attribute->name = std::move(attributeName);
    attribute->type = FLOAT;
    attribute->value = std::to_string(value);
    attributes.push(attribute->name, attribute);

    return this;
}


/******************************************************************************
 * addAttribute
 *
 * @brief
 * @param attributeName
 * @param value
 */
CppXml::Element *CppXml::Element::addAttribute(std::string attributeName, double value) {
    auto *attribute = new Attribute_t;

    attribute->name = std::move(attributeName);
    attribute->type = DOUBLE;
    attribute->value = std::to_string(value);
    attributes.push(attribute->name, attribute);

    return this;
}


/******************************************************************************
 * addAttribute
 *
 * @brief
 * @param attributeName
 * @param value
 */
CppXml::Element *CppXml::Element::addAttribute(std::string attributeName, int value) {
    auto *attribute = new Attribute_t;

    attribute->name = std::move(attributeName);
    attribute->type = INT;
    attribute->value = std::to_string(value);
    attributes.push(attribute->name, attribute);

    return this;
}


/******************************************************************************
 * addAttribute
 *
 * @brief
 * @param attributeName
 * @param value
 */
CppXml::Element *CppXml::Element::addAttribute(std::string attributeName, unsigned int value) {
    auto *attribute = new Attribute_t;

    attribute->name = std::move(attributeName);
    attribute->type = UINT;
    attribute->value = std::to_string(value);
    attributes.push(attribute->name, attribute);

    return this;
}


/******************************************************************************
 * addAttribute
 *
 * @brief
 * @param attributeName
 * @param value
 */
CppXml::Element *CppXml::Element::addAttribute(std::string attributeName, long value) {
    auto *attribute = new Attribute_t;

    attribute->name = std::move(attributeName);
    attribute->type = LONG;
    attribute->value = std::to_string(value);
    attributes.push(attribute->name, attribute);

    return this;
}


/******************************************************************************
 * addAttribute
 *
 * @brief
 * @param attributeName
 * @param value
 */
CppXml::Element *CppXml::Element::addAttribute(std::string attributeName, unsigned long value) {
    auto *attribute = new Attribute_t;

    attribute->name = std::move(attributeName);
    attribute->type = ULONG;
    attribute->value = std::to_string(value);
    attributes.push(attribute->name, attribute);

    return this;
}


/******************************************************************************
 * addAttribute
 *
 * @brief
 * @param attributeName
 * @param value
 */
CppXml::Element *CppXml::Element::addAttribute(std::string attributeName, long long value) {
    auto *attribute = new Attribute_t;

    attribute->name = std::move(attributeName);
    attribute->type = LONG_LONG;
    attribute->value = std::to_string(value);
    attributes.push(attribute->name, attribute);

    return this;
}


/******************************************************************************
 * addAttribute
 *
 * @brief
 * @param attributeName
 * @param value
 */
CppXml::Element* CppXml::Element::addAttribute(std::string attributeName, unsigned long long value) {
    auto *attribute = new Attribute_t;

    attribute->name = std::move(attributeName);
    attribute->type = ULONG_LONG;
    attribute->value = std::to_string(value);
    attributes.push(attribute->name, attribute);

    return this;
}


/******************************************************************************
 * @brief
 * @return
 */
CppXml::Element *CppXml::Element::addTextContent(const std::string& text) {
    textContent += text;
    return this;
}


/******************************************************************************
 * toString
 *
 * @brief
 * @return
 */
std::string CppXml::Element::elementToString() {
    std::string escapedName = escapeString(name);
    std::string subtreeString = "\n" + TABS(nestLvl);
    std::string attributeString;

    if (!attributes.empty()) {
        for (ssize_t i = 0; i < attributes.size(); i++) {
            attributeString += ATTRIBUTE(
                    escapeString(attributes[i]->name),
                    escapeString(attributes[i]->value)
                    );
        }
    }

    subtreeString += OPENING_TAG(escapedName, attributeString);

    //subtreeString += ">";

    if (!textContent.empty()) {
        if (!children.empty()) {
            subtreeString += "\n";
        }
        subtreeString += escapeString(textContent);
    }

    if (!children.empty()) {
        for (ssize_t i = 0; i < children.size(); i++) {
            subtreeString += children[i]->elementToString();
        }
        subtreeString += "\n" + TABS(nestLvl);
    }

    subtreeString += CLOSING_TAG(escapedName);

    return subtreeString;
}


/******************************************************************************
 * freeChildren
 *
 * @brief
 * @param parentNode
 */
void CppXml::Element::freeChildren(Element *parentNode) {
    for (ssize_t i = 0; i < parentNode->children.size(); i++) {
        if (!parentNode->children[i]->attributes.empty()) {
            freeAttributes(parentNode->children[i]);
        }
        if (!parentNode->children[i]->children.empty()) {
            freeChildren(parentNode->children[i]);
            delete parentNode->children[i];
        }
    }
}


/******************************************************************************
 * freeAttributes
 *
 * @brief
 * @param parentNode
 */
void CppXml::Element::freeAttributes(Element *parentNode) {
    for (ssize_t i = 0; i < parentNode->attributes.size(); i++) {
        delete parentNode->attributes[i];
    }
}


/******************************************************************************
 * @brief
 * @return
 */
std::string CppXml::Element::getElementKey() {
    return _elementKey;
}


/******************************************************************************
 * @brief
 * @param key
 */
void CppXml::Element::setElementKey(std::string key) {
    _elementKey = std::move(key);
}






