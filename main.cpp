//Nicholas Schroeder
// COE 1550 - Project 3 - 11.11.2019 

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "simulator.h"

using namespace std;
using namespace COE_1550_VMSIM;

//Report illegal args
void usage_error(){
	cout << "Usage: ./vmsim –n <numframes> -a <opt|fifo|aging> [-r <refresh>] <tracefile>" << endl;
}

//main
int main(int argc, char** argv){
	int numframes = 0;
	int algorithm = 0;
	int refresh = 0;
	string tracefile = "";

	bool n_set = false;
	bool a_set = false;
	bool tf_set = false;

	//parse program arguments
	for(int i=0;i<argc;i++){
		if(strcmp(argv[i],"-n") == 0){
			if(i+1 < argc){
				numframes = atoi(argv[i+1]);
				i++;
				n_set = true;
			}
			else{
				usage_error();

				return EXIT_FAILURE;
			}
		}
		else if(strcmp(argv[i],"-a") == 0){
			if(i+1 < argc){
				string a = argv[i+1];

				if(a == "opt")
					algorithm = OPT;
				else if(a == "fifo")
					algorithm = FIFO;
				else if(a == "aging")
					algorithm = AGING;
				else{
					usage_error();

					return EXIT_FAILURE;
				}

				i++;
				a_set = true;
			}
			else{
				usage_error();

				return EXIT_FAILURE;
			}
		}
		else if(strcmp(argv[i],"-r") == 0){
			if(i+1 < argc){
				refresh = atoi(argv[i+1]);
				i++;
			}
			else{
				usage_error();

				return EXIT_FAILURE;
			}
		}
		else if(i == argc-1){
			tf_set = true;
			tracefile = argv[i];

			break;
		}
	}

	//determine usage_error()
	if(!n_set || !a_set || !tf_set){
		usage_error();

		return EXIT_FAILURE;
	}

	//create new instance of the simulator class
	simulator* sim = new simulator(numframes,algorithm,refresh,tracefile);

	//Make sure trace file exists
	bool valid_file = sim->verify_file();

	if(!valid_file){
		cout << "Invalid tracefile." << endl;
		cout << "File \'"<< tracefile <<"\' not found." << endl;

		return EXIT_FAILURE;
	}

	//run the trace file
	sim->run_trace();
	//show stats from trace file run
	sim->show_report();

	return EXIT_SUCCESS;
}
