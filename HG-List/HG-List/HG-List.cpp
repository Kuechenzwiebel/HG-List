//
//  HG-List.cpp
//  HG-List
//
//  Created by Tobias Pflüger on 13.02.19.
//  Copyright © 2019 Tobias Pflüger. All rights reserved.
//

#include "HG-List.hpp"

hg::HGList::HGList(std::string line):
line(line) {
    
}

std::string hg::HGList::getLine() {
    return line;
}

void hg::HGList::setLine(std::string s) {
    line = s;
}

hg::ListTypes hg::HGList::getType() {
    if(line[0] == 'i') {
        return hg::INT;
    }
    else if(line[0] == 's') {
        return hg::STRING;
    }
    else if(line[0] == 'd') {
        return hg::DOUBLE;
    }
    else if(line[0] == 'b') {
        return hg::BOOL;
    }
    else if(line[0] == '/' && line[1] == '/') {
        return hg::COMMENT;
    }
    else {
        return hg::ERROR;
    }
}

std::string hg::HGList::getVarName() {
    std::string name;
    int start, end;
    
    start = (int)line.find("[") + 1;
    end = (int)line.find("]");
    
    name = hg::substr(line, start, end);
    
    return name;
}

int hg::HGList::getIntValue() {
    if(this->getType() == INT) {
        int value;
        int start, end;
        
        start = (int)line.find("{") + 1;
        end = (int)line.find("}");
        
        value = stoi(hg::substr(line, start, end));
        return value;
    }
    else {
        std::cout << this->getVarName() << " has not the correct type!" << std::endl;
        return NULL;
    }
}

double hg::HGList::getDoubleValue() {
    if(this->getType() == DOUBLE) {
        double value;
        int start, end;
        
        start = (int)line.find("{") + 1;
        end = (int)line.find("}");
        
        value = stod(hg::substr(line, start, end));
        return value;
    }
    else {
        std::cout << this->getVarName() << " has not the correct type!" << std::endl;
        return NULL;
    }
}

std::string hg::HGList::getStringValue() {
    if(this ->getType() == STRING) {
        std::string value;
        int start, end;
        
        start = (int)line.find("{") + 1;
        end = (int)line.find("}");
        
        value = hg::substr(line, start, end);
        return value;
    }
    else {
        std::cout << this->getVarName() << " has not the correct type!" << std::endl;
        return "";
    }
}

bool hg::HGList::getBoolValue() {
    if(this->getType() == BOOL) {
        int start, end;
        
        start = (int)line.find("{") + 1;
        end = (int)line.find("}");
        
        if(hg::substr(line, start, end) == "true" || hg::substr(line, start, end) == "1") {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        std::cout << this->getVarName() << " has not the correct type!" << std::endl;
        return NULL;
    }
}

void hg::HGList::setType(hg::ListTypes type) {
    switch (type) {
        case hg::INT:
            line = "i" + hg::substr(line, 1, (unsigned int)line.size());
            break;
            
        case hg::DOUBLE:
            line = "d" + hg::substr(line, 1, (unsigned int)line.size());
            break;
            
        case hg::STRING:
            line = "s" + hg::substr(line, 1, (unsigned int)line.size());
            break;
            
        case hg::BOOL:
            line = "b" + hg::substr(line, 1, (unsigned int)line.size());
            break;
            
        default:
            break;
    }
}

void hg::HGList::setVarName(std::string name) {
    line = hg::substr(line, 0, 2) + "[" + name + "]" + hg::substr(line, (unsigned int)line.find("{") - 1, (unsigned int)line.size() - 1);
}

void hg::HGList::setIntValue(int v) {
    line = hg::substr(line, 0, (unsigned int)line.find("{") + 1) + std::to_string(v) + "}";
}

void hg::HGList::setDoubleValue(double v) {
    line = hg::substr(line, 0, (unsigned int)line.find("{") + 1) + std::to_string(v) + "}";
}

void hg::HGList::setStringValue(std::string v) {
    line = hg::substr(line, 0, (unsigned int)line.find("{") + 1) + v + "}";
}

void hg::HGList::setBoolValue(bool v) {
    line = hg::substr(line, 0, (unsigned int)line.find("{") + 1) + std::to_string(v) + "}";
}


bool hg::lineValidForHGList(std::string line) {
    if(line[0] == 'i') {
        return true;
    }
    else if(line[0] == 's') {
        return true;
    }
    else if(line[0] == 'd') {
        return true;
    }
    else if(line[0] == 'b') {
        return true;
    }
    else if(line[0] == '/' && line[1] == '/') {
        return true;
    }
    else {
        return false;
    }
}

/*
std::vector<hg::HGList> hg::getHGListsFromFile(hg::File file) {
    std::vector<hg::HGList> lists;
    std::vector<std::string> strings = file.readFileLineByLine();
    
    for(int i = 0; i < strings.size(); i++) {
        if(strings[i].size() > 0) {
            if(hg::lineValidForHGList(strings[i])) {
                lists.push_back(hg::HGList(strings[i]));
            }
        }
    }
    
    return lists;
}*/

std::vector<hg::HGList> hg::getHGListsFromFileName(std::string fileName) {
    std::vector<hg::HGList> lists;
    std::ifstream in(fileName.c_str());
    
    if(!in) {
        std::cerr << "Cannot open the file : " << fileName << std::endl;
    }
    
    std::string str;
    while (std::getline(in, str)) {
        if(str.size() > 0) {
            if(hg::lineValidForHGList(str)) {
                lists.push_back(hg::HGList(str));
            }
        }
    }
    in.close();
    
    return lists;
}

int hg::getLocationFromName(std::vector<hg::HGList> *search, std::string varName) {
    for(int i = 0; i < search->size(); i++) {
        if((*search)[i].getVarName() == varName) {
            return i;
        }
    }
    return -1;
}

