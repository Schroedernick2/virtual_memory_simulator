//Nicholas Schroeder
// COE 1550 - Project 3 - 11.11.2019 

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <string>
#include "fifo_sim.h"
#include "opt_sim.h"
#include "aging_sim.h"

#define OPT		0
#define FIFO	1
#define AGING	2 

namespace COE_1550_VMSIM {
	//Simulator class
	class simulator{
		public:
			//Constructors
			simulator();
			simulator(int numframes,int alg,int refresh, std::string filename);
			simulator(int numframes,int alg,std::string filename);

			//function to make sure trace file exists
			bool verify_file();
			//function to report statistics at the end of a simulation
			void show_report();
			//function to run a given trace file
			void run_trace();

		private:
			int numframes;			//number of frames
			int alg;				//algorithm
			std::string alg_s;		//algorithm string representation
			int refresh;			//refresh period
			std::string filename;	//trace file name

			unsigned int frame_size;		//frame size
			unsigned int physical_frames;	//physical frame
			long int memory_size;			//size of memory

			int mem_accesses;		//number of memory accesses
			int page_faults;		//number of page_faults
			int writes_to_disk;		//number of writes to disk
			int cycle_count;		//number of cycles
			int refresh_count;		//number of refreshes

			fifo_sim* fifo;		//instance of fifo_sim class
			opt_sim* opt;		//instance of opt_sim class
			aging_sim* aging;	//instance of aging_sim class
	};
}

#endif
