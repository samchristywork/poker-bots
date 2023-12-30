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

void deal_community() {
  for (int i = 0; i < 5; i++) {
    community[i] = deck[deck_position];
    deck_position++;
  }
}

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

void show_deck() {
  printf("Deck: ");
  for (int i = deck_position; i < 52; i++) {
    printf("%d%c ", deck[i].value, deck[i].suit);
  }
  printf("\n");
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

void show_player(int i) {
  printf("Player %d: ", i);
  printf("%d ", players[i].chips);
  for (int j = 0; j < hand_shown; j++) {
    printf("%d%c ", players[i].hand[j].value, players[i].hand[j].suit);
  }
  if (players[i].folded) {
    printf("(folded)");
  }
  printf("\n");
}

void show_community() {
  printf("Community: ");
  for (int i = 0; i < community_shown; i++) {
    printf("%d%c ", community[i].value, community[i].suit);
  }
  printf("\n");
}

void call(int i) { printf("	Player %d calls\n", i); }

void raise(int i) { printf("	Player %d raises\n", i); }

void fold(int i) {
  printf("	Player %d folds\n", i);
  players[i].folded = true;
}

void check(int i) { printf("	Player %d checks\n", i); }

void ai(int i) {
  if (players[i].folded) {
    return;
  }
  int r = rand() % 100;
  if (r < 50) {
    call(i);
  } else if (r < 75) {
    raise(i);
  } else {
    fold(i);
  }
}

void preflop() {
  printf("Preflop\n");
  int i = starting_player;
  for (int j = 0; j < 5; j++) {
    ai(i);
    i = (i + 1) % 5;
  }
}

int main() {
  srand(time(NULL));
  init_deck();
  shuffle_deck();
  for (int i = 0; i < 5; i++) {
    init_player(i);
  }

  deal_community();

  show_players();
  show_community();

  preflop();

  community_shown = 3;
  hand_shown = 5;

  show_players();
  show_community();
}
