/* 
 * File:   Pimc.h
 * Author: florent
 *
 * Created on 25 novembre 2015, 16:43
 */

#ifndef PIMC_H
#define	PIMC_H

#include <vector>
#include <string>
#include "State.h"

class Pimc {
public:
    Pimc();
    Pimc(const Pimc& orig);
    virtual ~Pimc();
    std::vector<State*> getStates();
    int  getNbStates();
    void setNbStates(int i); 
    //int  getNewId();
    void addState(State& s);
    //void createState();
    State* getState(std::string stateName);
    bool stateExists(State *s);
    void printStates();
private:
    std::vector<State*> states;
    int nbStates;
};

#endif	/* PIMC_H */

