cmake_minimum_required(VERSION 3.16)
project(XMLBuilder)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        XMLBuilder
        main.cpp
        XMLBuilder/XMLBuilder.cpp
        XMLBuilder/XMLBuilder.h
        XMLBuilder/Tree.cpp
        XMLBuilder/Tree.h
        XMLBuilder/helper.cpp
        XMLBuilder/helper.h
        XMLBuilder/Element.cpp
        XMLBuilder/Element.h
        XMLBuilder/Document.cpp XMLBuilder/Document.h XMLBuilder/AssocVec.cpp XMLBuilder/AssocVec.h XMLBuilder/Tokenizer.cpp XMLBuilder/Tokenizer.h XMLBuilder/Parser.cpp XMLBuilder/Parser.h)