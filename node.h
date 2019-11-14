//Nicholas Schroeder
// COE 1550 - Project 3 - 11.11.2019 

#ifndef NODE_H
#define NODE_H

#include <stdint.h>

#define FAILURE -1

#define PAGE_SIZE	4096
#define PT_SIZE		1048576
#define PTE_SIZE	sizeof(struct pte_32*)

namespace COE_1550_VMSIM {
	//node struct declared here... used for page_table entry representations
	struct node {
		int page_number;	//page_number
		int dirty;			//dirty bit 0 or 1
		int age_counter;	//age counter 0-255 
		int reference;		//reference bit 0 or 1

		int full_addr;		//Full address including OFFSET

		node* next;			//Pointer to next node 
	};
}

#endif
