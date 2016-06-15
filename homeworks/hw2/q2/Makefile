GCC = g++
CFLAGS = -g -Wall
OBJS = CalcMain.o Calculator.o
EXE = Calculator

$(EXE): $(OBJS)
	$(GCC) $(OBJS) -o $(EXE)

Calculator.o: Calculator.cpp Calculator.h
	$(GCC) $(CFLAGS) -c Calculator.cpp

CalcMain.o: CalcMain.cpp Calculator.h
	$(GCC) $(CFLAGS) -c CalcMain.cpp

clean:
	rm $(OBJS) $(EXE)

