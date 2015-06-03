CC = g++
CFLAGS = -std=c++11 -g -Wall -Iinclude

SRC = src/genoset.cpp\
      src/genotype.cpp\
      src/haploset.cpp\
      src/haplotype.cpp\
      src/main.cpp

OBJS=$(SRC:.cpp=.o)

hi: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o bin/hi

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) bin/hi