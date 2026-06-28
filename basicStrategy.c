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
  char menu_option;
  char settings_option;

  do {
    printf("+-----------------------------------+\n");
    printf("|       Basic Strategy Trainer      |\n");
    printf("|-----------------------------------|\n");
    printf("|             Main Menu             |\n");
    printf("|-----------------------------------|\n");
    printf("|  1. Pair Splitting                |\n");
    printf("|  2. Soft Totals                   |\n");
    printf("|  3. Hard Totals                   |\n");
    printf("|  4. Options                       |\n");
    // printf("|  5. Full Game Practice            |\n");
    printf("|  0. Exit                          |\n");
    printf("|-----------------------------------|\n");
    printf("| Please enter an option from the   |\n");
    printf("| main menu                         |\n");
    printf("+-----------------------------------+\n");
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
    case '4':
      FILE *settingsFilePointer;

      // Open the actual settings.txt for settings persistence
      settingsFilePointer = fopen("settings.txt", "r");
      if (settingsFilePointer == NULL) {
        printf("Error accessing settings. Please fix");
        break;
      }

      // Debug print statement
      // printf("Settings Accessed\n");

      // Accessing doubleAfterSplitEnabled
      char doubleAfterSplitEnabled = fgetc(settingsFilePointer);

      fclose(settingsFilePointer);

      do {

        printf("+-----------------------------------+\n");
        printf("|       Basic Strategy Trainer      |\n");
        printf("|-----------------------------------|\n");
        printf("|             Settings              |\n");
        printf("|-----------------------------------|\n");
        printf("|  1. Double After Split: %c         |\n",
               doubleAfterSplitEnabled);
        printf("|  0. Main Menu                     |\n");
        printf("|-----------------------------------|\n");
        printf("| Please enter an option from the   |\n");
        printf("| main menu                         |\n");
        printf("+-----------------------------------+\n");

        scanf(" %c", &settings_option);

        switch (settings_option) {
        case '1':
          if (doubleAfterSplitEnabled == 'Y') {
            doubleAfterSplitEnabled = 'N';
          } else {
            doubleAfterSplitEnabled = 'Y';
          }
          break;
        default:
          printf("I don't know how we got here\n");
          break;
        }
      } while (settings_option != '0');

      // Repoen settings.txt and write the option
      settingsFilePointer = fopen("settings.txt", "w");
      if (settingsFilePointer != NULL) {
        fputc(doubleAfterSplitEnabled, settingsFilePointer);
        fclose(settingsFilePointer);
      }
      break;

    case '0':
      break;
    default:
      printf("Invalid input\n");
      break;
    }
  } while (menu_option != '0');

  return 0;
}
