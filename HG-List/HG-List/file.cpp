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
    
}

hg::File::File(const File &other) {
    fileName = other.fileName;
    fileStream = std::fstream(fileName);
}

hg::File::~File() {
    fileStream.close();
}

std::string hg::File::getFileName() {
    return fileName;
}

std::vector<std::unique_ptr<std::string>> hg::File::readFileLineByLine() {
    std::string content = readFile();
    std::vector<std::unique_ptr<std::string>> vec;
    
    int lastLine = 0;
    
    for(int i = 0; i < content.size(); i++) {
        if(content[i] == '\n') {
            vec.emplace_back(std::make_unique<std::string>(hg::substr(content, lastLine, i)));
            lastLine = i + 1;
        }
    }
    return vec;
}

std::string hg::File::readFile() {
    fileStream.open(fileName, std::ifstream::in);
    std::stringstream str;
    
    str << fileStream.rdbuf();
    
    fileStream.close();
    return str.str();
}

void hg::File::writeFile(const std::string &content) {
    fileStream.open(fileName, std::ofstream::out);
    fileStream << content;
    fileStream.close();
}


std::string hg::transformLinesToString(std::vector<std::unique_ptr<std::string>> *lines) {
    std::string s;
    
    for(int i = 0; i < lines->size(); i++) {
        s += *(*lines)[i] + "\n";
    }
    
    return s;
}

std::string hg::substr(const std::string &string, unsigned int start, unsigned int end) {
    std::string s;
    for(int i = start; i < end; i++) {
        s.push_back(string[i]);
    }
    return s;
}

bool hg::find(const std::string &string, const std::string &search) {
    if(string.find(search) > 0 && string.find(search) < string.length()) {
        return true;
    }
    return false;
}
