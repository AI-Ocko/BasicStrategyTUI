#include "../include/basicStrategy.h"
#include "../include/init_scr.h"
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Trainer(WINDOW *win,
             int (*trainerFunction)(WINDOW *win, Score *score,
                                    Settings *settings),
             Settings *settings) {
  Score score = {0, 0};
  srand(time(NULL));
  while (trainerFunction(win, &score, settings)) {
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
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_MAIN_MENU, "Main Menu");
      wattron(win, A_STANDOUT);
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_PAIR_SPLITTING,
                "(1)Pair Splitting");
      wattroff(win, A_STANDOUT);
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_SOFT_TOTALS, "(2)Soft Totals");
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_HARD_TOTALS, "(3)Hard Totals");
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_SETTINGS, "(4)Settings");
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_EXIT, "(0)Exit");
      Trainer(win, pairSplittingTrainer, ptrSettings);
      break;
    case '2':
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_MAIN_MENU, "Main Menu");
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_PAIR_SPLITTING,
                "(1)Pair Splitting");
      wattron(win, A_STANDOUT);
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_SOFT_TOTALS, "(2)Soft Totals");
      wattroff(win, A_STANDOUT);
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_HARD_TOTALS, "(3)Hard Totals");
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_SETTINGS, "(4)Settings");
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_EXIT, "(0)Exit");
      // Trainer(softTotalTrainer, ptrSettings);
      break;
    case '3':
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_MAIN_MENU, "Main Menu");
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_PAIR_SPLITTING,
                "(1)Pair Splitting");
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_SOFT_TOTALS, "(2)Soft Totals");
      wattron(win, A_STANDOUT);
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_HARD_TOTALS, "(3)Hard Totals");
      wattroff(win, A_STANDOUT);
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_SETTINGS, "(4)Settings");
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_EXIT, "(0)Exit");
      // Trainer(hardTotalTrainer, ptrSettings);
      break;
    case '4':
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_MAIN_MENU, "Main Menu");
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_PAIR_SPLITTING,
                "(1)Pair Splitting");
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_SOFT_TOTALS, "(2)Soft Totals");
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_HARD_TOTALS, "(3)Hard Totals");
      wattron(win, A_STANDOUT);
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_SETTINGS, "(4)Settings");
      wattroff(win, A_STANDOUT);
      mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_EXIT, "(0)Save and Exit");
      // Settings menu
      do {

        // Display initial settings
        if (ptrSettings->doubleAfterSplit == 'Y') {
          mvwprintw(win, 3, 4, "1. Double After Split Enabled? [ Yes ]");
        } else {
          mvwprintw(win, 3, 4, "1. Double After Split Enabled? [ No  ]");
        }

        if (ptrSettings->h17OrS17 == 'H') {
          mvwprintw(win, 5, 4, "2. Hit-17 or Stand-17? [  Hit  ]");
        } else {
          mvwprintw(win, 5, 4, "2. Hit-17 or Stand-17? [ Stand ]");
        }

        // Toggle settings
        switch (settingsOption = wgetch(win)) {
        case '1':
          if (ptrSettings->doubleAfterSplit == 'Y') {
            ptrSettings->doubleAfterSplit = 'N';
            mvwprintw(win, 3, 4, "1. Double After Split Enabled? [ No  ]");
          } else {
            ptrSettings->doubleAfterSplit = 'Y';
            mvwprintw(win, 3, 4, "1. Double After Split Enabled? [ Yes ]");
          }
          break;
        case '2':
          if (ptrSettings->h17OrS17 == 'H') {
            ptrSettings->h17OrS17 = 'S';
            mvwprintw(win, 5, 4, "2. Hit-17 or Stand-17? [ Stand ]");
          } else {
            ptrSettings->h17OrS17 = 'H';
            mvwprintw(win, 5, 4, "2. Hit-17 or Stand-17? [  Hit  ]");
          }
          break;
        case '0':
          break;
        default:
          mvwprintw(win, 10, 15, "Please enter a valid option");
          settingsOption = wgetch(win);
          mvwprintw(win, 10, 15, "                           ");
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
      mvwprintw(win, 10, 15, "Invalid input");
      break;
    }

    // Reset to main menu
    delwin(win);
  } while (menuOption != '0');

  endwin();

  return 0;
}
