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
  char menuOption;
  char settingsOption;
  char settingsDAS;
  char settingsH17S17;

  // Open settings and save inside main()
  FILE *settingsFilePointer;
  settingsFilePointer = fopen("settings.txt", "r");
  if (settingsFilePointer == NULL) {
    printf("Could not load settings.\n");
    return 1;
  }
  settingsDAS = fgetc(settingsFilePointer);
  settingsH17S17 = fgetc(settingsFilePointer);
  fclose(settingsFilePointer);

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
    scanf(" %c", &menuOption);

    switch (menuOption) {
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
      do {

        printf("+-----------------------------------+\n");
        printf("|       Basic Strategy Trainer      |\n");
        printf("|-----------------------------------|\n");
        printf("|             Settings              |\n");
        printf("|-----------------------------------|\n");
        printf("|  1. Double After Split: %c         |\n", settingsDAS);
        printf("|  2. Hit-17 or Stand-17: %c-17      |\n", settingsH17S17);
        printf("|  0. Save and Exit                 |\n");
        printf("|-----------------------------------|\n");
        printf("| Please enter an option from the   |\n");
        printf("| main menu                         |\n");
        printf("+-----------------------------------+\n");

        scanf(" %c", &settingsOption);

        // Toggle settings
        switch (settingsOption) {
        case '1':
          if (settingsDAS == 'Y') {
            settingsDAS = 'N';
          } else {
            settingsDAS = 'Y';
          }
          break;
        case '2':
          if (settingsH17S17 == 'H') {
            settingsH17S17 = 'S';
          } else {
            settingsH17S17 = 'H';
          }
          break;

        default:
          printf("Please enter a valid option.\n");
          break;
        }
      } while (settingsOption != '0');

      // Repoen settings.txt and save the inputs the user gave
      settingsFilePointer = fopen("settings.txt", "w");
      if (settingsFilePointer != NULL) {
        rewind(settingsFilePointer);
        fputc(settingsDAS, settingsFilePointer);
        fputc(settingsH17S17, settingsFilePointer);
        fclose(settingsFilePointer);
      } else {
        printf("Something went wrong opening settings file\n");
        break;
      }
      break;

    case '0':
      break;
    default:
      printf("Invalid input\n");
      break;
    }
  } while (menuOption != '0');

  return 0;
}
