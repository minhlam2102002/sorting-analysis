CC = g++
TARGET = sort
all : main.o DataGenerator.o SortAlgorithm.o Experimental.o CommandLine.o SortAlgorithmWithCount.o
	$(CC) main.o DataGenerator.o SortAlgorithm.o Experimental.o CommandLine.o SortAlgorithmWithCount.o -o $(TARGET)
DataGenerator.o : DataGenerator.cpp DataGenerator.h
	$(CC) -g -c DataGenerator.cpp
SortAlgorithm.o : SortAlgorithm.cpp SortAlgorithm.h
	$(CC) -g -c SortAlgorithm.cpp
SortAlgorithmWithCount.o : SortAlgorithmWithCount.cpp SortAlgorithmWithCount.h
	$(CC) -g -c SortAlgorithmWithCount.cpp
Experimental.o : Experimental.cpp Experimental.h
	$(CC) -g -c Experimental.cpp
CommandLine.o : CommandLine.cpp CommandLine.h
	$(CC) -g -c CommandLine.cpp
main.o : main.cpp DataGenerator.h SortAlgorithm.h Experimental.h CommandLine.h SortAlgorithmWithCount.h
	$(CC) -g -c main.cpp
clean :
	rm -f *.o
	rm -f main