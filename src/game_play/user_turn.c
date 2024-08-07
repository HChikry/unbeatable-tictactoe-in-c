#include <stdio.h>
#include <unistd.h>

#include "../../include/common/common.h"
#include "../../include/common/err.h"
#include "../../include/common/graphic.h"
#include "../../include/computer_turn/computer_turn.h"
#include "../../include/game_play/game_checkers.h"

int UserTurn(char *board) {
  int board_place_number = 0;
  bool is_function_run_once = false;

  do {
    if (is_function_run_once) {
      ErrorMessagePrinter();
      BoardPrinter(board);
    }

    board_place_number = GetGoodIntegerInput(1, 9);
    is_function_run_once = true;
  } while (board_place_number == 0 || !IsPlaceEmpty(board, board_place_number));

  *(board + board_place_number - 1) = USER_PLAYING_SYMBOL;

  TerminalCleaner();
  LogoPrinter();
  puts("\n\n+++++++++++++++++++++++ MESSAGE: +++++++++++++++++++++++");
  printf(
      "|                 You Played in \033[31;1mPlace %d\033[0m               "
      " |\n",
      board_place_number);
  puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

  BoardPrinter(board);
  sleep(1);
  return board_place_number;
}