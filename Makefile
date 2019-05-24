

objects = staticS1.txt static2 S1.txt

default: prog

name = S1.txt

teste: 
	echo $(objects)

prog.o: daraRed.cpp
	g++ -c -g -O3 -I/usr/local/include daraRed.cpp 

prog: prog.o
	g++ -g -o program daraRed.o -L/usr/local/lib -lGeographic

.PHONY: clean

local.o: example-LocalCartesian.cpp
	g++ -c -g -O3 -I/usr/local/include example-LocalCartesian.cpp

example: local.o
	g++ -g -o example example-LocalCartesian.o -L/usr/local/lib -lGeographic

reduced: prog
	./program $(name)

draw: reduced plotgps.py 
	python plotgps.py $(name)

hist: reduced plotHist.py 
	python plotHist.py $(name)

clean:
	rm daraRed.o program