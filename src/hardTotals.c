#include "../include/basicStrategy.h"
#include "../include/init_scr.h"
#include <ctype.h>
#include <stdlib.h>

// Dealer
// UpCard-----A------2------3------4------5------6------7------8------9-----10
Action HardTotalsH17[10][10] = {
    /*  8 */ {H, H, H, H, H, H, H, H, H, H},
    /*  9 */ {H, D, D, D, D, H, H, H, H, H},
    /* 10 */ {D, D, D, D, D, D, D, D, H, H},
    /* 11 */ {D, D, D, D, D, D, D, D, D, D},
    /* 12 */ {H, H, S, S, S, H, H, H, H, H},
    /* 13 */ {S, S, S, S, S, H, H, H, H, H},
    /* 14 */ {S, S, S, S, S, H, H, H, H, H},
    /* 15 */ {S, S, S, S, S, H, H, H, H, H},
    /* 16 */ {S, S, S, S, S, H, H, H, H, H},
    /* 17 */ {S, S, S, S, S, S, S, S, S, S}};

Action HardTotalsS17[10][10] = {
    /*  8 */ {H, H, H, H, H, H, H, H, H, H},
    /*  9 */ {H, D, D, D, D, H, H, H, H, H},
    /* 10 */ {D, D, D, D, D, D, D, D, H, H},
    /* 11 */ {H, D, D, D, D, D, D, D, D, D},
    /* 12 */ {H, H, S, S, S, H, H, H, H, H},
    /* 13 */ {S, S, S, S, S, H, H, H, H, H},
    /* 14 */ {S, S, S, S, S, H, H, H, H, H},
    /* 15 */ {S, S, S, S, S, H, H, H, H, H},
    /* 16 */ {S, S, S, S, S, H, H, H, H, H},
    /* 17 */ {S, S, S, S, S, S, S, S, S, S}};

int hardTotalTrainer(WINDOW *window, Score *score, Settings *settings) {
  int dealerUpCard = dealDealerUpCard(); // shifts value to A(1)-10
  int playerHardTotal =
      (rand() % 10) + 8; // shifts hardtotal to actual range 8-17

  char userAnswer;
  char correctAnswer;

  werase(window);
  box(window, 0, 0);
  wrefresh(window);

  // Print hard total and dealer up card
  mvwprintw(window, 3, 4, "You have a total of %d!", playerHardTotal);
  wrefresh(window);
  printDealerUpCard(window, dealerUpCard);

  // Get user choice
  mvwprintw(window, 7, 4, "Do you (H)it, (D)ouble, (S)tand, or (Q)uit?: ");
  wrefresh(window);
  userAnswer = wgetch(window);

  // exit
  if (toupper(userAnswer) == 'Q') {
    return 0;
  }

  // Check correct answer
  if (settings->h17OrS17 == 'H') {
    correctAnswer = answerToChar(
        window, HardTotalsH17[playerHardTotal - 8][dealerUpCard - 1], settings);
  } else if (settings->h17OrS17 == 'S') {
    correctAnswer = answerToChar(
        window, HardTotalsS17[playerHardTotal - 8][dealerUpCard - 1], settings);
  } else {
    mvwprintw(window, SCREEN_LINE_7, SCREEN_MARGIN,
              "Error. Please check settings.");
    return 0;
  }

  // Compare
  checkAndScore(window, score, correctAnswer, userAnswer);

  return 1;
};
