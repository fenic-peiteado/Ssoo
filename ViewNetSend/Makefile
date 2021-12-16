CXX=g++

CXXXFLAGS=-std=c++14 -g -Wall

programa:viewnetsend.o socket.o
		$(CXX) $(CXXXFLAGS) -o programa viewnetsend.o socket.o

viewnetsend.o: viewnetsend.cc
		$(CXX) $(CXXXFLAGS) -c viewnetsend.cc 
socket.o: socket.h socket.cc
		$(CXX) $(CXXXFLAGS) -c  socket.cc
clean:
		rm -f viewnetsend *.o