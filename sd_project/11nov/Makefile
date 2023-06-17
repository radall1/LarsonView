app2:  code.o State.o app2.o
	g++ -g -Wall code.o State.o app2.o -o app2

app1:  code.o State.o app1.o
	g++ -g -Wall code.o State.o app1.o -o app1

app2.o:  app2.cpp
	g++ -g -Wall -c app2.cpp

app1.o:  app1.cpp
	g++ -g -Wall -c app1.cpp

State.o: State.cpp State.h
	g++ -g -c State.cpp

code.o: code.cpp code.h
	g++ -g -Wall -c code.cpp
