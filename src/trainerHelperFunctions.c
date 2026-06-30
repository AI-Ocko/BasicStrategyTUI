#include "basicStrategy.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int dealDealerUpCard() { return rand() % 10 + 1; }

void printDealerUpCard(int dealerUpCard) {
  if (dealerUpCard == 1) {
    printf("Dealer's Up Card is A\n");
  } else {
    printf("Dealer's Up Card is %d\n", dealerUpCard);
  }
}

char answerToChar(Action a, Settings *settings) {
  switch (a) {
  case H:
    return 'H';
  case S:
    return 'S';
  case D:
    return 'D';
  case Ds:
    return settings->h17OrS17 == 'H' ? 'D' : 'S';
  case N:
    return 'N';
  case Y:
    return 'Y';
  case YN:
    return settings->doubleAfterSplit == 'Y' ? 'Y' : 'N';
  case Surr:
    return 's';
  default:
    printf("Error, could not print answer.\n");
    return '?';
  }
}

void checkAndScore(Score *score, char correctAnswer, char userAnswer) {
  score->total++;

  if (correctAnswer == toupper(userAnswer)) {
    printf("Correct!\n");
    score->correct++;
  } else {
    printf("Incorrect...The correct answer is %c\n", correctAnswer);
  }
};
