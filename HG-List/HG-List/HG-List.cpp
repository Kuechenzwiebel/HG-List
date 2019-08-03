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
    if(line.substr(0, 1) == "i") {
        return hg::INT;
    }
    else if(line.substr(0, 1) == "s") {
        return hg::STRING;
    }
    else if(line.substr(0, 1) == "d") {
        return hg::DOUBLE;
    }
    else if(line.substr(0, 1) == "b") {
        return hg::BOOL;
    }
    else {
        return hg::ERROR;
    }
}

std::string hg::HGList::getVarName() {
    std::string name;
    int start, end;
    
    start = (int)line.find("[") + 1;
    end = (int)line.find("]") - 3;
    
    name = line.substr(start, end);
    
    return name;
}

int hg::HGList::getIntValue() {
    if(this->getType() == INT) {
        int value;
        int start, end;
        
        start = (int)line.find("{") + 1;
        end = (int)line.find("}") - 3;
        
        value = stoi(line.substr(start, end));
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
        end = (int)line.find("}") - 8;
        
        value = stod(line.substr(start, end));
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
        end = (int)line.find("}") - 10;
        
        value = line.substr(start, end);
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
        end = (int)line.find("}") - 7;
        
        if(line.substr(start, end) == "true" || line.substr(start, end) == "1") {
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
            line = "i" + line.substr(1, line.size() - 1);
            break;
            
        case hg::DOUBLE:
            line = "d" + line.substr(1, line.size() - 1);
            break;
            
        case hg::STRING:
            line = "s" + line.substr(1, line.size() - 1);
            break;
            
        case hg::BOOL:
            line = "b" + line.substr(1, line.size() - 1);
            break;
            
        default:
            break;
    }
}

void hg::HGList::setVarName(std::string name) {
    line = line.substr(0, 2) + "[" + name + "]" + line.substr(line.find("{") - 1, line.size() - 1);
}

void hg::HGList::setIntValue(int v) {
    line = line.substr(0, line.find("{") + 1) + std::to_string(v) + "}";
}

void hg::HGList::setDoubleValue(double v) {
    line = line.substr(0, line.find("{") + 1) + std::to_string(v) + "}";
}

void hg::HGList::setStringValue(std::string v) {
    line = line.substr(0, line.find("{") + 1) + v + "}";
}

void hg::HGList::setBoolValue(bool v) {
    line = line.substr(0, line.find("{") + 1) + std::to_string(v) + "}";
}



std::vector<hg::HGList> hg::getHGListsFromFileName(std::string fileName) {
    std::vector<hg::HGList> lists;
    std::ifstream in(fileName.c_str());
    
    if(!in) {
        std::cerr << "Cannot open the file : " << fileName << std::endl;
    }
    
    
    std::string str;
    while (std::getline(in, str)) {
        if(str.size() > 0) {
            lists.push_back(hg::HGList(str));
            if(lists[lists.size() -1].getType() == hg::ERROR) {
                lists.pop_back();
            }
        }
    }
    in.close();
    
    return lists;
}

int hg::getLocationFromName(std::vector<hg::HGList> search, std::string varName) {
    for(int i = 0; i < search.size(); i++) {
        if(search[i].getVarName() == varName) {
            return i;
        }
    }
    return -1;
}
