EXE = renderer

$(EXE): main.cpp
	$(CXX) -o $(EXE) main.cpp -lncurses

clean:
	rm renderer
