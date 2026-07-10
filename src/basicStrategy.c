#include "../include/basicStrategy.h"
#include "../include/init_scr.h"
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Trainer loader:
// Takes trainer function (pairSplittingTrainer, softTotalTrainer,
// hardTotalTrainer).
// Takes pointer to settings struct Runs trainer function
// with ability to read settings to check for correct answers
static void Trainer(WINDOW *window,
                    int (*trainerFunction)(WINDOW *win, Score *score,
                                           Settings *settings),
                    Settings *settings) {
  Score score = {0, 0};
  while (trainerFunction(window, &score, settings)) {
    // Print results
    if (score.total > 0) {
      mvwprintw(window, SCREEN_LINE_5, SCREEN_MARGIN, "--- Results ---");
      mvwprintw(window, SCREEN_LINE_6, SCREEN_MARGIN, "Score: %d / %d",
                score.correct, score.total);
      mvwprintw(window, SCREEN_LINE_7, SCREEN_MARGIN, "Accuracy: %.1f%%",
                (float)score.correct / score.total * 100);
      mvwprintw(window, 19, 20, "Press any key to continue");
      wgetch(window);
    }
  };
}

// Options for printMenuBar
typedef enum {
  HIGHLIGHT_MAIN_MENU = 0,
  HIGHLIGHT_PAIR_SPLITTING = 1,
  HIGHLIGHT_SOFT_TOTALS = 2,
  HIGHTLIGHT_HARD_TOTALS = 3,
  HIGHLIGHT_SETTINGS = 4
} MenuHighlight;

// Print Highlighted Toggled Menu
static void printMenuBar(WINDOW *window, int MenuHighlight,
                         const char *exitLabel) {
  static const struct {
    int x;
    const char *menuLabel;
  } MenuLabel[] = {
      {WIDTH_FROM_TOP_LEFT_MAIN_MENU, "Main Menu"},
      {WIDTH_FROM_TOP_LEFT_PAIR_SPLITTING, "(1)Pair Splittings"},
      {WIDTH_FROM_TOP_LEFT_SOFT_TOTALS, "(2)Soft Totals"},
      {WIDTH_FROM_TOP_LEFT_HARD_TOTALS, "(3)Hard Totals"},
      {WIDTH_FROM_TOP_LEFT_SETTINGS, "(4)Settings"},
  };
  const int numberOfMenuLabels = sizeof(MenuLabel) / sizeof(MenuLabel[0]);

  werase(window);
  box(window, 0, 0);

  for (int i = 0; i < numberOfMenuLabels; i++) {
    if (i == MenuHighlight) {
      wattron(window, A_STANDOUT);
    }
    mvwprintw(window, MENU_MARGIN, MenuLabel[i].x, "%s",
              MenuLabel[i].menuLabel);
    if (i == MenuHighlight) {
      wattroff(window, A_STANDOUT);
    }
  }
  mvwprintw(window, MENU_MARGIN, WIDTH_FROM_TOP_LEFT_EXIT, "%s", exitLabel);
  wrefresh(window);
};

// Read settings.txt file and save it to struct
static void loadSettings(FILE *FilePointer, WINDOW *window,
                         Settings *settings) {
  if (FilePointer != NULL) {
    settings->doubleAfterSplit = fgetc(FilePointer);
    settings->h17OrS17 = fgetc(FilePointer);
  } else {
    // If no settings are found, proceed with defaults
    werase(window);
    mvwprintw(window, SCREEN_MARGIN, SCREEN_LINE_1,
              "Error accessing settings. Proceeding wtih defaults. Press any "
              "key to continue...");
    wgetch(window);
    FilePointer = fopen("settings.txt", "w");
    settings->doubleAfterSplit = 'Y';
    settings->h17OrS17 = 'H';
    fputc(settings->h17OrS17, FilePointer);
    fputc(settings->doubleAfterSplit, FilePointer);
    fclose(FilePointer);
  }
}

int main(void) {
  char menuOption;
  char settingsOption;

  // Initialize ncurses
  initscr();            // Start ncurses mode, creates stdscr
  cbreak();             // Disable line buffering, get input char-by-char
  noecho();             // don't echo typed keys automatically
  keypad(stdscr, TRUE); // enable arrow keys, F-keys, etc.
  curs_set(0);          // hides the terminal cursor

  // Random seed
  srand(time(NULL));

  // Main menu
  do {
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // Menu bar area: border(1) + menu row(1) + border(1) = 3 rows, starting at
    // y=2
    int menuTop = 2;
    int menuHeight = 3;

    WINDOW *menuWindow = newwin(menuHeight + 2, xMax - 4, menuTop, 2);
    box(menuWindow, 0, 0);

    printMenuBar(menuWindow, HIGHLIGHT_MAIN_MENU, "(0)Exit");

    // Screen window: starts right after the menu bar (+1 row gap), fills rest
    // of screen
    int gap = 1;
    int screenTop = menuTop + menuHeight + gap;
    int screenHt = (yMax - 2) - screenTop; // leave 2-row margin at the bottom

    // Initialize window and print main menu screen
    WINDOW *screenWindow = newwin(screenHt - 2, xMax - 4, screenTop, 2);
    box(screenWindow, 0, 0);

    mvwprintw(screenWindow, SCREEN_LINE_1, SCREEN_MARGIN,
              "Welcome to the BlackJack Basic Strategy TUI Trainer!");
    mvwprintw(
        screenWindow, SCREEN_LINE_2, SCREEN_MARGIN,
        "Press the key of the (H)ighlighted character to go to that menu");
    mvwprintw(screenWindow, SCREEN_LINE_3, SCREEN_MARGIN,
              "(1)Pair Splitting Trainer");
    mvwprintw(screenWindow, SCREEN_LINE_4, SCREEN_MARGIN,
              "(2)Soft Totals Trainer");
    mvwprintw(screenWindow, SCREEN_LINE_5, SCREEN_MARGIN,
              "(3)Hard Totals Trainer");
    mvwprintw(screenWindow, SCREEN_LINE_6, SCREEN_MARGIN, "(4)Settings");
    mvwprintw(screenWindow, SCREEN_LINE_7, SCREEN_MARGIN, "(0)Exit");

    wrefresh(menuWindow);
    wrefresh(screenWindow);

    // Open settings and save settings to struct inside main()
    FILE *settingsFilePointer;
    Settings settings;
    Settings *ptrSettings = &settings;
    settingsFilePointer = fopen("settings.txt", "r");
    loadSettings(settingsFilePointer, screenWindow, &settings);
    fclose(settingsFilePointer);

    menuOption = wgetch(screenWindow);

    // Trainer options
    switch (menuOption) {
    case '1':
      printMenuBar(menuWindow, HIGHLIGHT_PAIR_SPLITTING, "(Q)uit");
      Trainer(screenWindow, pairSplittingTrainer, ptrSettings);
      break;
    case '2':
      printMenuBar(menuWindow, HIGHLIGHT_SOFT_TOTALS, "(Q)uit");
      Trainer(screenWindow, softTotalTrainer, ptrSettings);
      break;
    case '3':
      printMenuBar(menuWindow, HIGHTLIGHT_HARD_TOTALS, "(Q)uit");
      Trainer(screenWindow, hardTotalTrainer, ptrSettings);
      break;
    case '4':
      do {
        // Update Menu Bar
        printMenuBar(menuWindow, HIGHLIGHT_SETTINGS, "(0)Save and Exit");

        // Wipe screen for settings menu
        werase(screenWindow);
        box(screenWindow, 0, 0);
        wrefresh(screenWindow);

        // Display initial settings
        if (ptrSettings->doubleAfterSplit == 'Y') {
          mvwprintw(screenWindow, SCREEN_LINE_1, SCREEN_MARGIN,
                    "1. Double After Split Enabled? [ Yes ]");
        } else {
          mvwprintw(screenWindow, SCREEN_LINE_1, SCREEN_MARGIN,
                    "1. Double After Split Enabled? [ No  ]");
        }

        if (ptrSettings->h17OrS17 == 'H') {
          mvwprintw(screenWindow, SCREEN_LINE_2, SCREEN_MARGIN,
                    "2. Hit-17 or Stand-17? [  Hit  ]");
        } else {
          mvwprintw(screenWindow, SCREEN_LINE_2, SCREEN_MARGIN,
                    "2. Hit-17 or Stand-17? [ Stand ]");
        }
        mvwprintw(screenWindow, SCREEN_LINE_3, SCREEN_MARGIN,
                  "0. Save and Exit");

        // Toggle settings
        switch (settingsOption = wgetch(screenWindow)) {
        case '1':
          if (ptrSettings->doubleAfterSplit == 'Y') {
            ptrSettings->doubleAfterSplit = 'N';
            mvwprintw(screenWindow, SCREEN_LINE_1, SCREEN_MARGIN,
                      "1. Double After Split Enabled? [ No  ]");
          } else {
            ptrSettings->doubleAfterSplit = 'Y';
            mvwprintw(screenWindow, SCREEN_LINE_1, SCREEN_MARGIN,
                      "1. Double After Split Enabled? [ Yes ]");
          }
          break;
        case '2':
          if (ptrSettings->h17OrS17 == 'H') {
            ptrSettings->h17OrS17 = 'S';
            mvwprintw(screenWindow, SCREEN_LINE_2, SCREEN_MARGIN,
                      "2. Hit-17 or Stand-17? [ Stand ]");
          } else {
            ptrSettings->h17OrS17 = 'H';
            mvwprintw(screenWindow, SCREEN_LINE_2, SCREEN_MARGIN,
                      "2. Hit-17 or Stand-17? [  Hit  ]");
          }
          break;
        case '0':
          break;
        default:
          mvwprintw(screenWindow, SCREEN_LINE_4, 30,
                    "Please enter a valid option. Press any key to continue.");
          settingsOption = wgetch(screenWindow);
          mvwprintw(screenWindow, SCREEN_LINE_4, 30,
                    "                           ");
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
        fclose(settingsFilePointer);
        break;
      }
      break;
    case '0':
      break;
    default:
      mvwprintw(screenWindow, SCREEN_LINE_5, 15, "Invalid input");
      break;
    }

    // Reset to main menu on next loop
    delwin(menuWindow);
    delwin(screenWindow);
  } while (menuOption != '0');

  endwin();

  return 0;
}
