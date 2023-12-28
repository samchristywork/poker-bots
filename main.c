#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct card {
  int value;
  char suit;
};

struct player {
  struct card hand[5];
  bool folded;
  bool human;
  int chips;
};

struct rank {
  int rank;
  int value;
};

int main() {
}
