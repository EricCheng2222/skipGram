//
//  Matrix.cpp
//  skipGram(II)
//
//  Created by Eric Cheng on 10/19/17.
//  Copyright © 2017 Eric Cheng. All rights reserved.
//

#include "Matrix.hpp"
#include <cmath>

int i, j;

void matrix::randomSet(){
    for ( i=0; i<*col; i++) {
        for ( j=0; j<*row; j++) {
            m[i][j] = ((double)random()/(double)RAND_MAX);
        }
    }
}

void matrix::clear(){
    for ( i=0; i<*col; i++) {
        for ( j=0; j<*row; j++) {
            m[i][j] = 0.0;
        }
    }
}


void matrix::setVal(coord &c, double d){
    m[c.x][c.y] = d;
}

matrix matrix::softMax(){
    double D = 0;
    matrix *a = new matrix(1, *this->row);
    for ( i=0; i<*row; i++) {
        D = D + exp(m[0][i]);
    }
    
    for ( i=0; i<*row; i++) {
        a->m[0][i] = exp(m[0][i])/D;
    }
    use.push_back(a);
    return *a;
}


matrix matrix::operator*(const double &d){
    matrix *ret = new matrix(*col, *row);
    for ( i=0; i<*col; i++) {
        for ( j=0; j<*row; j++) {
            ret->m[i][j] = d*m[i][j];
        }
    }
    use.push_back(ret);
    return *ret;
}

matrix matrix::operator+(const matrix &a){
    matrix *ret = new matrix(*col, *row);
    for ( i=0; i<*col; i++) {
        for ( j=0; j<*row; j++) {
            ret->m[i][j] = a.m[i][j] + m[i][j];
        }
    }
    use.push_back(ret);
    return *ret;
}

matrix matrix::operator-(const matrix &a){
    matrix *ret = new matrix(*col, *row);
    for ( i=0; i<*col; i++) {
        for ( j=0; j<*row; j++) {
            ret->m[i][j] = m[i][j] - a.m[i][j];
        }
    }
    use.push_back(ret);
    return *ret;
}

matrix matrix::trans(){
    matrix *ret = new matrix(*row, *col);
    for ( i=0; i<*col; i++) {
        for ( j=0; j<*row; j++) {
            ret->m[j][i] = m[i][j];
        }
    }
    use.push_back(ret);
    return *ret;
}

void matrix::print(){
    for ( i=0; i<*col; i++) {
        for ( j=0; j<*row; j++) {
            printf("%lf ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

matrix matrix::operator*(const matrix &a){
    matrix *ret = new matrix(*col, *a.row);
    for ( i=0; i<*col; i++) {
        for ( j=0; j<*a.row; j++) {
            double sum = 0;
            for (int k=0; k<*row; k++) {
                sum = sum + m[i][k]*a.m[k][j];
            }
            ret->m[i][j] = sum;
        }
    }
    use.push_back(ret);
    return *ret;
}

void matrix::operator=(const matrix &a){
    for (int i=0; i<*col; i++) {
        for (int j=0; j<*row; j++) {
            this->m[i][j] = a.m[i][j];
        }
    }
}

double matrix::getVal(coord &c){
    return m[c.x][c.y];
}

void matrix::initialize(int a, int b){
    col = (int*)malloc(sizeof(int));
    row = (int*)malloc(sizeof(int));
    *col = a; *row = b;
    m = (double**)malloc(sizeof(double*)*a);
    for (int i=0; i<a; i++) {
        m[i] = (double*)malloc(sizeof(double)*b);
    }
}

