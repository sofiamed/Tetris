COMP = g++
LIBS = 
OPTIONS = -std=c++11 -g


%.o : %.cpp
	$(COMP) $(OPTIONS) -c $^ -o $@ $(LIBS)
	

init: main.o
	$(COMP) $(OPTIONS) main.o -o Tetris.exe $(LIBS)
	./Tetris.exe
	
clean:
	rm -f *.o

