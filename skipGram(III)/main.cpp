//
//  main.cpp
//  skipGram(II)
//
//  Created by Eric Cheng on 10/17/17.
//  Copyright © 2017 Eric Cheng. All rights reserveD->
//

#include <iostream>
#include <cstdio>
#include "Dictionary.hpp"
#include "Matrix.hpp"


int const FeatureSize = 3;
int const window = 3; // only the word after


char *fileOpen = (char*)malloc(sizeof(char)*200);
vector<string> strData;
void scanInput(dictionary *D){
    strcpy(fileOpen, "/Users/eric/Desktop/input3.txt");
    FILE *fp;
    fp = fopen(fileOpen, "r");
    while (true) {
        char *s = (char*)malloc(sizeof(char)*100);
        if(fscanf(fp, "%s", s)==EOF) break;
        D->addWord(s);
        strData.push_back(s);
    }
    fclose(fp);
    D->updateID();
}

int main(int argc, const char * argv[]) {
    double alpha = 0.003125;
    dictionary *D = new dictionary();
    scanInput(D);
    matrix onehot(1, D->size());
    matrix W(D->size(), FeatureSize);
    matrix h(1, FeatureSize);
    matrix WP(FeatureSize, D->size());
    matrix x (1, D->size());
    matrix u (1, D->size());
    vector<matrix> t; // each t need initiation
    matrix sum (1, D->size());
    
    W.randomSet();
    WP.randomSet();
    
    matrix xderi(1, D->size());
    matrix hderi(1, FeatureSize);
    matrix wpderi(FeatureSize, D->size());
    matrix wderi (D->size(), FeatureSize);
    coord tmp(0, 0);
    coord tmp1(0, 0);
    coord tmp2(0, 0);
    
    t.resize(2*window);
    for (int m=-window; m<window; m++) {
        if (m==0) continue;
        t[m+window].initialize(1, D->size());
    }
    
    for (int rep = 0; rep<500; rep++) {
        for (int i=window; i<strData.size()-window; i++) {
            //initialize
            onehot.clear();
            //t.clear();
            tmp.set(0, D->getID(strData[i+1]));

            for (int m=-window; m<window; m++) {
                if (m==0) continue;
                tmp.set(0, D->getID(strData[i+m]));
                t[m+window].clear();
                t[m+window].setVal(tmp, 1);
            }
            
            //feedForward
            tmp.set(0, D->getID(strData[i]));
            onehot.setVal(tmp, 1);
            h = onehot*W;
            x = h*WP;
            u = x.softMax();
            
            //backProp
            sum.clear();
            for (int m=-window; m<window; m++) {
                if (m == 0) continue;
                sum = sum + t[m+window];
            }
            xderi = u*2*window - sum;
            printf("\n\n");
            hderi = xderi * WP.trans();
            //WPderi
            for (int m=0; m<FeatureSize; m++) {
                for (int n=0; n<D->size(); n++) {
                    tmp.set(m, n);
                    tmp1.set(0, n);
                    tmp2.set(0, m);
                    wpderi.setVal(tmp, xderi.getVal(tmp1)*h.getVal(tmp2));
                }
            }
            //Wderic
            wderi.clear();
            for (int m=0; m<FeatureSize; m++) {
                tmp.set(D->getID(strData[i]), m);
                tmp1.set(0, m);
                wderi.setVal(tmp, hderi.getVal(tmp1));
            }
            
            //learn
            W = W - wderi*alpha;
            WP = WP - wpderi*alpha;
        }
    }
    
    W.print();
    onehot.clear();
    
    
    //feedForward
    tmp.set(0, D->getID(strData[2]));
    onehot.setVal(tmp, 1);
    h = onehot*W;
    x = h*WP;
    u = x.softMax();
    u.print();
    
    for (int i=0; i<strData.size(); i++) {
        printf("%s %d\n", strData[i].c_str(), D->getID(strData[i]));
    }

    return 0;
}





