CXX=g++

CXXXFLAGS=-std=c++14 -g -Wall

programa: viewnetreceive.o socket.o
		$(CXX) $(CXXXFLAGS) -o programa viewnetreceive.o socket.o

viewnetreceive.o: viewnetreceive.cc
		$(CXX) $(CXXXFLAGS) -c viewnetreceive.cc 
socket.o: socket.h socket.cc
		$(CXX) $(CXXXFLAGS) -c  socket.cc
clean:
		rm -f viewnetreceive *.o