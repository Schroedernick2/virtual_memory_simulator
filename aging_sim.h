//Nicholas Schroeder
// COE 1550 - Project 3 - 11.11.2019 

#ifndef AGING_SIM_H
#define AGING_SIM_H

#include "page_table.h"

namespace COE_1550_VMSIM {
	//Aging_sim class derived from page_table
	class aging_sim : public page_table {

		using page_table::page_table;

		public:
			//use the page_table() constructor
			explicit aging_sim() : page_table(0,0){}
			//use the page_table(int,int) constructor
			explicit aging_sim(int numframes, int refresh) : page_table(numframes, refresh){}

			//overwrite remove method from page_table parent class
			virtual int remove(int opt=0);
			//Function to set the reference bit for a given page_number
			int set_ref(int page_number);
			//Function to set the full address for a page_number when it is added
			int set_full_addr(int page_number, int full_addr);
			//Function to refresh the counters
			int refresh_counters();
	};
}

#endif
