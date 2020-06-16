cmake_minimum_required(VERSION 3.16)
project(CppXml)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        XMLBuilder
        main.cpp
        src/XMLBuilder.cpp
        include/XMLBuilder.h
        src/Tree.cpp
        include/Tree.h
        src/helper.cpp
        include/helper.h
        src/Element.cpp
        include/Element.h
        src/Document.cpp
        include/Document.h
        src/AssocVec.cpp
        include/AssocVec.h
        src/Tokenizer.cpp
        include/Tokenizer.h
        src/Parser.cpp
        include/Parser.h
)