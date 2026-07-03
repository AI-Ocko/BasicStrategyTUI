#include "../include/basicStrategy.h"
#include "../include/init_scr.h"
#include <ctype.h>
#include <curses.h>
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

void PrintMenuScreen(WINDOW *win, char menuOption) {
  switch (menuOption) {
  case '1':
    mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_MAIN_MENU, "Main Menu");
    wattron(win, A_STANDOUT);
    mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_PAIR_SPLITTING, "(1)Pair Splitting");
    wattroff(win, A_STANDOUT);
    mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_SOFT_TOTALS, "(2)Soft Totals");
    mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_HARD_TOTALS, "(3)Hard Totals");
    mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_SETTINGS, "(4)Settings");
    mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_EXIT, "(0)Exit");
    wrefresh(win);
    // Trainer(pairSplittingTrainer, ptrSettings);
    break;
  case '2':
    mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_MAIN_MENU, "Main Menu");
    mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_PAIR_SPLITTING, "(1)Pair Splitting");
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
    mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_PAIR_SPLITTING, "(1)Pair Splitting");
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
    mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_PAIR_SPLITTING, "(1)Pair Splitting");
    mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_SOFT_TOTALS, "(2)Soft Totals");
    mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_HARD_TOTALS, "(3)Hard Totals");
    wattron(win, A_STANDOUT);
    mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_SETTINGS, "(4)Settings");
    wattroff(win, A_STANDOUT);
    mvwprintw(win, 0, WIDTH_FROM_TOP_LEFT_EXIT, "(0)Exit");
  }
}
