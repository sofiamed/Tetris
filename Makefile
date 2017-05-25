COMP = g++
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
OPTIONS = -std=c++11 -g
BUILD_DIR = build/
THIS_DIR = `pwd`



$(BUILD_DIR)%.o : %.cpp
	$(COMP) $(OPTIONS) -c $^ -o $@ $(LIBS)



INIT_FILES = $(BUILD_DIR)init.o	$(BUILD_DIR)Blocs.o $(BUILD_DIR)Fenetre.o
init: $(INIT_FILES)
	$(COMP) $(OPTIONS) $^ -o $(BUILD_DIR)Tetris.exe $(LIBS)
	make clean
	#$(BUILD_DIR)Tetris.exe

clean:
	rm -f $(BUILD_DIR)*.o

