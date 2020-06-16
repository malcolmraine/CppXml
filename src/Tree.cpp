//
// Created by Malcolm Hall on 6/8/20.
//

#include "../include/Tree.h"

#include <utility>
#include <iostream>
#include <regex>

#define PATH_REPR_DELIM "->"
#define IDENTICAL_TAG_LIMIT 10000


int CppXml::getElementKeyIdx(const std::string& x)
{
    unsigned long delimEndPos = x.find(ELEM_KEY_IDX_DELIM) + ELEM_KEY_IDX_DELIM.length();
    return std::stoi(x.substr(delimEndPos,delimEndPos + 1));
}

std::string CppXml::getElementKeyName(const std::string& x)
{
    return x.substr(0, x.find(ELEM_KEY_IDX_DELIM));
}



/******************************************************************************
 * Tree
 *
 * @brief Constructor for Tree
 */
CppXml::Tree::Tree() {
    root = new Element("_root");
    root->parent = nullptr;
}


/******************************************************************************
 * ~Tree
 *
 * @brief Destructor for Tree
 */
CppXml::Tree::~Tree() {
    root->freeChildren(root);
    delete root;
}


/******************************************************************************
 * addElement
 *
 * @brief Add a new element to the tree.
 * @param elementName
 * @param parent
 * @return
 */
CppXml::Element* CppXml::Tree::addElement(const std::string& elementName, Element *parent) const {
    auto *newElement = new Element(elementName);
    int tagDifferentiator = 0;

    newElement->parent = parent != nullptr ? parent : root;
    newElement->nestLvl = newElement->parent->nestLvl + 1;

    std::string baseKey = newElement->parent->getElementKey();

    if (!newElement->parent->getElementKey().empty())
    {
        baseKey += "->";
    }

    baseKey += elementName;

    /* To fix the issue of multiple child elements of the same name, we append a unique identifier
     * onto the element name using ?_#$# as a delimiter. The first instance of the element name will
     * use ?_#$#0 as the identifier and the second instance will use ?_#$#1 and so on for each
     * additional use of that element name. */
    std::string elementKey = baseKey + ELEM_KEY_IDX_DELIM + std::to_string(tagDifferentiator);

    if (newElement->parent != nullptr)
    {
        while (tagDifferentiator < IDENTICAL_TAG_LIMIT && newElement->parent->children.count(elementKey))
        {
            elementKey = baseKey + ELEM_KEY_IDX_DELIM + std::to_string(tagDifferentiator);
            tagDifferentiator++;
        }

        newElement->setElementKey(elementKey);
    }
    else
    {
        newElement->setElementKey(elementKey);
    }
    
    /* The element is pushed onto the data structure containing all the parent's children. */
    newElement->parent->children.push(elementKey, newElement);
    return newElement;
}


/******************************************************************************
 * findElement
 *
 * @brief
 * @param nodePath
 * @return
 */
 CppXml::Element *CppXml::Tree::findElement(std::string nodePath)
{
    std::string path = std::move(nodePath);
    std::string childKey;
    std::string delimiter = PATH_REPR_DELIM;
    Element* e = root;
    std::vector<std::string> uniqueNames;

    /*
     * use whole path regex to check path string validity.
     *
     * Whole path regex: (?:(?:([\w^\s]+)(?:\[(\d)+\]|\?_#\$#(\d)+)?)(?:\->)?){1,255}
     * Unique name regex: [\w^\s]+(?:\[\d+\]|\?_#\$#\d+)?
     *
     * XML tag regex:
     * XML attribute regex:
     * XML name regex:
     */

    /* Regular expression for the entire search path to check for properly formed search strings    */
    std::regex searchPathRegex(R"((?:(?:([\w^\s]+)(?:\[(\d)+\]|\?_#\$#(\d)+)?)(?:\->)?){1,255})");

    /* Check if the given search path is even valid before doing anything else  */
    if (!std::regex_search(path, searchPathRegex))
    {
        return root;
    }

    /* Regular expression to match the element names or keys that are given in the search path  */
    std::regex elementNameRegex(R"([\w^\s]+(?:\[\d+\]|\?_#\$#\d+)?)");

    /* Regular expression to match the element index. This could be in normal index
     * notation or in the unique identifier notation that is used internally    */
    std::regex uniqueSuffixRegex(R"(\[\d+\]|\?_#\$#\d+)");

    /* Regular expression specifically for the index notation   */
    std::regex idxNotationSuffix(R"([\w^\s]+(?:\[\d+\]))");

    std::smatch nameMatch;
    while (std::regex_search(path, nameMatch, elementNameRegex)) {
        std::string s = nameMatch.str(0);

        if (!std::regex_search(s, uniqueSuffixRegex))
        {
            s += ELEM_KEY_IDX_DELIM + "0";
        }
        else
        {
            std::smatch idxMatch;
            if (std::regex_search(s, idxMatch, idxNotationSuffix))
            {
                s = s.substr(0, s.find(idxMatch.str(0)) + 1)
                        .append(ELEM_KEY_IDX_DELIM)
                        .append(idxMatch.str(0).substr(2, 1));
            }
        }

        uniqueNames.push_back(s);
        path = nameMatch.suffix().str();
    }

    childKey = uniqueNames[0];

    if (e->children.count(childKey))
    {
        e = e->children[childKey];
    }
    else
    {
        /* Return the root element if the key is not found in the child object store   */
        return root;
    }

    for (int i = 1; i < uniqueNames.size(); i++)
    {
        childKey += PATH_REPR_DELIM + uniqueNames[i];
        if (e->children.count(childKey))
        {
            e = e->children[childKey];
        }
        else
        {
            /* Return the root element if the key is not found in the child object store   */
            return root;
        }
        std::cout << childKey << std::endl;
    }

    return e;
}


/******************************************************************************
 * deleteElement
 *
 * @brief
 * @param nodePath
 * @return
 */
bool CppXml::Tree::deleteElement(std::string nodePath) {
    Element *e = findElement(std::move(nodePath));
    Element *parent = e->parent;

    for (ssize_t i = 0; i < e->children.size(); i++)
    {
        parent->children.push(e->children[i]->name, e->children[i]);
    }

    delete e;

    return true;
}


/******************************************************************************
 * deleteSubTree
 *
 * @brief
 * @param rootNodePath
 * @return
 */
bool CppXml::Tree::deleteSubTree(std::string rootNodePath) {
    Element *e = findElement(std::move(rootNodePath));

    e->freeChildren(e);
    delete e;

    return true;
}