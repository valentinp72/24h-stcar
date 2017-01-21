toolsLoc = ../tools/

main: main.o tools.o easySdl2.o
	gcc -o $@ $^ -framework SDL2 -framework SDL2_image -framework SDL2_ttf

main.o: main.c $(toolsLoc)tools.h $(toolsLoc)easySdl2.h
	gcc -c $<

tools.o: $(toolsLoc)tools.c
	gcc -c $<

easySdl2.o: $(toolsLoc)easySdl2.c
	gcc -c $<
