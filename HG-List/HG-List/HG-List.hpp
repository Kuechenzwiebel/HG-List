//
//  HG-List.hpp
//  HG-List
//
//  Created by Tobias Pflüger on 13.02.19.
//  Copyright © 2019 Tobias Pflüger. All rights reserved.
//

#ifndef HG_List_hpp
#define HG_List_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace hg {
    enum ListTypes {
        INT = 1,
        STRING = 2,
        DOUBLE = 3,
        BOOL = 4,
        ERROR = -1
    };
    
    class HGList {
    public:
        HGList(std::string line);
        
        std::string getLine();
        void setLine(std::string s);
        
        hg::ListTypes getType();
        std::string getVarName();
        
        int getIntValue();
        double getDoubleValue();
        std::string getStringValue();
        bool getBoolValue();
        
        
        void setType(hg::ListTypes type);
        void setVarName(std::string name);
        
        void setIntValue(int v);
        void setDoubleValue(double v);
        void setStringValue(std::string v);
        void setBoolValue(bool v);
        
    private:
        std::string line;
    };
    
    std::vector<HGList> getHGListsFromFileName(std::string fileName);
    
    int getLocationFromName(std::vector<hg::HGList> search, std::string varName);
}

#endif /* HG_List_hpp */
