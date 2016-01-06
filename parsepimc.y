%{
#include <cstdio>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include "Pimc.h"
//#include <ppl.hh>

#define MAXSTATES 10000
    
    
using namespace std;
//using namespace Parma_Polyhedra_Library::IO_Operators;


typedef std::unordered_map< std::string, std::unordered_map< std::string, std::vector< std::string > > > state_map;
typedef std::unordered_map< std::string, std::vector< std::string > > succ_map;
typedef state_map::iterator it_state;
typedef succ_map::iterator it_succ;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

void yyerror(state_map &dataMap, const char *s);
int yyparse(state_map &dataMap);
%}

%parse-param{std::unordered_map< std::string, std::unordered_map< std::string, std::vector< std::string > > > &dataMap}

// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  But tokens could be of any
// arbitrary data type!  So we deal with that in Bison by defining a C union
// holding each of the types of tokens that Flex could return, and have Bison
// use that union instead of "int" for the definition of "yystype":
%union {
	int ival;
	float fval;
	char *sval;
}

// define the constant-string tokens:
%token PIMC NSTATE WITH ARROW
%token END

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING

%%

// the first rule defined is the highest-level rule, which in our
// case is just the concept of a whole "snazzle file":

end_parsing:
	header body_section footer { cout << "Done with the pIMC file!" << endl; }
	;
header:
	PIMC { cout << "pIMC file version " << endl;}
	;
body_section:
	body_lines
	;
body_lines:
	body_line body_lines
	| body_line
	;
body_line: // We then create for every State its list of successors (succ) with probabilities (prob) contained in Interval
	STRING ARROW STRING WITH STRING STRING { 
                                std::string stateName = $1;
                                std::string succName = $3;
              
                                std::string inf = $5;
                                std::string sup = $6;
                                
                                // borne inf/sup
                                std::vector< std::string > vint;
                                vint.push_back(inf);
                                vint.push_back(sup);

                                // succ
                                succ_map msucc;

                                // state
                                it_state stateIt;
                                stateIt = dataMap.find(stateName);
                                
                                // IF a state had this name in the unordered_map
                                // it means it already has some successors
                                // so we store the succ map in msucc
                                // ELSE we can start from msucc being null
                                if(stateIt != dataMap.end()) {
                                   msucc = dataMap[stateName];    
                                }
                                
                                msucc[succName] = vint; // in all cases, we append the new successor vector to the succ map
                                dataMap[stateName] = msucc; // we then append the new successors map for this state
                            }
	;
footer:
	END
	;

%%

int main(int, char**) {
        typedef std::unordered_map< std::string, std::unordered_map< std::string, std::vector<std::string> > >::iterator it_state;
        typedef std::unordered_map< std::string, std::vector< std::string > >::iterator it_succ;
        
        state_map dataMap;
       
	// open the in file:
	FILE *filein = fopen("in.pimc", "r");
	// verify it exists:
	if (!filein) {
		cout << "I can't open in.pimc!" << endl;
		return -1;
	}
	// set flex to read from the file
	yyin = filein;

	// parse input until the end
	do {
		yyparse(dataMap);
	} while (!feof(yyin));

        // Pimc init
        Pimc* myPimc;
        myPimc = new Pimc();

        // First, we create all the states (defined as states or as successors in the text file)
        for (it_state iterator = dataMap.begin(); iterator != dataMap.end(); iterator++) {
            myPimc->addState(*(new State(iterator->first)));

            for (it_succ iteratorBis = iterator->second.begin(); iteratorBis != iterator->second.end(); iteratorBis++) {
                myPimc->addState(*(new State(iteratorBis->first)));
            }
        }

        // Then we initialize all the successors of states defined in the text file
        for (it_state iterator = dataMap.begin(); iterator != dataMap.end(); iterator++) {

            for (it_succ iteratorBis = iterator->second.begin(); iteratorBis != iterator->second.end(); iteratorBis++) {
                if(myPimc->getState(iteratorBis->first) != NULL) {
                    Interval* inter = new Interval(iteratorBis->second.at(0),iteratorBis->second.at(1));
                    myPimc->getState(iterator->first)->addSucc(*(myPimc->getState(iteratorBis->first)), *inter);
                }
            }
        }
        myPimc->printStates();
        
        Interval it("0.2","0.9");

        /*Variable x(0);
        Variable y(1);
        
        Grid_Generator_System gs;
        gs.insert(grid_point(0*x+0*y));
        gs.insert(parameter(3*x+0*y));
        gs.insert(parameter(0*x+3*y));
        */
        
        
}

void yyerror(state_map &dataMap, const char *s) {
	cout << "EEK, parse error!  Message: " << s << endl;
	// might as well halt now:
	exit(-1);
}
