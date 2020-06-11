//
// Created by Malcolm Hall on 6/8/20.
//

#ifndef XMLBUILDER_TREE_H
#define XMLBUILDER_TREE_H

#include <map>
#include <string>
#include <typeinfo>
#include "Element.h"

#define IDENTICAL_TAG_LIMIT 10000
#define ELEM_KEY_IDX_DELIM    "_#$#"

class Tree {
public:
    Tree();
    ~Tree();

    Element* addElement(const std::string& elementName, Element *parent) const;
    Element* findElement(std::string nodePath);    // findElement("root->nodeA->nodeB)
    bool deleteElement(std::string nodePath);
    bool deleteSubTree(std::string rootNodePath);

    Element *root;
};


#endif //XMLBUILDER_TREE_H
