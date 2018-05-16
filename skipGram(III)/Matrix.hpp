//
//  Matrix.hpp
//  skipGram(II)
//
//  Created by Eric Cheng on 10/19/17.
//  Copyright © 2017 Eric Cheng. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>
#include <vector>
using namespace std;
struct coord {
    int x, y;
    coord(int a, int b){
        x = a; y = b;
    }
    void set(int a, int b){
        x = a; y = b;
    }
};

class matrix {
private:
    int *col, *row;
    vector<matrix*> use;
    double **m;
public:
    matrix(int a, int b){
        col = (int*)malloc(sizeof(int));
        row = (int*)malloc(sizeof(int));
        *col = a; *row = b;
        m = (double**)malloc(sizeof(double*)*a);
        for (int i=0; i<a; i++) {
            m[i] = (double*)malloc(sizeof(double)*b);
        }
    }
    matrix(){}
    //~matrix() = default;
    ~matrix(){
        for (int i=0; i<*col; i++) {
            free(m[i]);
        }
        free(m);
        free(col);
        free(row);
    }
    void randomSet();
    void clear();
    void setVal(coord&, double);
    double getVal(coord&);
    matrix operator* (const matrix &a);
    matrix operator+ (const matrix &a);
    matrix operator- (const matrix &a);
    matrix operator* (const double &d);
    void operator= (const matrix &a);
    matrix softMax();
    matrix trans();
    void print();
    void initialize(int, int);
};
#endif /* Matrix_hpp */

