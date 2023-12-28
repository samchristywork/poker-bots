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

struct card community[5];
struct player players[5];
struct card deck[52];
int deck_position = 0;
int small_blind = 1;
int big_blind = 2;
int pot = 0;
int community_shown = 0;
int hand_shown = 2;
int starting_player = 0;

int main() {
}
