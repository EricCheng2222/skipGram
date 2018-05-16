//
//  Dictionary.cpp
//  skipGram(II)
//
//  Created by Eric Cheng on 10/19/17.
//  Copyright © 2017 Eric Cheng. All rights reserved.
//

#include "Dictionary.hpp"


void dictionary::addWord(string s){
    for (int i=0; i<s.size(); i++) s[i] = tolower(s[i]);
    
    letterCell *now = root;
    bool isExistChar = 0;
    bool isNew = 0;
    for (int i=0; i<s.size(); i++) {
        isExistChar = 0;
        for (int j=0; j<now->children.size(); j++) {
            if (s[i] == now->children[j]->c) {
                isExistChar = 1;
                now = now->children[j];
                break;
            }
        }
        if (isExistChar==0) {
            //create new node
            letterCell *tmp = new letterCell();
            tmp->c = s[i];
            now->children.push_back(tmp);
            now = tmp;
            isNew = 1;
        }
    }
    
    if (isNew || isExistChar) {
        now->isWord = 1;
        dictionarySize++;
    }
}

void dictionary::updateID(){
    IDcount = 0;
    traverse(root);
}

void dictionary::traverse(letterCell *now){
    if (now->isWord) {
        now->ID = IDcount;
        IDcount++;
        for (int i=0; i<now->children.size(); i++) {
            traverse(now->children[i]);
        }
        
    }
    else{
        for (int i=0; i<now->children.size(); i++) {
            traverse(now->children[i]);
        }
    }
}

int dictionary::size(){
    return IDcount;
}

int dictionary::getID(string &s){
    for (int i=0; i<s.size(); i++) {
        s[i] = tolower(s[i]);
    }
    letterCell *now = root;
    for (int i=0; i<s.size(); i++) {
        for (int j=0; j<now->children.size(); j++) {
            if (s[i]==now->children[j]->c) {
                now = now->children[j];
                break;
            }
        }
    }
    
    return now->ID;
}





