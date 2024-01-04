#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct card {
  int value;
  char suit;
};

struct player {
  struct card hand[2];
  bool folded;
  bool human;
  int chips;
};

struct rank {
  int rank;
  int value;
};

struct game {
  struct card community[5];
  struct player players[5];
  struct card deck[52];
  int deck_position;
  int small_blind;
  int big_blind;
  int pot;
  int community_shown;
  int hand_shown;
  int starting_player;
};

struct game game;

void deal_community() {
  for (int i = 0; i < 5; i++) {
    game.community[i] = game.deck[game.deck_position];
    game.deck_position++;
  }
}

void init_deck() {
  int i = 0;
  for (int suit = 0; suit < 4; suit++) {
    for (int value = 2; value < 15; value++) {
      game.deck[i].value = value;
      switch (suit) {
      case 0:
        game.deck[i].suit = 'H';
        break;
      case 1:
        game.deck[i].suit = 'D';
        break;
      case 2:
        game.deck[i].suit = 'C';
        break;
      case 3:
        game.deck[i].suit = 'S';
        break;
      }
      i++;
    }
  }
}

void shuffle_deck() {
  for (int i = 0; i < 52; i++) {
    int j = rand() % 52;
    struct card temp = game.deck[i];
    game.deck[i] = game.deck[j];
    game.deck[j] = temp;
  }
}

void show_deck() {
  printf("Deck: ");
  for (int i = game.deck_position; i < 52; i++) {
    printf("%d%c ", game.deck[i].value, game.deck[i].suit);
  }
  printf("\n");
}

void init_player(int i) {
  game.players[i].folded = false;
  game.players[i].human = false;
  game.players[i].chips = 20;

  for (int j = 0; j < 5; j++) {
    game.players[i].hand[j] = game.deck[game.deck_position];
    game.deck_position++;
  }
}

void show_player(int i) {
  printf("Player %d: ", i);
  printf("%d ", game.players[i].chips);
  for (int j = 0; j < game.hand_shown; j++) {
    printf("%d%c ", game.players[i].hand[j].value,
           game.players[i].hand[j].suit);
  }
  if (game.players[i].folded) {
    printf("(folded)");
  }
  printf("\n");
}

void show_community() {
  printf("Community: ");
  for (int i = 0; i < game.community_shown; i++) {
    printf("%d%c ", game.community[i].value, game.community[i].suit);
  }
  printf("\n");
}

void call(int i) { printf("	Player %d calls\n", i); }

void raise(int i) { printf("	Player %d raises\n", i); }

void fold(int i) {
  printf("	Player %d folds\n", i);
  game.players[i].folded = true;
}

void check(int i) { printf("	Player %d checks\n", i); }

void ai(int i) {
  if (game.players[i].folded) {
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
  int i = game.starting_player;
  for (int j = 0; j < 5; j++) {
    ai(i);
    i = (i + 1) % 5;
  }
}

bool is_flush(struct card hand[7]) {
  int count[4] = {0, 0, 0, 0};
  for (int i = 0; i < 7; i++) {
    switch (hand[i].suit) {
    case 'H':
      count[0]++;
      break;
    case 'D':
      count[1]++;
      break;
    case 'C':
      count[2]++;
      break;
    case 'S':
      count[3]++;
      break;
    }
  }
  for (int i = 0; i < 4; i++) {
    if (count[i] >= 5) {
      return true;
    }
  }
  return false;
}

bool is_straight(struct card hand[7]) {
  int count[15] = {0};
  for (int i = 0; i < 7; i++) {
    count[hand[i].value]++;
  }
  for (int i = 0; i < 11; i++) {
    if (count[i] && count[i + 1] && count[i + 2] && count[i + 3] &&
        count[i + 4]) {
      return true;
    }
  }
  return false;
}

bool is_straight_flush(struct card hand[7]) {
  if (is_flush(hand) && is_straight(hand)) {
    return true;
  }

  return false;
}

bool is_royal_flush(struct card hand[7]) {
  if (is_straight_flush(hand)) {
    if (hand[0].value == 10) {
      return true;
    }
  }

  return false;
}

bool is_four_of_a_kind(struct card hand[7]) {
  int count[15] = {0};
  for (int i = 0; i < 7; i++) {
    count[hand[i].value]++;
  }
  for (int i = 0; i < 15; i++) {
    if (count[i] >= 4) {
      return true;
    }
  }
  return false;
}

bool is_full_house(struct card hand[7]) {
  int count[15] = {0};
  for (int i = 0; i < 7; i++) {
    count[hand[i].value]++;
  }
  bool three = false;
  bool two = false;
  for (int i = 0; i < 15; i++) {
    if (count[i] == 3) {
      three = true;
    } else if (count[i] == 2) {
      two = true;
    }
  }
  if (three && two) {
    return true;
  }
  return false;
}

bool is_three_of_a_kind(struct card hand[7]) {
  int count[15] = {0};
  for (int i = 0; i < 7; i++) {
    count[hand[i].value]++;
  }
  for (int i = 0; i < 15; i++) {
    if (count[i] == 3) {
      return true;
    }
  }
  return false;
}

int main() {
  game.starting_player = 0;
  game.small_blind = 1;
  game.big_blind = 2;
  game.pot = 0;
  game.community_shown = 0;
  game.hand_shown = 2;

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

  game.community_shown = 3;
  game.hand_shown = 5;

  show_players();
  show_community();
}
