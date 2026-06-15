#include "basicStrategy.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  char menu_option, initials;
  int difficulty;

  printf("==============Basic==Strategy==Trainer=============\n");

  do {
    printf("Main Menu\n");
    printf("1. Pair Splitting");
    printf("2. Soft Totals");
    printf("3. Hard Totals");
    printf("0. Exit\n");
    printf("Please enter an option from the main menu: ");
    scanf(" %c", &menu_option);

    switch (menu_option) {
    case '1':
      Score score = {0, 0};
      srand(time(NULL));
      while (pairSplittingTrainer(&score)) {
        if (score.total > 0) {
          printf("\n--- Results ---\n");
          printf("Score: %d / %d\n", score.correct, score.total);
          printf("Accuracy: %.1f%%\n\n",
                 (float)score.correct / score.total * 100);
        }
      };
      break;
    case '2':
      srand(time(NULL));
      while (softTotalTrainer(&score)) {
        if (score.total > 0) {
          printf("\n--- Results ---\n");
          printf("Score: %d / %d\n", score.correct, score.total);
          printf("Accuracy: %.1f%%\n\n",
                 (float)score.correct / score.total * 100);
        }
      };
      break;
    case '3':
      srand(time(NULL));
      while (hardTotalTrainer(&score)) {
        if (score.total > 0) {
          printf("\n--- Results ---\n");
          printf("Score: %d / %d\n", score.correct, score.total);
          printf("Accuracy: %.1f%%\n\n",
                 (float)score.correct / score.total * 100);
        }
      };
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
