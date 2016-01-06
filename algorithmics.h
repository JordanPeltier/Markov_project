/* 
 * File:   algorithmics.h
 * Author: florent
 *
 * Created on 17 décembre 2015, 15:52
 */

#ifndef ALGORITHMICS_H
#define	ALGORITHMICS_H

#include <string>
#include <vector>
#include "State.h"
#include "Pimc.h"


bool localConsistencyStr(std::string stateName, Pimc& pimc, vector<State*> succSubset);
bool localConsistency(State& s, Pimc& pimc, vector<State*> succSubset);


#endif	/* ALGORITHMICS_H */

