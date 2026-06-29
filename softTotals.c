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
  int dealerUpCard = (rand() % 10) + 1;
  int playerSecondCard = rand() % 8;

  char printPlayerSecondCard;
  char printDealerUpCard;
  char userAnswer;
  char correctAnswer;

  // Convert int to char
  printPlayerSecondCard = playerSecondCard + '2';
  if (dealerUpCard == 1) {
    printDealerUpCard = 'A';
  } else {
    printDealerUpCard = dealerUpCard;
  }

  // Print messages
  printf("You have A,%c\n", printPlayerSecondCard);
  if (printDealerUpCard == 'A') {
    printf("Dealer's up card is %c\n", printDealerUpCard);
  } else {
    printf("Dealer's up card is %d\n", printDealerUpCard);
  }

  // Get user choice
  printf("Do you (H)it, (D)ouble, (S)tand, or (Q)uit?: ");
  scanf(" %c", &userAnswer);

  // exit
  if (toupper(userAnswer) == 'Q') {
    return 0;
  }

  score->total++;

  // Check if game is H-17 or S-17
  if (settings->h17OrS17 == 'H') {
    // Debug print
    // printf("This is a H-17 Game. Dealer hits on soft 17\n");

    // Check correct answer
    switch (SoftTotalsH17[playerSecondCard][dealerUpCard - 1]) {
    case H:
      correctAnswer = 'H';
      break;
    case S:
      correctAnswer = 'S';
      break;
    case D:
      correctAnswer = 'D';
      break;
    case Ds:
      correctAnswer = 'D';
      break;
    default:
      printf("error checking answer\n");
      break;
    }
  } else {
    // Debug print
    // printf("This is a S-17 Game. Dealer stands on soft 17\n");

    // Check correct answer
    switch (SoftTotalsS17[playerSecondCard][dealerUpCard - 1]) {
    case H:
      correctAnswer = 'H';
      break;
    case S:
      correctAnswer = 'S';
      break;
    case D:
      correctAnswer = 'D';
      break;
    case Ds:
      correctAnswer = 'S';
      break;
    default:
      printf("error checking answer\n");
      break;
    }
  }

  // Compare
  if (correctAnswer == toupper(userAnswer)) {
    printf("Correct!\n");
    score->correct++;
  } else {
    printf("Incorrect! Correct answer was %c\n", correctAnswer);
  }

  return 1;
};
