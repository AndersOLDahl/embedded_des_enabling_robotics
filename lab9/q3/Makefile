GCC = g++
CFLAGS = -g -Wall
OBJS = GPIO.o ServoPosition.o
EXE = GPIO

$(EXE): $(OBJS)
	$(GCC) $(OBJS) -o $(EXE)

GPIO.o: GPIO.cc GPIO.h
	$(GCC) $(CFLAGS) -c GPIO.cc

ServoPosition.o: ServoPosition.cc GPIO.h
	$(GCC) $(CFLAGS) -c ServoPosition.cc

clean:
	rm $(OBJS) $(EXE)

