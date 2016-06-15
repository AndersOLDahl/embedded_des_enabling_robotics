GCC = g++
CFLAGS = -g -Wall
OBJS = GPIO.o ServoSpeed.o
EXE = GPIO

$(EXE): $(OBJS)
	$(GCC) $(OBJS) -o $(EXE)

GPIO.o: GPIO.cc GPIO.h
	$(GCC) $(CFLAGS) -c GPIO.cc

ServoSpeed.o: ServoSpeed.cc GPIO.h
	$(GCC) $(CFLAGS) -c ServoSpeed.cc

clean:
	rm $(OBJS) $(EXE)

