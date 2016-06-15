GCC = g++
CFLAGS = -g -Wall
OBJS = zedMain.o ZedBoard.o WiimoteAccel.o
EXE = zedboard

$(EXE): $(OBJS)
	$(GCC) $(OBJS) -o $(EXE)

zedMain.o: zedMain.cpp ZedBoard.h
	$(GCC) $(CFLAGS) -c zedMain.cpp

WiimoteAccel.o: WiimoteAccel.cpp WiimoteAccel.h
	$(GCC) $(CFLAGS) -c WiimoteAccel.cpp

ZedBoard.o: ZedBoard.cpp ZedBoard.h
	$(GCC) $(CFLAGS) -c ZedBoard.cpp

clean:
	rm $(OBJS)
