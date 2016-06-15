GCC = g++
CFLAGS = -g -Wall
OBJS = GPIO.o MultiSpeed.o
EXE = GPIO

$(EXE): $(OBJS)
	$(GCC) $(OBJS) -o $(EXE) -pthread -std=c++0x

GPIO.o: GPIO.cc GPIO.h
	$(GCC) $(CFLAGS) -c GPIO.cc

MultiSpeed.o: MultiSpeed.cc GPIO.h
	$(GCC) $(CFLAGS) -c MultiSpeed.cc -pthread -std=c++0x

clean:
	rm $(OBJS) $(EXE)

