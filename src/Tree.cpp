//
// Created by Malcolm Hall on 6/8/20.
//

#include "Tree.h"

#include <utility>

#define PATH_REPR_DELIM "->"


/******************************************************************************
 * Tree
 *
 * @brief Constructor for Tree
 */
Tree::Tree() {
    root = new Element("_root");
    root->parent = nullptr;
}


/******************************************************************************
 * ~Tree
 *
 * @brief Destructor for Tree
 */
Tree::~Tree() {
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
Element* Tree::addElement(const std::string& elementName, Element *parent) const {
    auto *newElement = new Element(elementName);
    int tagDifferentiator = 0;

    /* To fix the issue of multiple child elements of the same name, we append a unique identifier
     * onto the element name using _#$# as a delimiter. The first instance of the element name will
     * use _#$#0 as the identifier and the second instance will use _#$#1 and so on for each
     * additional use of that element name. */
    std::string elementNameUnique = elementName + "_#$#" + std::to_string(tagDifferentiator);
    std::string elementKey = parent->getElementKey();

    if (parent != nullptr)
    {
        while (tagDifferentiator < IDENTICAL_TAG_LIMIT && parent->children.count(elementNameUnique))
        {
            elementNameUnique = elementName + ELEM_KEY_IDX_DELIM + std::to_string(tagDifferentiator);
            tagDifferentiator++;
        }

        if (!parent->getElementKey().empty())
        {
            elementKey += "->";
        }

        newElement->setElementKey(elementKey + elementNameUnique);
    }
    else
    {
        newElement->setElementKey(elementNameUnique);
    }

    /* Now we set the new element's parent and nest level accordingly. The element is
     * pushed onto the data structure containing all the parent's children. */
    newElement->parent = parent;
    newElement->nestLvl = parent->nestLvl + 1;
    parent->children.push(elementName, newElement);
    return newElement;
}


/******************************************************************************
 * findElement
 *
 * @brief
 * @param nodePath
 * @return
 */
 // TODO Fix this and separate out parser
Element *Tree::findElement(std::string nodePath)
{
    size_t pos = 0;
    std::string path = std::move(nodePath);
    std::string delimiter = PATH_REPR_DELIM;
    Element* element = root;

    while ((pos = path.find(PATH_REPR_DELIM)) != std::string::npos)
    {
        std::string nodeName = path.substr(0, pos);

        if (element->children.count(nodeName))
        {
            element = element->children[nodeName];
            path.erase(0, pos + delimiter.length());
        }
        else
        {
            return nullptr;
        }
    }
    return element->children[path];
}


/******************************************************************************
 * deleteElement
 *
 * @brief
 * @param nodePath
 * @return
 */
bool Tree::deleteElement(std::string nodePath) {
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
bool Tree::deleteSubTree(std::string rootNodePath) {
    Element *e = findElement(std::move(rootNodePath));

    e->freeChildren(e);
    delete e;

    return true;
}
