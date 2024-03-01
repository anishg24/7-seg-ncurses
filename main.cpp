#include <iostream>
#include <curses.h>
#include <locale.h>
#include <string>

#define FILLED "▓"
// #define EMPTY "░"
#define EMPTY " "

#define NUM_DIGITS 4

#define HORIZONTAL_BAR(startx, starty, character) \
  mvprintw(starty, startx, character); \
  mvprintw(starty, startx+1, character);

#define VERTICAL_BAR(startx, starty, character) \
  mvprintw(starty, startx, character); \
  mvprintw(starty+1, startx, character);

int digit_to_bits[16][8] = {
  {0, 0, 0, 0, 0, 0, 1, 1}, // 0
  {1, 0, 0, 1, 1, 1, 1, 1}, // 1
  {0, 0, 1, 0, 0, 1, 0, 1}, // 2
  {0, 0, 0, 0, 1, 1, 0, 1}, // 3
  {1, 0, 0, 1, 1, 0, 0, 1}, // 4
  {0, 1, 0, 0, 1, 0, 0, 1}, // 5
  {0, 1, 0, 0, 0, 0, 0, 1}, // 6
  {0, 0, 0, 1, 1, 1, 1, 1}, // 7
  {0, 0, 0, 0, 0, 0, 0, 1}, // 8
  {0, 0, 0, 0, 1, 0, 0, 1}, // 9
  {0, 0, 0, 1, 0, 0, 0, 1}, // A
  {1, 1, 0, 0, 0, 0, 0, 1}, // b
  {0, 1, 1, 0, 0, 0, 1, 1}, // C
  {1, 0, 0, 0, 0, 1, 0, 1}, // d
  {0, 1, 1, 0, 0, 0, 0, 1}, // e
  {0, 1, 1, 1, 0, 0, 0, 1}, // f
};

// https://www.realdigital.org/img/48ab4f6b32ae0b47e5d4c519f6ce7c9b.svg
// Remember, signals are active low!
void printDigit(int startx, int starty, int segments[8]) {
  // Imagine a 6x4 grid
  HORIZONTAL_BAR(startx+1, starty, segments[0] ? EMPTY : FILLED);
  HORIZONTAL_BAR(startx+1, starty+3, segments[6] ? EMPTY : FILLED);
  HORIZONTAL_BAR(startx+1, starty+6, segments[3] ? EMPTY : FILLED);

  VERTICAL_BAR(startx, starty+1, segments[5] ? EMPTY : FILLED);
  VERTICAL_BAR(startx+3, starty+1, segments[1] ? EMPTY : FILLED);
  VERTICAL_BAR(startx, starty+4, segments[4] ? EMPTY : FILLED);
  VERTICAL_BAR(startx+3, starty+4, segments[2] ? EMPTY: FILLED);
}

int main (int argc, char *argv[]) {
  if (argc == 3 && argv[1][0] == 'd') {
    int digit = std::atoi(argv[2]);
    if (digit > 15) {
      printf("Expected dumped value to be in range of 0-15, got %d.\n", digit);
      return 1;
    }
    // printf("%d", digit);
    for (int i = 0; i < 8; i++) {
    // for (int i = 7; i >= 0; i--) {
      printf("%d ", digit_to_bits[digit][i]);
    }
    printf("\n");
    return 0;
  }

  if (argc < 8) {
    printf("Expected %d arguments, found %d.\n", 8, argc);
    return 1;
  }

  int bit_vector[8];
  for (int i = 1; i < 8; i++) {
    printf("%d ", argv[i][0] - '0');
    bit_vector[i-1] = argv[i][0] - '0';
  }

  setlocale(LC_ALL, "");
  initscr();
  noecho();
  curs_set(0);

  int startx = 5;
  int starty = 10;
  int offset = 10;

  printDigit(startx, starty, bit_vector); 

  refresh();
  getch();
  endwin();
  return 0;
}
