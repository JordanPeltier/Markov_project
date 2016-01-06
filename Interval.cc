/* 
 * File:   Interval.cc
 * Author: florent
 * 
 * Created on 25 novembre 2015, 13:48
 */

#include <iostream>
#include <string>
#include "Interval.h"

using namespace std;

Interval::Interval(string f, string s) {
    this->f = f;
    this->s = s;
}

Interval::Interval(const Interval& orig) {
}

Interval::~Interval() {
}

void Interval::setF(string str) {
    this->f = str;
}
void Interval::setS(string str) {
    this->s = str;
}

string Interval::getF() {
    return this->f;
}
string Interval::getS() {
    return this->s;
}

double Interval::getInf() {
    return std::atof(this->f.c_str());
}

double Interval::getSup() {
    return std::atof(this->s.c_str());
}

void Interval::printIntval() {
    cout << "[";
    cout <<  f;
    cout << ";";
    cout <<  s;
    cout << "]";
}
