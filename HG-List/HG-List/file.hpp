//
//  File.hpp
//  HG-List
//
//  Created by Tobias Pflüger on 11.05.19.
//  Copyright © 2019 Tobias Pflüger. All rights reserved.
//

#ifndef File_hpp
#define File_hpp

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

namespace hg {
    class File {
    public:
        File(std::string fileName);
        
        ~File();
        
        std::vector <std::string> readFileLineByLine();
        std::string readFile();
        
    private:
        std::string fileName;
        std::ifstream file;
    };
}

#endif /* File_hpp */
