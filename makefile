#Nicholas Schroeder [NIS102]
# COE 1550 - Project 3 - DUE: 11.11.2019

vmsim: main.o simulator.o fifo_sim.o
	g++ -o vmsim $^
main.o: main.cpp simulator.h fifo_sim.h
	g++ -c main.cpp
simulator.o: simulator.cpp simulator.h fifo_sim.cpp fifo_sim.h
	g++ -c simulator.cpp
fifo_sim.o: fifo_sim.cpp fifo_sim.h
	g++ -c fifo_sim.cpp

clean:
	rm -rf *.o vmsim
