#ifndef BASICSTRATEGY_H
#define BASICSTRATEGY_H

#include <curses.h>

typedef struct {
  int correct;
  int total;

} Score;

typedef struct {
  char doubleAfterSplit; //   Y/N
  char h17OrS17;         //   H/S
} Settings;

typedef enum {
  H = 0,
  S = 1,
  D = 2,
  Ds = 3,
  N = 4,
  Y = 5,
  YN = 6,
  Surr = 7

} Action;

int pairSplittingTrainer(WINDOW *window, Score *score, Settings *settings);
int softTotalTrainer(WINDOW *window, Score *score, Settings *settings);
int hardTotalTrainer(WINDOW *window, Score *score, Settings *settings);

// Trainer Helper Functions
int dealDealerUpCard(void);
void printDealerUpCard(WINDOW *window, int dealerUpCard);
char answerToChar(Action a, Settings *settings);
void checkAndScore(WINDOW *window, Score *score, char correctAnswer,
                   char userAnswer);

extern Action HardTotalsH17[10][10];
extern Action HardTotalsS17[10][10];
extern Action SoftTotalsH17[8][10];
extern Action SoftTotalsS17[8][10];
extern Action PairSplitting[10][10];
extern int surrender[3][10];

#endif
