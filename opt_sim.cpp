//Nicholas Schroeder
// COE 1550 - Project 3 - 11.11.2019

#include <cstdlib>
#include <string.h>
#include <fstream>
#include <iostream>
#include "opt_sim.h"

using namespace std;

namespace COE_1550_VMSIM {
	//Function to get the initial trace and load values from trace file
	int opt_sim::get_init_trace(string filename){
		ifstream infile;
		infile.open(filename.c_str());

		int count = 0;

		char t;
		unsigned int a, c;

		//get the number of lines (memory accesses)
		while(infile >> t >> hex >> a >> dec >> c)
			count++;

		this->total_memaccesses = count;

		//allocate memory for trace file storage variables
		this->types = (char*)malloc(count*sizeof(char));
		this->cycles = (unsigned int*)malloc(count*sizeof(unsigned int));
		this->addrs = (unsigned int*)malloc(count*sizeof(unsigned int));

		//reset infile to start of the file
		infile.clear();
		infile.seekg(0,ios::beg);

		int iter = 0;

		//iterate through each line of trace file and store contents appropriately
		while(infile >> t >> hex >> a >> dec >> c){
			this->types[iter] = t;
			this->addrs[iter] = a/4096;
			this->cycles[iter] = c;

			iter++;
		}

		//close file
		infile.close();

		return 0;
	}

	//overwritten remove method for Page Table
	int opt_sim::remove(int mem_access){
		//return failure if empty
		if(this->size == 0)
			return FAILURE;

		//declare array to be used to determined the victim
		int places[this->size+1];

		//initialize places[] to all 0s
		for(int k=0;k<this->size;k++)
			places[k] = 0;

		int i=0;

		struct node* curr = this->head;

		//iterate through PT
		while(curr != NULL){
			int curr_place = 0;						//set current_place = 0
			unsigned int addr = curr->page_number;	//set addr to current PTE's addr

			bool set = false;

			//iterate through remaining memory accesses
			for(int j=mem_access;j<this->total_memaccesses;j++){
				//if addr is being used in the future, store when in places
				if(addr == this->addrs[j]){
					places[i] = curr_place;
					set = true;

					break;
				}

				curr_place++;
			}

			//if not set then addr is not used and set places to max
			if(!set)
				places[i] = this->total_memaccesses;

			i++;
			curr = curr->next;
		}

		int max = places[0];
		int max_index = 0;
		bool is_head = false;
		bool is_tail = false;

		curr = this->head;
		i=0;

		//look for max place to remove a victim

		while(curr != NULL){
			if(places[i] >= max){
				max = places[i];
				max_index = i;

				is_head = curr == this->head;
				is_tail = curr == this->tail;
			}

			i++;
			curr = curr->next;
		}

		int was_dirty = -1;

		if(is_head && is_tail){
			was_dirty = this->head->dirty;

			this->head = NULL;
			this->tail = NULL;

			this->size = 0;

			return was_dirty;
		}

		if(is_head){
			was_dirty = this->head->dirty;

			this->head = this->head->next;
			this->size--;

			return was_dirty;
		}

		curr = this->head;
		i=0;

		while(curr != NULL){
			if(is_tail && i==max_index - 1){
				was_dirty = this->tail->dirty;

				this->tail = curr;
				this->tail->next = NULL;

				this->size--;

				return was_dirty;
			}

			if(i == max_index - 1){
				was_dirty = curr->next->dirty;
				curr->next = curr->next->next;

				this->size--;

				return was_dirty;
			}

			i++;
			curr = curr->next;
		}

		return FAILURE;
	}
}
