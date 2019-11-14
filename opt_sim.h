//Nicholas Schroeder
// COE 1550 - Project 3 - 11.11.2019

#ifndef OPT_SIM_H
#define OPT_SIM_H

#include <string>
#include "page_table.h"

namespace COE_1550_VMSIM {
	//Opt_sim class derived from page_table
	class opt_sim : public page_table {

		using page_table::page_table;

		public:
			//use the page_table constructor and the opt_sim(int) constructor
			opt_sim() : page_table(0,0){
				opt_sim(0);
			}

			//use the page_table constructor and initialize derived class variables
			opt_sim(int numframes) : page_table(numframes,0){
				this->total_memaccesses = 0;

				this->types = NULL;		//array of types from trace file
				this->cycles = NULL;	//array of cycle numbers from trace file
				this->addrs = NULL;		//array of addresses from trace file
			}

			//Destructor
			~opt_sim(){
				//free class arrays
				free(this->types);
				free(this->cycles);
				free(this->addrs);
			}

			//overwrite remove method from page_table parent class
			virtual int remove(int mem_access);
			//Function to initially traverse trace file and load info into class arrays
			int get_init_trace(std::string filename);

		private:
			int total_memaccesses;		//number of total memory accesses for a trace file
			char* types;				//array of types
			unsigned int* addrs;		//array of addresses
			unsigned int* cycles;		//array of cycle count numbers
	};
}

#endif
