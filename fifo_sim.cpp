//Nicholas Schroeder
// COE 1550 - Project 3 - 11.11.2019 

#include <cstdlib>
#include <iostream>
#include "fifo_sim.h"

using namespace std;

namespace COE_1550_VMSIM {
	//Overwritten remove method for Page Table
	int fifo_sim::remove(int opt){
		//return failure if PT empty
		if(page_table::size == 0)
			return FAILURE; 

		//FIFO so just remove the head and return its dirty bit

		int was_dirty = this->head->dirty;

		//only one element in PT
		if(this->size == 1){
			this->head = NULL;
			this->tail = NULL;
		}
		else
			this->head = this->head->next;

		this->size--;

		return was_dirty;
	}
}
