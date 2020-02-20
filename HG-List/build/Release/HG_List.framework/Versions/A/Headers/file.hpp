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
        File(const File &other);
        ~File();
        
        std::vector<std::string> readFileLineByLine();
        std::string readFile();
        
        void writeFile(const std::string &content);
        
    private:
        std::string fileName;
        std::fstream fileStream;
    };
    
    std::string substr(const std::string &string, unsigned int start, unsigned int end);
    bool find(const std::string &string, const std::string &search);
    
    std::string transformLinesToString(std::vector<std::string> *lines);
}

#endif /* File_hpp */
