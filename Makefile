COMP = g++
LIBS = 
OPTIONS = -std=c++11 -g
BUILD_DIR = build/
THIS_DIR = `pwd`






$(BUILD_DIR)%.o : %.cpp
	$(COMP) $(OPTIONS) -c $^ -o $@ $(LIBS)
	

	
INIT_FILES = $(BUILD_DIR)init.o	
init: $(INIT_FILES)
	$(COMP) $(OPTIONS) $^ -o $(BUILD_DIR)Tetris.exe $(LIBS)
	$(BUILD_DIR)Tetris.exe
	
clean:
	rm -f $(BUILD_DIR)*.o

