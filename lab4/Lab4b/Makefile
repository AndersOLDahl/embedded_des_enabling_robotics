GCC = g++
CFLAGS = -g -Wall
OBJS = WiimoteAccel.o main.o
EXE = WiimoteAccel

$(EXE): $(OBJS)
	$(GCC) $(OBJS) -o $(EXE)

WiimoteBtns.o: WiimoteAccel.cpp WiimoteAccel.h
	$(GCC) $(CFLAGS) -c WiimoteBtns.cpp

main.o: main.cpp WiimoteAccel.h
	$(GCC) $(CFLAGS) -c main.cpp

clean:
	rm $(OBJS) $(EXE)
