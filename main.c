#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void init_deck() {
  int i = 0;
  for (int suit = 0; suit < 4; suit++) {
    for (int value = 2; value < 15; value++) {
      deck[i].value = value;
      switch (suit) {
      case 0:
        deck[i].suit = 'H';
        break;
      case 1:
        deck[i].suit = 'D';
        break;
      case 2:
        deck[i].suit = 'C';
        break;
      case 3:
        deck[i].suit = 'S';
        break;
      }
      i++;
    }
  }
}

void shuffle_deck() {
  for (int i = 0; i < 52; i++) {
    int j = rand() % 52;
    struct card temp = deck[i];
    deck[i] = deck[j];
    deck[j] = temp;
  }
}

void init_player(int i) {
  players[i].folded = false;
  players[i].human = false;
  players[i].chips = 20;

  for (int j = 0; j < 5; j++) {
    players[i].hand[j] = deck[deck_position];
    deck_position++;
  }
}

int main() {
  srand(time(NULL));
}
