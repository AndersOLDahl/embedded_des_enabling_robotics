GCC = g++
CFLAGS = -g -Wall
OBJS = WiimoteBtns.o main.o
EXE = WiimoteBtns

$(EXE): $(OBJS)
	$(GCC) $(OBJS) -o $(EXE)

WiimoteBtns.o: WiimoteBtns.cpp WiimoteBtns.h
	$(GCC) $(CFLAGS) -c WiimoteBtns.cpp

main.o: main.cpp WiimoteBtns.h
	$(GCC) $(CFLAGS) -c main.cpp

clean:
	rm $(OBJS) $(EXE)
