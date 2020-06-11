//
// Created by Malcolm Hall on 6/8/20.
//

#ifndef XMLBUILDER_ELEMENT_H
#define XMLBUILDER_ELEMENT_H

#include <string>
#include <map>
#include "AssocVec.h"

enum Type {
    UNKNOWN = -1,
    STRING,
    CHAR,
    UCHAR,
    FLOAT,
    DOUBLE,
    INT,
    LONG,
    LONG_LONG,
    UINT,
    ULONG,
    ULONG_LONG
};


typedef struct {
    std::string name;
    std::string value;
    Type type;
} Attribute_t;


class Element {
public:
    explicit Element(std::string elementName);
    ~Element();

    void addAttribute(std::string attributeName, std::string value);
    void addAttribute(std::string attributeName, char value);
    void addAttribute(std::string attributeName, unsigned char value);
    void addAttribute(std::string attributeName, float value);
    void addAttribute(std::string attributeName, double value);
    void addAttribute(std::string attributeName, int value);
    void addAttribute(std::string attributeName, unsigned int value);
    void addAttribute(std::string attributeName, long value);
    void addAttribute(std::string attributeName, unsigned long value);
    void addAttribute(std::string attributeName, long long value);
    void addAttribute(std::string attributeName, unsigned long long value);

    Element *parent;
    //std::map<std::string, Attribute_t*> attributes;
    AssocVec<Attribute_t*> attributes;
    AssocVec<Element*> children;
    std::string name;
    std::string textContent;
    std::string toString();
    void freeChildren(Element* parentNode);
    std::string getElementKey();
    void setElementKey(std::string key);
    int nestLvl = 0;


private:
    static void freeAttributes(Element* parentNode);
    std::string _elementKey = "";

};



#endif //XMLBUILDER_ELEMENT_H
