/* 
 * File:   State.cc
 * Author: florent
 * 
 * Created on 25 novembre 2015, 12:32
 */

#include <iostream>
#include <vector>
#include <string>
#include "State.h"
#include "Interval.h"

using namespace std;

State::State(string sid) {
	this->sid = sid;
}

State::State(const State& orig) {
}

State::~State() {
}

string State::getId() {
    return this->sid;
}

void State::setId(int n) {
    this->sid = n;
}

vector<State*> State::getSucc() {
    return this->succ;
}

vector<Interval*> State::getProb() {
    return this->prob;
}

void State::addSucc(State &su, Interval &in) {
    this->succ.push_back(&su);
    this->prob.push_back(&in);
}

void State::printId() {
    cout << "State " << this->sid << endl;
}

void State::printSucc() {
    
    switch(this->succ.size()) {
        case 0 : cout << "State " << this->sid << " has no successor."; break;
        case 1 : cout << "Successor of state " << this->sid << " is "; break;
        default : cout << "Successors of state " << this->sid << " are ";
    }
    
    for(int i=0; i<this->succ.size(); i++) {
        cout << this->succ.at(i)->getId();
        this->prob.at(i)->printIntval();
        if(i == this->succ.size()-1) {
            cout << ".";
        }
        else {
            cout << " ; ";
        }
    }
    cout << endl;
    
}

