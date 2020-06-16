//
// Created by Malcolm Hall on 6/8/20.
//

#ifndef XMLBUILDER_ELEMENT_H
#define XMLBUILDER_ELEMENT_H

#include <string>
#include <map>
#include "AssocVec.h"

namespace CppXml {

    enum Type {
        UNKNOWN = -1, STRING, CHAR, UCHAR, FLOAT, DOUBLE, INT, LONG, LONG_LONG, UINT, ULONG, ULONG_LONG
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

        Element *addAttribute(std::string attributeName, std::string value);

        Element *addAttribute(std::string attributeName, char value);

        Element *addAttribute(std::string attributeName, unsigned char value);

        Element *addAttribute(std::string attributeName, float value);

        Element *addAttribute(std::string attributeName, double value);

        Element *addAttribute(std::string attributeName, int value);

        Element *addAttribute(std::string attributeName, unsigned int value);

        Element *addAttribute(std::string attributeName, long value);

        Element *addAttribute(std::string attributeName, unsigned long value);

        Element *addAttribute(std::string attributeName, long long value);

        Element *addAttribute(std::string attributeName, unsigned long long value);

        Element* addTextContent(const std::string& text);
        std::string elementToString();

        void freeChildren(Element *parentNode);

        std::string getElementKey();

        void setElementKey(std::string key);

        Element *parent;
        int nestLvl = 0;
        AssocVec<Attribute_t *> attributes;
        AssocVec<Element *> children;
        std::string name;
        std::string textContent;

    private:
        static void freeAttributes(Element *parentNode);

        std::string _elementKey = "";

    };

}

#endif //XMLBUILDER_ELEMENT_H
