/* 
 * File:   State.h
 * Author: florent
 *
 * Created on 25 novembre 2015, 12:32
 */

#ifndef STATE_H
#define	STATE_H

#include <vector>
#include <string>
#include "Interval.h"

class State {
public:
    State(std::string);
    State(const State& orig); /* Constructeur de recopie, on utilise la reference a un autre etat */
    virtual ~State();
    std::string getId();
    void setId(int n);
    std::vector<State*> getSucc();
    std::vector<Interval*> getProb();
    void addSucc(State &su, Interval &in);
    void printSucc();
    void printId();
private:
    std::string sid;
    std::vector<State*> succ;
    std::vector<Interval*> prob;
};

#endif	/* STATE_H */

