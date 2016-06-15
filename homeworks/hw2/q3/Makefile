GCC = g++
CFLAGS = -g -Wall
OBJS = main.o Furniture.o Table.o Bed.o
EXE = Furniture

$(EXE): $(OBJS)
	$(GCC) $(OBJS) -o $(EXE)

main.o: main.cpp Furniture.h Table.h Bed.h
	$(GCC) $(CFLAGS) -c Main.cpp

Furniture.o: Furniture.cpp Furniture.h
	$(GCC) $(CFLAGS) -c Furniture.cpp

Table.o: Table.cpp Table.h
	$(GCC) $(CFLAGS) -c Table.cpp

Bed.o: Bed.cpp Bed.h
	$(GCC) $(CFLAGS) -c Bed.cpp

clean:
	rm $(OBJS) $(EXE)
