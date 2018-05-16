//
//  Dictionary.hpp
//  skipGram(II)
//
//  Created by Eric Cheng on 10/19/17.
//  Copyright © 2017 Eric Cheng. All rights reserved.
//

#ifndef Dictionary_hpp
#define Dictionary_hpp

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

struct letterCell {
    bool isWord = 0;
    int ID = -1;
    char c = 0;
    vector<letterCell*> children;
};


class dictionary {
private:
    int IDcount = 0;
    int dictionarySize = 0;
    letterCell *root = new letterCell();
    void traverse(letterCell *now);
public:
    void addWord(string s);
    void updateID();
    int size();
    int getID(string &s);
};



#endif /* Dictionary_hpp */

