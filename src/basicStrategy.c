#include "../include/basicStrategy.h"
#include "../include/init_scr.h"
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Trainer(WINDOW *window,
             int (*trainerFunction)(WINDOW *win, Score *score,
                                    Settings *settings),
             Settings *settings) {
  Score score = {0, 0};
  srand(time(NULL));
  while (trainerFunction(window, &score, settings)) {
    if (score.total > 0) {
      mvwprintw(window, 11, 4, "--- Results ---");
      mvwprintw(window, 13, 4, "Score: %d / %d", score.correct, score.total);
      mvwprintw(window, 15, 4, "Accuracy: %.1f%%",
                (float)score.correct / score.total * 100);
      mvwprintw(window, 19, 20, "Press any key to continue");
      wgetch(window);
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

    // Menu bar area: border(1) + menu row(1) + border(1) = 3 rows, starting at
    // y=2
    int menuTop = 2;
    int menuHeight = 3;

    WINDOW *menuWindow = newwin(menuHeight, xMax - 4, menuTop, 2);
    box(menuWindow, 0, 0);
    // ... menu bar mvwprintw calls stay the same, all at row 0 ...

    wattron(menuWindow, A_STANDOUT);
    mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_MAIN_MENU, "Main Menu");
    wattroff(menuWindow, A_STANDOUT);
    mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_PAIR_SPLITTING,
              "(1)Pair Splitting");
    mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_SOFT_TOTALS, "(2)Soft Totals");
    mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_HARD_TOTALS, "(3)Hard Totals");
    mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_SETTINGS, "(4)Settings");
    mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_EXIT, "(0)Exit");

    // Screen window: starts right after the menu bar (+1 row gap), fills rest
    // of screen
    int gap = 1;
    int screenTop = menuTop + menuHeight + gap;
    int screenHt = (yMax - 2) - screenTop; // leave 2-row margin at the bottom

    // Initialize window and main menu
    WINDOW *screenWindow = newwin(screenHt, xMax - 4, screenTop, 2);
    box(screenWindow, 0, 0);

    mvwprintw(screenWindow, 3, 5,
              "Welcome to the BlackJack Basic Strategy TUI Trainer!");

    wrefresh(menuWindow);
    wrefresh(screenWindow);

    menuOption = wgetch(menuWindow);

    // Trainer options
    switch (menuOption) {
    case '1':
      werase(menuWindow);
      box(menuWindow, 0, 0);
      mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_MAIN_MENU, "Main Menu");
      wattron(menuWindow, A_STANDOUT);
      mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_PAIR_SPLITTING,
                "(1)Pair Splitting");
      wattroff(menuWindow, A_STANDOUT);
      mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_SOFT_TOTALS,
                "(2)Soft Totals");
      mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_HARD_TOTALS,
                "(3)Hard Totals");
      mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_SETTINGS, "(4)Settings");
      mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_EXIT, "(Q)uit");
      wrefresh(menuWindow);
      Trainer(screenWindow, pairSplittingTrainer, ptrSettings);
      break;
    case '2':
      mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_MAIN_MENU, "Main Menu");
      mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_PAIR_SPLITTING,
                "(1)Pair Splitting");
      wattron(menuWindow, A_STANDOUT);
      mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_SOFT_TOTALS,
                "(2)Soft Totals");
      wattroff(menuWindow, A_STANDOUT);
      mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_HARD_TOTALS,
                "(3)Hard Totals");
      mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_SETTINGS, "(4)Settings");
      mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_EXIT, "(0)Exit");
      // Trainer(softTotalTrainer, ptrSettings);
      break;
    case '3':
      mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_MAIN_MENU, "Main Menu");
      mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_PAIR_SPLITTING,
                "(1)Pair Splitting");
      mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_SOFT_TOTALS,
                "(2)Soft Totals");
      wattron(menuWindow, A_STANDOUT);
      mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_HARD_TOTALS,
                "(3)Hard Totals");
      wattroff(menuWindow, A_STANDOUT);
      mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_SETTINGS, "(4)Settings");
      mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_EXIT, "(0)Exit");
      // Trainer(hardTotalTrainer, ptrSettings);
      break;
    case '4':
      do {
        // Update Menu Bar
        werase(menuWindow);
        box(menuWindow, 0, 0);
        mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_MAIN_MENU, "Main Menu");
        mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_PAIR_SPLITTING,
                  "(1)Pair Splitting");
        mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_SOFT_TOTALS,
                  "(2)Soft Totals");
        mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_HARD_TOTALS,
                  "(3)Hard Totals");
        wattron(menuWindow, A_STANDOUT);
        mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_SETTINGS, "(4)Settings");
        wattroff(menuWindow, A_STANDOUT);
        mvwprintw(menuWindow, 0, WIDTH_FROM_TOP_LEFT_EXIT, "(0)Save and Exit");
        wrefresh(menuWindow);

        // Wipe screen for settings menu
        werase(screenWindow);
        box(screenWindow, 0, 0);
        wrefresh(screenWindow);

        // Display initial settings
        if (ptrSettings->doubleAfterSplit == 'Y') {
          mvwprintw(screenWindow, 3, 4,
                    "1. Double After Split Enabled? [ Yes ]");
        } else {
          mvwprintw(screenWindow, 3, 4,
                    "1. Double After Split Enabled? [ No  ]");
        }

        if (ptrSettings->h17OrS17 == 'H') {
          mvwprintw(screenWindow, 5, 4, "2. Hit-17 or Stand-17? [  Hit  ]");
        } else {
          mvwprintw(screenWindow, 5, 4, "2. Hit-17 or Stand-17? [ Stand ]");
        }

        // Toggle settings
        switch (settingsOption = wgetch(screenWindow)) {
        case '1':
          if (ptrSettings->doubleAfterSplit == 'Y') {
            ptrSettings->doubleAfterSplit = 'N';
            mvwprintw(screenWindow, 3, 4,
                      "1. Double After Split Enabled? [ No  ]");
          } else {
            ptrSettings->doubleAfterSplit = 'Y';
            mvwprintw(screenWindow, 3, 4,
                      "1. Double After Split Enabled? [ Yes ]");
          }
          break;
        case '2':
          if (ptrSettings->h17OrS17 == 'H') {
            ptrSettings->h17OrS17 = 'S';
            mvwprintw(screenWindow, 5, 4, "2. Hit-17 or Stand-17? [ Stand ]");
          } else {
            ptrSettings->h17OrS17 = 'H';
            mvwprintw(screenWindow, 5, 4, "2. Hit-17 or Stand-17? [  Hit  ]");
          }
          break;
        case '0':
          break;
        default:
          mvwprintw(screenWindow, 10, 15, "Please enter a valid option");
          settingsOption = wgetch(screenWindow);
          mvwprintw(screenWindow, 10, 15, "                           ");
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
      mvwprintw(screenWindow, 10, 15, "Invalid input");
      break;
    }

    // Reset to main menu
    delwin(menuWindow);
    delwin(screenWindow);
  } while (menuOption != '0');

  endwin();

  return 0;
}
