#Nicholas Schroeder
# COE 1550 - Project 3 - 11.11.2019 

#Makefile

vmsim: main.o simulator.o page_table.o fifo_sim.o aging_sim.o opt_sim.o
	g++ --std=c++11 -o vmsim $^
main.o: main.cpp simulator.o page_table.o fifo_sim.o aging_sim.o opt_sim.o
	g++ --std=c++11 -c main.cpp
simulator.o: simulator.cpp simulator.h page_table.o fifo_sim.o aging_sim.o opt_sim.o
	g++ --std=c++11 -c simulator.cpp
aging_sim.o: aging_sim.cpp aging_sim.h page_table.o
	g++ --std=c++11 -c aging_sim.cpp
fifo_sim.o: fifo_sim.cpp fifo_sim.h page_table.o
	g++ --std=c++11 -c fifo_sim.cpp
opt_sim.o: opt_sim.cpp opt_sim.h page_table.o
	g++ --std=c++11 -c opt_sim.cpp
page_table.o: page_table.cpp page_table.h
	g++ --std=c++11 -c page_table.cpp

clean:
	rm -rf *.o vmsim

clean_exec:
	rm -rf *.o

