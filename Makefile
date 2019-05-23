default: prog


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
	./program

draw: reduced plotgps.py
	python plotgps.py

clean:
	rm daraRed.o program