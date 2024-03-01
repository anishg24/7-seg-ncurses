To run, you need to first ensure you have ncurses installed. Then run:
```bash
make
./main c0 c1 c2 c3 c4 c5 c6 c7
```
where c0-c7 are your cathode bits (as lined up in the diagram we went over).

To generate some control bits to verify your results against, you can run:
```bash
./main d <0-15>
```
where <0-15> is some value in between 0 and 15.

You can use this in conjunction with the renderer as:
```bash
./main $(./main d <0-15>)
```
