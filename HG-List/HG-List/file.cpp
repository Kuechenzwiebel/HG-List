//
//  File.cpp
//  HG-List
//
//  Created by Tobias Pflüger on 11.05.19.
//  Copyright © 2019 Tobias Pflüger. All rights reserved.
//

#include "file.hpp"

hg::File::File(std::string fileName):
fileName(fileName) {
    file = std::ifstream(fileName);
    
    if(!file) {
        std::cerr << "Cant open the file: " << fileName << std::endl;
    }
}

hg::File::~File() {
    file.close();
}

std::vector <std::string> hg::File::readFileLineByLine() {
    std::vector <std::string> vec;
    
    std::string str;
    while (std::getline(file, str)) {
        if(str.size() > 0) {
            vec.push_back(str);
        }
    }
    return vec;
}

std::string hg::File::readFile() {
    std::string str;
    
    try {
        std::stringstream contentStream;
        
        contentStream << file.rdbuf();
        str = contentStream.str();
    }
    catch (std::ifstream::failure e) {
        printf("File could not be read!\n");
    }
    
    return str;
}
