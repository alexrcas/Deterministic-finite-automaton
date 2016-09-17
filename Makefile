CC=g++ 
CXXFLAGS=-g

OBJS = main.o dfa.o delta.o interface.o

 state.oall: ${OBJS}
	$(CC) $(CXXFLAGS) -o dfa ${OBJS}

clean: 
	rm -rf *.o dfa
