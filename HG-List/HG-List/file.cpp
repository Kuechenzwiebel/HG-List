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
    fileStream = std::fstream(fileName);
    
    if(!fileStream) {
        std::cerr << "Cant open the file: " << fileName << std::endl;
    }
}

hg::File::~File() {
    fileStream.close();
}

std::vector<std::string> hg::File::readFileLineByLine() {
    std::string content = readFile();
    std::vector<std::string> vec;
    
    int lastLine = 0;
    
    for(int i = 0; i < content.size(); i++) {
        if(content[i] == '\n') {
            vec.push_back(hg::substr(content, lastLine, i));
            lastLine = i + 1;
        }
    }
    return vec;
}

std::string hg::File::readFile() {
    fileStream.open(fileName, std::ifstream::in);
    std::string str;
    
    try {
        std::stringstream contentStream;
        
        contentStream << fileStream.rdbuf();
        str = contentStream.str();
    }
    catch (std::ifstream::failure e) {
        printf("File could not be read!\n");
    }
    fileStream.close();
    return str;
}

void hg::File::writeFile(std::string content) {
    fileStream.open(fileName, std::ofstream::out);
    fileStream << content;
    fileStream.close();
}


std::string hg::transformLinesToString(std::vector<std::string> *lines) {
    std::string s;
    
    for(int i = 0; i < lines->size(); i++) {
        s += (*lines)[i] + "\n";
    }
    
    return s;
}

std::string hg::substr(std::string string, unsigned int start, unsigned int end) {
    std::string s;
    for(int i = start; i < end; i++) {
        s.push_back(string[i]);
    }
    return s;
}

bool hg::find(std::string string, std::string search) {
    if(string.find(search) > 0 && string.find(search) < string.length()) {
        return true;
    }
    return false;
}
