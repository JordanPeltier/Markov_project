/* 
 * File:   Pimc.cc
 * Author: florent
 * 
 * Created on 25 novembre 2015, 16:43
 */

#include <iostream>
#include <vector>
#include "Pimc.h"
#include "State.h"

using namespace std;

Pimc::Pimc() {
}

Pimc::Pimc(const Pimc& orig) {
}

Pimc::~Pimc() {
}

vector<State*> Pimc::getStates() {
    return this->states;
}

int Pimc::getNbStates(){
    return this->nbStates;
}

void Pimc::setNbStates(int i){
    this->nbStates = i;
}

// vérifie si un état existe déjà dans la pIMC (en le repérant par son identifiant State.sid)
bool Pimc::stateExists(State *s) {
    bool res = false;
    
    for(int i=0; i<this->states.size();i++) {
        if(this->states.at(i)->getId() == s->getId()) { // si le State en paramètre a le même is qu'un State déjà existant
            res = true; // on renvoie vrai
            break;
        }
    }
    
    return res;
}

State* Pimc::getState(std::string stateName) {
    State* s = NULL;
    
    for(int i=0; i<this->states.size();i++) {
        if(this->states.at(i)->getId() == stateName) { // si le State en paramètre a le même nom que le State de la boucle
            s = this->states.at(i); // on copie le pointeur vers ce state
            break;
        }
    }
    
    return s;
}

void Pimc::addState(State &s) {
    if(!this->stateExists(&s)) {
        this->states.push_back(&s);
        this->setNbStates(this->getNbStates() + 1);
    }
}

/*int Pimc::getNewId() {
    int max = 0;
    for(int i=0; i<this->states.size(); i++) {
        if(this->states.at(i)->getId()>max) {
            max=this->states.at(i)->getId();
        }
    }
    return max+1;
}*/

/*void Pimc::createState() {
    State s;
    s.setId(this->getNewId());
    this->addState(s);
}*/


void Pimc::printStates() {
    cout << endl;
    for(int i=0; i<this->states.size(); i++) {
        this->states.at(i)->printSucc();
    }
}

