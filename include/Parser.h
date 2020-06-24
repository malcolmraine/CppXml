/**************************************************************************************************
* File: Parser.h
* Description:
* Author: Malcolm Hall
* Date: 6/10/20
* Version: 1
*
**************************************************************************************************/
#ifndef XMLBUILDER_PARSER_H
#define XMLBUILDER_PARSER_H

/**************************************************************************************************
*       INCLUDES AND DECLARATIONS
**************************************************************************************************/
#include <string>
#include <vector>
#include <map>
#include "Tokenizer.h"

namespace CppXml {

enum ComponentType {
    OPENING_TAG,
    CLOSING_TAG,
    SELF_CLOSING_TAG,
    ATTRIBUTE,
    XML_DECLARATION,
    TEXT_CONTENT
};

enum ConsumptionState {
    UNKNOWN,
    INIT,
    XML_DECLARATION_CONSUMPTION,
    XML_DECLARATION_CONSUMPTION_END,
    UNKNOWN_TAG_CONSUMPTION,
    OPENING_TAG_CONSUMPTION,
    OPENING_TAG_CONSUMPTION_END,
    SELF_CLOSING_TAG_CONSUMPTION,
    SELF_CLOSING_TAG_CONSUMPTION_END,
    CLOSING_TAG_CONSUMPTION,
    CLOSING_TAG_CONSUMPTION_END,
    ATTRIBUTE_NAME_CONSUMPTION,
    ATTRIBUTE_NAME_CONSUMPTION_END,
    ATTRIBUTE_VALUE_CONSUMPTION,
    ATTRIBUTE_VALUE_CONSUMPTION_END,
    TEXT_CONTENT_CONSUMPTION
};

/*
 * Opening tags: name will be filled, value will be empty
 * Closing tags: name will be filled, value will be empty
 * Attributes: name and value will be filled
 * Text content: name will be empty and value will be filled
 */
typedef struct {
    std::string name;
    std::string value;
    ComponentType type;

} XmlComponent_t;

/*
 * We will read in the xml file character by character assemble the sub-components.
 *
 *
 */
    class Parser {
    public:
        Parser();
        ~Parser();

        /*
         * each character will be read in from the tokenizer and used to build document
         * components. The character and the current state will be used to either build
         * the active components name or value or to determine whether a state transitionn is necessary.
         * If a state transition occurs, a new component needs to be created as pushed
         * onto the end of the component vector. This will be the new active component.
         */
        void parse();
        inline XmlComponent_t* activeComponent() { return components.back(); };
        void loadDocument(std::string file);
        void stateTransition(char c);
        void buildDocument();
        bool fileExists();

    protected:
        Tokenizer tokenizer;
        /* This is just for holding the tag components as we build the document.
         * We need to make sure that all tags are closed. When we encounter a tag,
         * the component struct will be pushed onto the stack. WHen we encounter a closing
         * tag, we check if the name matches that of the component on the top of the stack.
         * If it matches, pop that component and keep moving. Otherwise, throw an error.
         * If the stack is not empty after all the components are processed, we know that
         * the document is not well-formed */
        std::vector<XmlComponent_t*> tagStack;

        /* Vector for holding the component structs in order */
        std::vector<XmlComponent_t*> components;

        ConsumptionState state;
        std::string docName;
        bool fileLoaded;

    };
}


#endif //XMLBUILDER_PARSER_H
/**************************************************************************************************
*       END OF FILE
**************************************************************************************************/