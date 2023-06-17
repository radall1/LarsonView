# LarsonView



## LarsonView

LarsonView is a mobile application that allows users to remotely check the availability of laundry machines in Larson Hall and schedule the occupied ones in advance.

## Code Structure

For the purposes of this project, we assume that the output from the Arduino board is stored in the startup_mem file. The app needs the following files to work. 

- [ ] State.cpp
- [ ] State.h
- [ ] code.cpp
- [ ] code.h
- [ ] app3.cpp
- [ ] startup_mem
- [ ] schedule.yaml
- [ ] count.yaml
- [ ] scheduling.yaml
- [ ] scheduled.yaml

## How to compile and run

The app material is available in the final folder. To compile it, run the following lines:

```
g++ -g -c code.cpp
g++ -g -c State.cpp
g++ -g -c app3.cpp
g++ -g -Wall app3.o State.o code.o /usr/local/cs/cs251/react.o -lcurl
```

Alternatively, you could just utilize our Makefile by writing the following line:

```
make
```
