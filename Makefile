CPP = g++
CPPFLAGS = -Wall

OBJ = main.o EmpresasParceiras.o

main: $(OBJ)
	$(CPP) $(CPPFLAGS) $(OBJ) -o main 

main.o: main.cpp
	$(CPP) $(CPPFLAGS) -c main.cpp -o main.o

EmpresasParceiras.o: EmpresasParceiras.cpp EmpresasParceiras.h
	$(CPP) $(CPPFLAGS) -c EmpresasParceiras.cpp -o EmpresasParceiras.o

all: main

clean:
	rm -f *.o
