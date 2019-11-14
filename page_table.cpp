//Nicholas Schroeder
// COE 1550 - Project 3 - 11.11.2019

#include <cstdlib>
#include "page_table.h"
#include <iostream>

using namespace std;

namespace COE_1550_VMSIM {
	//Default constructor
	page_table::page_table(){
		page_table(0,0);
	}

	//Single parameter constructor
	page_table::page_table(int numframes){
		page_table(numframes,0);
	}

	//Main constructor
	page_table::page_table(int numframes, int refresh){
		//Initialize empty page_table

		this->numframes = numframes;
		this->refresh = refresh;

		this->size = 0;
		this->head = NULL;
		this->tail = NULL;
	}

	page_table::~page_table(){
		//free used memory

		delete this->head;
		delete this->tail;
	}

	//Insert PTE function
	int page_table::insert(int page_number){
		//Return -1 if the PT is full
		if(this->size == this->numframes)
			return FAILURE;

		//Create a new node with default parameters
		struct node* new_node = new node;

		new_node->page_number = page_number;
		new_node->reference = 0;
		new_node->dirty = 0;
		new_node->age_counter = 128;
		new_node->full_addr = 0;
		new_node->next = NULL;

		if(this->size == 0){
			//PT is empty
			this->head = new_node;
			this->tail = new_node;
		}
		else{
			//PT is not empty
			this->tail->next = new_node;
			this->tail = new_node;
		}

		this->size++;	//increment and return size of PT

		return this->size;
	}

	//Contains function, returns true if page_number is in PT else returns false
	bool page_table::contains(int page_number){
		//return false if PT is empty
		if(this->size == 0)
			return false;

		struct node *current = this->head;

		//iterate through PT and return true if page_number is found
		while(current != NULL){
			if(current->page_number == page_number)
				return true;
			current = current->next;
		}

		//page_number was not found, return false
		return false;
	}

	//Set dirty bit function... set's page_number's dirty bit to 1
	int page_table::set_dirty(int page_number){
		struct node* current = this->head;

		//iterate through PT and find page_number and set dirty to 1
		while(current != NULL){
			if(current->page_number == page_number){
				current->dirty = 1;

				return 0;
			}

			current = current->next;
		}

		//page_number was not found, return FAILURE (-1)
		return FAILURE;	
	}

	//Virtual Remove method... MUST be overwritten by derived classes
	int page_table::remove(int opt){
		return FAILURE;
	}
}

