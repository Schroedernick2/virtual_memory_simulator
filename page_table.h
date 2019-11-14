//Nicholas Schroeder
// COE 1550 - Project 3 - 11.11.2019 

#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include "node.h"

namespace COE_1550_VMSIM {
	//Page_table class used for algorithm simulations
	//Linked List
	class page_table {
		public:
			//Explicit constructors for use in derived classes

			//Default constructor
			explicit page_table();
			//Constructor with numframes parameter
			explicit page_table(int numframes);
			//Constructor with numframes and refresh parameter
			explicit page_table(int numframes, int refresh);

			//Destructor
			~page_table();

			//Function to insert a page number into the Page Table
			int insert(int page_number);
			//Function checks if a page number is in the Page Table
			bool contains(int page_number);
			//Function to set a PTE's dirty bit to 1 for a page_number
			int set_dirty(int page_number);

			//Remove method that MUST be overwritten in derived classes
			virtual int remove(int opt=0);

		protected:
			int numframes;		//number of frames
			int refresh;		//refresh period

			struct node* head;	//head of Page Table
			struct node* tail;	//tail of Page Table
			int size;			//size of Page Table
	};
}

#endif
