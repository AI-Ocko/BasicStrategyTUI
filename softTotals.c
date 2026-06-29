#include "basicStrategy.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Dealer
// UpCard--------------A------2------3------4------5------6------7------8------9-----10
Action SoftTotalsH17[8][10] = {
    /* A,2 */ {H, H, H, H, D, D, H, H, H, H},
    /* A,3 */ {H, H, H, H, D, D, H, H, H, H},
    /* A,5 */ {H, H, H, D, D, D, H, H, H, H},
    /* A,5 */ {H, H, H, D, D, D, H, H, H, H},
    /* A,6 */ {H, H, D, D, D, D, H, H, H, H},
    /* A,7 */ {H, Ds, Ds, Ds, Ds, Ds, S, S, H, H},
    /* A,8 */ {S, S, S, S, S, Ds, S, S, S, S},
    /* A,9 */ {S, S, S, S, S, S, S, S, S, S}};

Action SoftTotalsS17[8][10] = {
    /* A,2 */ {H, H, H, H, D, D, H, H, H, H},
    /* A,3 */ {H, H, H, H, D, D, H, H, H, H},
    /* A,5 */ {H, H, H, D, D, D, H, H, H, H},
    /* A,5 */ {H, H, H, D, D, D, H, H, H, H},
    /* A,6 */ {H, H, D, D, D, D, H, H, H, H},
    /* A,7 */ {H, S, Ds, Ds, Ds, Ds, S, S, H, H},
    /* A,8 */ {S, S, S, S, S, S, S, S, S, S},
    /* A,9 */ {S, S, S, S, S, S, S, S, S, S}};

int softTotalTrainer(Score *score, Settings *settings) {
  int dealerUpCard = dealDealerUpCard();
  int playerSecondCard = rand() % 8;

  char printPlayerSecondCard;
  char userAnswer;
  char correctAnswer;

  // Convert int to char
  printPlayerSecondCard = playerSecondCard + '2';

  // Print messages
  printf("You have A,%c\n", printPlayerSecondCard);
  printDealerUpCard(dealerUpCard);

  // Get user choice
  printf("Do you (H)it, (D)ouble, (S)tand, or (Q)uit?: ");
  scanf(" %c", &userAnswer);

  // exit
  if (toupper(userAnswer) == 'Q') {
    return 0;
  }

  if (settings->h17OrS17 == 'H') {
    correctAnswer = answerToChar(
        SoftTotalsH17[playerSecondCard][dealerUpCard - 1], settings);
  } else {
    correctAnswer = answerToChar(
        SoftTotalsS17[playerSecondCard][dealerUpCard - 1], settings);
  }

  checkAndScore(score, correctAnswer, userAnswer);

  return 1;
};
