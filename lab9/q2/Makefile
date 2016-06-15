GCC = g++
CFLAGS = -g -Wall
OBJS = GPIO.o main.o
EXE = GPIO

$(EXE): $(OBJS)
	$(GCC) $(OBJS) -o $(EXE)

GPIO.o: GPIO.cc GPIO.h
	$(GCC) $(CFLAGS) -c GPIO.cc

main.o: main.cc GPIO.h
	$(GCC) $(CFLAGS) -c main.cc

clean:
	rm $(OBJS) $(EXE)

