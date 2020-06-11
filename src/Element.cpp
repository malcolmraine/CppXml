//
// Created by Malcolm Hall on 6/8/20.
//

#include "Element.h"
#include <iostream>
#include <utility>


#define CLOSING_TAG(x)    "<\\" + x + ">"
#define ATTRIBUTE(x, y)   " " + x + "=" + "\"" + y + "\""
#define TABS(n)           std::string(n, '\t')


/******************************************************************************
 * @brief
 * @param elementName
 */
Element::Element(std::string elementName) {
    name = std::move(elementName);
    parent = nullptr;
}


/******************************************************************************
 * @brief
 */
Element::~Element() {
    freeChildren(this);
}


/******************************************************************************
 * @brief
 * @param attributeName
 * @param value
 */
void Element::addAttribute(std::string attributeName, std::string value)
{
    auto *attribute = new Attribute_t;

    attribute->name = std::move(attributeName);
    attribute->type = STRING;
    attribute->value = std::move(value);
    attributes.push(attribute->name, attribute);
}


/******************************************************************************
 * @brief
 * @param attributeName
 * @param value
 */
void Element::addAttribute(std::string attributeName, char value)
{
    auto *attribute = new Attribute_t;

    attribute->name = std::move(attributeName);
    attribute->type = CHAR;
    attribute->value = std::to_string(value);
    attributes.push(attribute->name, attribute);
}


/******************************************************************************
 * addAttribute
 *
 * @brief
 * @param attributeName
 * @param value
 */
void Element::addAttribute(std::string attributeName, unsigned char value)
{
    auto *attribute = new Attribute_t;

    attribute->name = std::move(attributeName);
    attribute->type = UCHAR;
    attribute->value = std::to_string(value);
    attributes.push(attribute->name, attribute);
}


/******************************************************************************
 * addAttribute
 *
 * @brief
 * @param attributeName
 * @param value
 */
void Element::addAttribute(std::string attributeName, float value)
{
    auto *attribute = new Attribute_t;

    attribute->name = std::move(attributeName);
    attribute->type = FLOAT;
    attribute->value = std::to_string(value);
    attributes.push(attribute->name, attribute);
}


/******************************************************************************
 * addAttribute
 *
 * @brief
 * @param attributeName
 * @param value
 */
void Element::addAttribute(std::string attributeName, double value)
{
    auto *attribute = new Attribute_t;

    attribute->name = std::move(attributeName);
    attribute->type = DOUBLE;
    attribute->value = std::to_string(value);
    attributes.push(attribute->name, attribute);
}


/******************************************************************************
 * addAttribute
 *
 * @brief
 * @param attributeName
 * @param value
 */
void Element::addAttribute(std::string attributeName, int value)
{
    auto *attribute = new Attribute_t;

    attribute->name = std::move(attributeName);
    attribute->type = INT;
    attribute->value = std::to_string(value);
    attributes.push(attribute->name, attribute);
}


/******************************************************************************
 * addAttribute
 *
 * @brief
 * @param attributeName
 * @param value
 */
void Element::addAttribute(std::string attributeName, unsigned int value)
{
    auto *attribute = new Attribute_t;

    attribute->name = std::move(attributeName);
    attribute->type = UINT;
    attribute->value = std::to_string(value);
    attributes.push(attribute->name, attribute);
}


/******************************************************************************
 * addAttribute
 *
 * @brief
 * @param attributeName
 * @param value
 */
void Element::addAttribute(std::string attributeName, long value)
{
    auto *attribute = new Attribute_t;

    attribute->name = std::move(attributeName);
    attribute->type = LONG;
    attribute->value = std::to_string(value);
    attributes.push(attribute->name, attribute);
}


/******************************************************************************
 * addAttribute
 *
 * @brief
 * @param attributeName
 * @param value
 */
void Element::addAttribute(std::string attributeName, unsigned long value)
{
    auto *attribute = new Attribute_t;

    attribute->name = std::move(attributeName);
    attribute->type = ULONG;
    attribute->value = std::to_string(value);
    attributes.push(attribute->name, attribute);
}


/******************************************************************************
 * addAttribute
 *
 * @brief
 * @param attributeName
 * @param value
 */
void Element::addAttribute(std::string attributeName, long long value)
{
    auto *attribute = new Attribute_t;

    attribute->name = std::move(attributeName);
    attribute->type = LONG_LONG;
    attribute->value = std::to_string(value);
    attributes.push(attribute->name, attribute);
}


/******************************************************************************
 * addAttribute
 *
 * @brief
 * @param attributeName
 * @param value
 */
void Element::addAttribute(std::string attributeName, unsigned long long value)
{
    auto *attribute = new Attribute_t;

    attribute->name = std::move(attributeName);
    attribute->type = ULONG_LONG;
    attribute->value = std::to_string(value);
    attributes.push(attribute->name, attribute);
}


/******************************************************************************
 * toString
 *
 * @brief
 * @return
 */
std::string Element::toString()
{
    std::string subtreeString = "\n" + TABS(nestLvl) + "<" + name;

    if (!attributes.empty())
    {
        for (ssize_t i = 0; i < attributes.size(); i++)
        {
            subtreeString += ATTRIBUTE(attributes[i]->name, attributes[i]->value);
        }
    }

    subtreeString += ">";

    if (!textContent.empty())
    {
        if (!children.empty()) {
            subtreeString += "\n";
        }
        subtreeString += textContent;
    }

    if (!children.empty())
    {
        for (ssize_t i = 0; i < children.size(); i++)
        {
            subtreeString += children[i]->toString();
        }
        subtreeString += "\n" + TABS(nestLvl) ;
    }

    subtreeString += CLOSING_TAG(name);

    return subtreeString;
}


/******************************************************************************
 * freeChildren
 *
 * @brief
 * @param parentNode
 */
void Element::freeChildren(Element* parentNode)
{
    for (ssize_t i = 0; i < parentNode->children.size(); i++)
    {
        if (!parentNode->children[i]->attributes.empty())
        {
            freeAttributes(parentNode->children[i]);
        }
        if (!parentNode->children[i]->children.empty())
        {
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
void Element::freeAttributes(Element *parentNode)
{
    for (ssize_t i = 0; i < parentNode->attributes.size(); i++)
    {
        delete parentNode->attributes[i];
    }
}


/******************************************************************************
 * @brief
 * @return
 */
std::string Element::getElementKey() {
    return _elementKey;
}


/******************************************************************************
 * @brief
 * @param key
 */
void Element::setElementKey(std::string key) {
    _elementKey = std::move(key);
}





