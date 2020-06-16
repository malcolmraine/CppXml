//
// Created by Malcolm Hall on 6/8/20.
//

#ifndef XMLBUILDER_TREE_H
#define XMLBUILDER_TREE_H

#include <map>
#include <string>
#include <typeinfo>
#include "Element.h"
#include "../include/helper.h"




namespace CppXml {

    const std::string ELEM_KEY_IDX_DELIM = "?_#$#";

    int getElementKeyIdx(const std::string& x);
    std::string getElementKeyName(const std::string& x);

    class Tree {
    public:
        Tree();

        ~Tree();

        Element *addElement(const std::string &elementName, Element *parent = nullptr) const;

        Element *findElement(std::string nodePath);    // findElement("root->nodeA->nodeB)

        bool deleteElement(std::string nodePath);

        bool deleteSubTree(std::string rootNodePath);

        Element *root;
    };
}

#endif //XMLBUILDER_TREE_H
