//Nicholas Schroeder
// COE 1550 - Project 3 - 11.11.2019 

#ifndef FIFO_SIM_H
#define FIFO_SIM_H

#include "page_table.h"

namespace COE_1550_VMSIM {
	//Fifo_sim class derived from page_table
	class fifo_sim : public page_table {

		using page_table::page_table;

		public:
			//use the page_table() constructor
			explicit fifo_sim() : page_table(0,0) {}
			//use the page_table(int,int) constructor
			explicit fifo_sim(int numframes) : page_table(numframes,0){}

			//overwrite remove method from page_table parent class
			virtual int remove(int opt=0);
	};
}

#endif
