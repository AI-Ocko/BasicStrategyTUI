#include "basicStrategy.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Trainer(int (*trainerFunction)(Score *score)) {
  Score score = {0, 0};
  srand(time(NULL));
  while (trainerFunction(&score)) {
    if (score.total > 0) {
      printf("\n--- Results ---\n");
      printf("Score: %d / %d\n", score.correct, score.total);
      printf("Accuracy: %.1f%%\n\n", (float)score.correct / score.total * 100);
    }
  };
}

int main(void) {
  char menu_option, initials;
  int difficulty;

  printf("==============Basic==Strategy==Trainer=============\n");

  do {
    printf("Main Menu\n");
    printf("1. Pair Splitting\n");
    printf("2. Soft Totals\n");
    printf("3. Hard Totals\n");
    printf("4. Options\n");
    printf("0. Exit\n");
    printf("Please enter an option from the main menu: ");
    scanf(" %c", &menu_option);

    switch (menu_option) {
    case '1':
      Trainer(pairSplittingTrainer);
      break;
    case '2':
      Trainer(softTotalTrainer);
      break;
    case '3':
      Trainer(hardTotalTrainer);
      break;
    case '0':
      break;
    default:
      printf("invalid input");
      break;
    }
  } while (menu_option != '0');

  return 0;
}
