#include "basicStrategy.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Trainer(int (*trainerFunction)(Score *score, Settings *settings),
             Settings *settings) {
  Score score = {0, 0};
  srand(time(NULL));
  while (trainerFunction(&score, settings)) {
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

  // Open settings and save settings to struct inside main()
  FILE *settingsFilePointer;
  settingsFilePointer = fopen("settings.txt", "r");
  if (settingsFilePointer == NULL) {
    printf("Could not load settings.\n");
    return 1;
  }
  Settings settings;
  settings.doubleAfterSplit = fgetc(settingsFilePointer);
  settings.h17OrS17 = fgetc(settingsFilePointer);
  Settings *ptrSettings = &settings;
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
      Trainer(pairSplittingTrainer, ptrSettings);
      break;
    case '2':
      Trainer(softTotalTrainer, ptrSettings);
      break;
    case '3':
      // Trainer(hardTotalTrainer);
      break;
    case '4':
      do {

        printf("+-----------------------------------+\n");
        printf("|       Basic Strategy Trainer      |\n");
        printf("|-----------------------------------|\n");
        printf("|             Settings              |\n");
        printf("|-----------------------------------|\n");
        printf("|  1. Double After Split: %c         |\n",
               ptrSettings->doubleAfterSplit);
        printf("|  2. Hit-17 or Stand-17: %c-17      |\n",
               ptrSettings->h17OrS17);
        printf("|  0. Save and Exit                 |\n");
        printf("|-----------------------------------|\n");
        printf("| Please enter an option from the   |\n");
        printf("| main menu                         |\n");
        printf("+-----------------------------------+\n");

        scanf(" %c", &settingsOption);

        // Toggle settings
        switch (settingsOption) {
        case '1':
          if (ptrSettings->doubleAfterSplit == 'Y') {
            ptrSettings->doubleAfterSplit = 'N';
          } else {
            ptrSettings->doubleAfterSplit = 'Y';
          }
          break;
        case '2':
          if (ptrSettings->h17OrS17 == 'H') {
            ptrSettings->h17OrS17 = 'S';
          } else {
            ptrSettings->h17OrS17 = 'H';
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
        fputc(ptrSettings->doubleAfterSplit, settingsFilePointer);
        fputc(ptrSettings->h17OrS17, settingsFilePointer);
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
