//Nicholas Schroeder
// COE 1550 - Project 3 - 11.11.2019 

#include <cstdlib>
#include "aging_sim.h"

namespace COE_1550_VMSIM {
	//Overwritten Page Table remove function
	int aging_sim::remove(int opt){
		//If empty return false
		if(this->size == 0)
			return FAILURE;

		int min = this->head->age_counter;
		int curr_dirty = this->head->dirty;
		int curr_fa = this->head->full_addr;
		int min_index = 0;
		int i=0;

		struct node* curr = this->head;

		//iterate through page table to find victim
		while(curr != NULL){
			//check counters first
			if(curr->age_counter < min){
				//reset victim values
				min = curr->age_counter;
				min_index = i;
				curr_dirty = curr->dirty;
				curr_fa = curr->full_addr;
			}
			else if(curr->age_counter == min){
				//COUNTERS ARE EQUAL

				//break tie on dirty bit first
				if(curr_dirty == 1 && curr->dirty == 0){
					//reset victim values
					min = curr->age_counter;
					min_index = i;
					curr_dirty = curr->dirty;
					curr_fa = curr->full_addr;	
				}
				else if(curr_dirty == curr->dirty){
					//DIRTY BITS ARE EQUAL

					//break tie on full address
					if(curr->full_addr < curr_fa){
						//reset victim values
						min = curr->age_counter;
						min_index = i;
						curr_dirty = curr->dirty;
						curr_fa = curr->full_addr;
					}
				}
			}

			i++;
			curr = curr->next;
		}
		
		//REMOVE THE VICTIM AND RETURN ITS DIRTY BIT

		bool is_head = (min_index == 0);
		bool is_tail = (min_index == this->size-1);

		int was_dirty = -1;

		//Only one element in PT
		if(is_head && is_tail){
			was_dirty = this->head->dirty;

			this->head = NULL;
			this->tail = NULL;
			this->size = 0;

			return was_dirty;
		}

		//If victim is head then just set head to head->next and subtract from size
		if(is_head){
			was_dirty = this->head->dirty;

			this->head = this->head->next;
			this->size--;

			return was_dirty;
		}

		curr = this->head;
		i=0;

		//Victim is not head and there's more than one element in the PT
		while(curr != NULL){
			if(is_tail && i == min_index - 1){
				was_dirty = this->tail->dirty;

				this->tail = curr;
				this->tail->next = NULL;

				this->size--;

				return was_dirty;
			}

			if(i == min_index - 1){
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

	//Iterate through PT and set page_number's reference bit to 1
	int aging_sim::set_ref(int page_number){
		struct node* curr = this->head;

		while(curr != NULL){
			if(curr->page_number == page_number){
				curr->reference = 1;

				return 0;
			}

			curr = curr->next;
		}

		return FAILURE;
	}

	//Iterate through PT and set page_number's full address to full_addr
	int aging_sim::set_full_addr(int page_number, int full_addr){
		struct node* curr = this->head;

		while(curr != NULL){
			if(curr->page_number == page_number){
				curr->full_addr = full_addr;

				return 0;
			}

			curr = curr->next;
		}

		return FAILURE;
	}

	//Refresh each PTE's Age Counter
	int aging_sim::refresh_counters(){
		struct node* curr = this->head;

		//iterate through PT
		while(curr != NULL){
			//Shift counter to the right 1 bit
			curr->age_counter = curr->age_counter >> 1;

			//If reference == 1 then set MSB of counter to 1
			if(curr->reference == 1)
				curr->age_counter = curr->age_counter | 128;

			//reset reference for the counter
			curr->reference = 0;
			curr = curr->next;
		}

		return 0;
	}
}
