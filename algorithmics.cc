#include <string>
#include <vector>
#include "Pimc.h"
#include "State.h"

using namespace std; 

bool localConsistency(State& s, Pimc& pimc, vector<State*> succSubset) {
    bool res = true;
    
    // Verify that the successor subset is indeed composed of successor of s
    
    // For each of those successors, check the conditions
    
    //
    
    return res;
}

bool localConsistencyStr(string stateName, Pimc& pimc, vector<State*> succSubset) {
    bool res = localConsistency(*(pimc.getState(stateName)), pimc, succSubset);
    return res;
}

