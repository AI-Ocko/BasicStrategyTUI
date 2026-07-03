#include "../include/basicStrategy.h"
#include "../include/init_scr.h"
#include <curses.h>
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
  Settings settings;
  settingsFilePointer = fopen("settings.txt", "r");
  if (settingsFilePointer == NULL) {
    printf("No settings found. Setting default settings.\n");
    settings.doubleAfterSplit = 'Y';
    settings.h17OrS17 = 'H';
    settingsFilePointer = fopen("settings.txt", "w");
    if (settingsFilePointer != NULL) {
      fputc(settings.doubleAfterSplit, settingsFilePointer);
      fputc(settings.h17OrS17, settingsFilePointer);
      fclose(settingsFilePointer);
    } else {
      printf("*Gulp* Uh...Boss? You might want to take a look at this\n");
      return 1;
    }
  } else {
    // Save settings.txt information to local struct pointer
    settings.doubleAfterSplit = fgetc(settingsFilePointer);
    settings.h17OrS17 = fgetc(settingsFilePointer);
    fclose(settingsFilePointer);
  }

  Settings *ptrSettings = &settings;

  // Initialize ncurses
  initscr();            // Start ncurses mode, creates stdscr
  cbreak();             // Disable line buffering, get input char-by-char
  noecho();             // don't echo typed keys automatically
  keypad(stdscr, TRUE); // enable arrow keys, F-keys, etc.
  curs_set(0);          // hides the terminal cursor

  // Main menu
  do {

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // Initialize window and main menu
    WINDOW *win = newwin(yMax / 2, xMax / 2, yMax / 4, xMax / 4);
    box(win, 0, 0);
    wattron(win, A_STANDOUT);
    mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_MAIN_MENU, "Main Menu");
    wattroff(win, A_STANDOUT);
    mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_PAIR_SPLITTING, "(1)Pair Splitting");
    mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_SOFT_TOTALS, "(2)Soft Totals");
    mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_HARD_TOTALS, "(3)Hard Totals");
    mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_SETTINGS, "(4)Settings");
    mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_EXIT, "(0)Exit");

    wrefresh(win);
    menuOption = wgetch(win);

    // Trainer options
    switch (menuOption) {
    case '1':
      PrintMenuScreen(win, menuOption);
      wrefresh(win);
      // Trainer(pairSplittingTrainer, ptrSettings);
      break;
      PrintMenuScreen(win, menuOption);
      // Trainer(softTotalTrainer, ptrSettings);
      break;
    case '3':
      PrintMenuScreen(win, menuOption);
      // Trainer(hardTotalTrainer, ptrSettings);
      break;
    case '4':
      PrintMenuScreen(win, menuOption);
      // Settings menu
      do {

        // printf("+-----------------------------------+\n");
        // printf("|       Basic Strategy Trainer      |\n");
        // printf("|-----------------------------------|\n");
        // printf("|             Settings              |\n");
        // printf("|-----------------------------------|\n");
        // printf("|  1. Double After Split: %c         |\n",
        //        ptrSettings->doubleAfterSplit);
        // printf("|  2. Hit-17 or Stand-17: %c-17      |\n",
        //        ptrSettings->h17OrS17);
        // printf("|  0. Save and Exit                 |\n");
        // printf("|-----------------------------------|\n");
        // printf("| Please enter an option from the   |\n");
        // printf("| main menu                         |\n");
        // printf("+-----------------------------------+\n");

        settingsOption = wgetch(win);

        // scanf(" %c", &settingsOption);

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
          wprintw(win, "Please enter a valid option.\n");
          break;
        }
      } while (settingsOption != '0');

      // Repoen settings.txt and save the inputs the user gave
      settingsFilePointer = fopen("settings.txt", "w");
      if (settingsFilePointer != NULL) {
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

    // Reset to main menu
    delwin(win);

  } while (menuOption != '0');

  endwin();

  return 0;
}
