/* 
 * File:   Interval.h
 * Author: florent
 *
 * Created on 25 novembre 2015, 13:48
 */

#ifndef INTERVAL_H
#define	INTERVAL_H

#include <vector>
#include <string>

class Interval {
public:
    Interval(std::string f, std::string s);
    Interval(const Interval& orig);
    virtual ~Interval();
    void setS(std::string str);
    void setF(std::string str);
    std::string getS();
    std::string getF();
    double getInf();
    double getSup();
    void printIntval();
private:
    std::string f;
    std::string s;
};

#endif	/* INTERVAL_H */

