DEFAULT_GMAX = 40
GMAX = $(DEFAULT_GMAX)
CPP = g++ -DNDEBUG -DGMAX=$(GMAX) -march=corei7 -O3

all: ../init_files ../run_walk ../show_semigroup ../run_alone

%.o:%.cpp %.hpp
	$(CPP) -c $< -o $@

../init_files: semigroup.o sse.o init_files.cpp 
	$(CPP) $^ -o $@

../run_walk: semigroup.o sse.o stack.o walk.o run_walk.cpp 
	$(CPP) $^ -o $@

../show_semigroup: semigroup.o sse.o show_semigroup.cpp 
	$(CPP) $^ -o $@	

../run_alone: semigroup.o sse.o stack.o walk.o main.cpp
	$(CPP) $^ -o $@

clean:
	$(RM) ../init_files ../run_walk
	$(RM) *.o
	$(RM) ../todo/* ../lock/* ../done/* ../results/* ../counter/*
	$(RM) *~
	$(RM) vgcore*

