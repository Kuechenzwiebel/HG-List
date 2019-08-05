//
//  main.cpp
//  HG-List
//
//  Created by Tobias Pflüger on 30.01.19.
//  Copyright © 2019 Tobias Pflüger. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

#include "HG-List.hpp"
#include "file.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    vector<hg::HGList> lists = hg::getHGListsFromFileName("list.hg");
    
    for(int i = 0; i < lists.size(); i++) {
        cout << lists[i].getVarName() << " = ";
        
        switch (lists[i].getType()) {
            case hg::INT:
                cout << lists[i].getIntValue() << endl;
                break;
                
            case hg::DOUBLE:
                cout << lists[i].getDoubleValue() << endl;
                break;
                
            case hg::STRING:
                cout << lists[i].getStringValue() << endl;
                break;
                
            case hg::BOOL:
                cout << lists[i].getBoolValue() << endl;
                break;
                
            case hg::COMMENT:
                cout << "Comment" << endl;
                break;
                
            default:
                cout << "Error" << endl;
                break;
        }
    }
    
    hg::File f("list.hg");
    
    cout << endl << endl;
    
    vector<string> lines;
    lines = f.readFileLineByLine();
    
    cout << hg::transformLinesToString(&lines) << endl;
    
    return 0;
}
