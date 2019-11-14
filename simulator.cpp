//Nicholas Schroeder
// COE 1550 - Project 3 - 11.11.2019 

#include <iostream>
#include <fstream>
#include <sstream>
#include "simulator.h"

using namespace std;

namespace COE_1550_VMSIM{
	//Default constructor
	simulator::simulator(){
		simulator(0,0,0,"");
	}

	//Main constructor
	simulator::simulator(int numframes,int alg,int refresh,string filename){
		//Set specified variables
		this->numframes = numframes;
		this->alg = alg;
		this->refresh = refresh;
		this->filename = filename;

		//initialize class variables to default values
		this->mem_accesses = 0;
		this->page_faults = 0;
		this->writes_to_disk = 0;
		this->cycle_count = 1;
		this->refresh_count = 0;

		//Determine string representation of Algorithm
		switch(alg){
			case OPT:
				this->alg_s = "OPT";
				break;
			case FIFO:
				this->alg_s = "FIFO";
				break;
			case AGING:
				this->alg_s = "AGING";
				break;
			default:
				this->alg_s = "OTHER";
				break;
		}

		//Create new simulator class instances
		this->fifo = new fifo_sim(numframes);
		this->opt = new opt_sim(numframes);
		this->aging = new aging_sim(numframes,refresh);

		//initialize other class variables
		this->frame_size = PAGE_SIZE;
		this->memory_size = this->frame_size * numframes;
	}
	
	//Additional constructor
	simulator::simulator(int numframes,int alg,string filename){
		simulator(numframes,alg,0,filename);
	}

	//Function that returns true if trace file exists and false otherwise
	bool simulator::verify_file(){
		ifstream infile(this->filename.c_str());

		if(!infile)
			return false;

		infile.close();

		return true;
	} 

	//Function to run a given trace file
	void simulator::run_trace(){
		ifstream infile;

		infile.open(this->filename.c_str());

		char access_type;
		unsigned int address;
		unsigned int cycles;

		int page_number = 0;

		//run get_init_trace if opt algorithm
		if(this->alg == OPT)
			this->opt->get_init_trace(this->filename);

		//Iterate through each line in the trace file
		while((infile >> access_type >> hex >> address >> dec >> cycles)){
			//divide the address by PAGE_SIZE, unless its aging then handle later
			if(this->alg != AGING)
				address /= 4096;

			switch(this->alg){
				case OPT:
					if(!this->opt->contains(address)){
						//PAGE_FAULT
						//try to insert
						int insert = this->opt->insert(address);

						if(insert < 0){
							//Page table is full
							//remove a PTE
							int dirty = this->opt->remove(this->mem_accesses);
							//insert new PTE
							this->opt->insert(address);
						
							//if removed element was dirty then write to disk
							if(dirty == 1)
								this->writes_to_disk++;
						}

						//set dirty if store
						if(access_type == 's')
							this->opt->set_dirty(address);

						//increment page_faults
						this->page_faults++;
					}
					else{
						//HIT
						//set dirty if store
						if(access_type == 's')
							this->opt->set_dirty(address);
					}

					break;
				case FIFO:
					if(!this->fifo->contains(address)){
						//PAGE_FAULT
						//try to insert
						int insert = this->fifo->insert(address);

						if(insert < 0){
							//Page table is full
							//remove a PTE
							int dirty = this->fifo->remove();

							//insert new PTE
							this->fifo->insert(address);

							//if removed element was dirty then write to disk
							if(dirty == 1)
								this->writes_to_disk++;
						}

						//set dirty if store
						if(access_type == 's')
							this->fifo->set_dirty(address);

						//increment page_faults
						this->page_faults++;
					}
					else{
						//HIT
						//set dirty if store
						if(access_type == 's')
							this->fifo->set_dirty(address);
					}

					break;
				case AGING:
					//get page_number
					page_number = address/4096;

					//increment cycles appropriately
					if(this->mem_accesses == 0)
						this->cycle_count = cycles;
					else
						this->cycle_count += cycles;

					//Handle refresh at apropriate times before handling mem access
					while(this->refresh*this->refresh_count <= this->cycle_count){
						this->aging->refresh_counters();

						this->refresh_count++;
					}

					if(!this->aging->contains(page_number)){
						//PAGE_FAULT
						//try to insert
						int insert = this->aging->insert(page_number);

						if(insert < 0){
							//Page table is full
							//remove a PTE
							int dirty = this->aging->remove();

							//insert new PTE
							this->aging->insert(page_number);

							//if removed element was dirty then write to disk
							if(dirty == 1)
								this->writes_to_disk++;
						}

						//set full address for new PTE
						this->aging->set_full_addr(page_number,address);

						//set dirty if store
						if(access_type == 's')
							this->aging->set_dirty(page_number);

						//increment page_faults
						this->page_faults++;
					}
					else{
						//HIT
						//set dirty if store
						if(access_type == 's')
							this->aging->set_dirty(page_number);

						//set reference bit to 1
						this->aging->set_ref(page_number);
					}

					break;
				default:
					break;
			}

			//incremement memory_accesses and cycle_count by 1
			this->mem_accesses++;
			this->cycle_count++;

		}

		infile.close();
	}

	//Report function
	void simulator::show_report(){
		cout << "Algorithm: " << this->alg_s << endl;
		cout << "Number of frames: " << this->numframes << endl;
		cout << "Total memory accesses: " << this->mem_accesses << endl;
		cout << "Total page faults: " << this->page_faults << endl;
		cout << "Total writes to disk: " << this->writes_to_disk << endl;
	}
}
