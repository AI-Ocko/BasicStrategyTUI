#include "../include/basicStrategy.h"
#include "../include/init_scr.h"
#include <ctype.h>
#include <curses.h>
#include <stdlib.h>

// Dealer
// UpCard--------------A------2------3------4------5------6------7------8------9-----10
Action SoftTotalsH17[8][10] = {
    /* A,2 */ {H, H, H, H, D, D, H, H, H, H},
    /* A,3 */ {H, H, H, H, D, D, H, H, H, H},
    /* A,4 */ {H, H, H, D, D, D, H, H, H, H},
    /* A,5 */ {H, H, H, D, D, D, H, H, H, H},
    /* A,6 */ {H, H, D, D, D, D, H, H, H, H},
    /* A,7 */ {H, Ds, Ds, Ds, Ds, Ds, S, S, H, H},
    /* A,8 */ {S, S, S, S, S, Ds, S, S, S, S},
    /* A,9 */ {S, S, S, S, S, S, S, S, S, S}};

Action SoftTotalsS17[8][10] = {
    /* A,2 */ {H, H, H, H, D, D, H, H, H, H},
    /* A,3 */ {H, H, H, H, D, D, H, H, H, H},
    /* A,4 */ {H, H, H, D, D, D, H, H, H, H},
    /* A,5 */ {H, H, H, D, D, D, H, H, H, H},
    /* A,6 */ {H, H, D, D, D, D, H, H, H, H},
    /* A,7 */ {H, S, Ds, Ds, Ds, Ds, S, S, H, H},
    /* A,8 */ {S, S, S, S, S, S, S, S, S, S},
    /* A,9 */ {S, S, S, S, S, S, S, S, S, S}};

int softTotalTrainer(WINDOW *window, Score *score, Settings *settings) {
  int dealerUpCard = dealDealerUpCard();
  int playerSecondCard = rand() % 8;

  char printPlayerSecondCard;
  char userAnswer;
  char correctAnswer;

  // Convert int to char
  printPlayerSecondCard = playerSecondCard + '2';

  werase(window);
  box(window, 0, 0);
  wrefresh(window);

  // Print hands
  mvwprintw(window, SCREEN_LINE_1, SCREEN_MARGIN, "You have A,%c",
            printPlayerSecondCard);
  wrefresh(window);

  printDealerUpCard(window, dealerUpCard); // prints on SCREEN_LINE_2

  // Get user choice
  mvwprintw(window, SCREEN_LINE_3, SCREEN_MARGIN,
            "Do you (H)it, (D)ouble, (S)tand, or (Q)uit?: ");
  wrefresh(window);
  userAnswer = wgetch(window);

  // exit
  if (toupper(userAnswer) == 'Q') {
    return 0;
  }

  // Check for invalid input
  while (userAnswer != 'h' && userAnswer != 'd' && userAnswer != 's') {
    mvwprintw(window, SCREEN_LINE_7, SCREEN_MARGIN,
              "Invalid input... please answer again.");
    userAnswer = wgetch(window);
    mvwprintw(window, SCREEN_LINE_7, SCREEN_MARGIN,
              "                                     ");
  }

  // Check userAnswer against correctAnswer
  if (settings->h17OrS17 == 'H') {
    correctAnswer = answerToChar(
        window, SoftTotalsH17[playerSecondCard][dealerUpCard - 1], settings);
  } else {
    correctAnswer = answerToChar(
        window, SoftTotalsS17[playerSecondCard][dealerUpCard - 1], settings);
  }

  // Print results
  checkAndScore(window, score, correctAnswer, userAnswer);

  return 1;
};
