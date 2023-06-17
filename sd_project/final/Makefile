app3:  State.o code.o app3.o
	 g++ -g -Wall app3.o State.o code.o /usr/local/cs/cs251/react.o -lcurl

app3.o: app3.cpp
	g++ -g -c app3.cpp

State.o: State.cpp State.h
	g++ -g -c State.cpp

code.o: code.cpp code.h
	g++ -g -c code.cpp