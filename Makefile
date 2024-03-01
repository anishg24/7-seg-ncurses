EXE = renderer

$(EXE): main.cpp
	$(CC) -lncurses -o $(EXE) main.cpp

clean:
	rm renderer
