#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/common/common.h"
#include "../include/common/form.h"
#include "../include/common/graphic.h"
#include "../include/friends_gameplay/friends_gameplay.h"
#include "../include/game_play/game_play.h"
#include "../include/game_play/saving_gameplays.h"

void PlayingAgainstComputer(void);
void PlayingWithFriends(void);
void SavedGameplayChoice(void);

int main(void) {
  WelcomePage();
  int menu_choice = 0;

  while (menu_choice != 4) {
    menu_choice = MainMenuPage();

    if (1 == menu_choice) PlayingAgainstComputer();
    if (2 == menu_choice) PlayingWithFriends();
    if (3 == menu_choice) SavedGameplayChoice();
  }

  TerminalCleaner();
  LogoPrinter();
  puts("\n\n+++++++++++++++++++++++ MESSAGE: +++++++++++++++++++++++");
  puts("|   Thank you for playing the game, see you soon! :)   |");
  puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
  return 0;
}  // end of the main

void PlayingAgainstComputer(void) {
  GameplayNode *head = NULL;  // linked list to store gameplay moves
  bool should_user_play = false;
  int game_mode_choice = 0;
  int menu_choice = 2;

  do {
    DeleteTheGameplay(&head);
    if (2 == menu_choice) game_mode_choice = GetGameplayMode();
    should_user_play = IsUserWillPlayFirst();

    char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int game_result =
        GamePlay(board, game_mode_choice, should_user_play, &head);
    WinnerMessagePrinter(game_mode_choice, game_result);
    menu_choice = EndGameMenuPage(board);
  } while (1 == menu_choice || 2 == menu_choice);

  if (4 == menu_choice) {
    DeleteTheGameplay(&head);
    return;
  }

  // Saving The Gameplay
  int game_title_choice = 0;
  TerminalCleaner();
  LogoPrinter();
  game_title_choice = GameTitleMenuPage();

  TerminalCleaner();
  LogoPrinter();
  char gameplay_title[MAX_GAMEPLAY_TITLE_LENGTH + 2] = {0};

  if (1 == game_title_choice) {
    // Manually Adding the Title of the Save
    GetGameTitle(gameplay_title);
  } else {
    // Automatically Adding the Title of the Save
    int save_number = GetNextGameplayTitleNumber(game_mode_choice);
    snprintf(gameplay_title, MAX_GAMEPLAY_TITLE_LENGTH, "%s %0.d",
             DEFAULT_SAVED_GAMEPLAY_NAME, save_number);
  }

  if (SaveGameplayIntoFile(head, game_mode_choice, gameplay_title,
                           should_user_play)) {
    SavedGameMessage(gameplay_title, false);
    // puts("\nerror in SaveTheGameplay");
    // return 1;`
  } else {
    SavedGameMessage(gameplay_title, true);
  }

  DeleteTheGameplay(&head);
  return;
}  // end of first choice

void PlayingWithFriends(void) {
  int number_of_players = GetNumberOfPlayers();
  if (number_of_players > 2) DisplayMultiplePlayerRules();

  char board[(number_of_players + 1) * (number_of_players + 1)];
  for (size_t i = 0; i < (number_of_players + 1) * (number_of_players + 1);
       i++) {
    board[i] = '0';
  }

  char *players_rank = MultiplePlayerGameplay(board, number_of_players);
  MultiplePlayerGameSummary(board, players_rank, number_of_players);
  free(players_rank);

  char c[2];
  do {
    printf(" press enter to exist....");
    fgets(c, 2, stdin);
  } while (c[0] != '\n');
}

void SavedGameplayChoice(void) {
  // 1: show game play    and    2: delete gameplay
  int saved_gameplay_action = GetSavedGameplayAction();
  int gameplay_mode = GetGameplayMode();

  TerminalCleaner();
  LogoPrinter();
  int titles_count = PrintSavedGameplayTitles(gameplay_mode);
  if (0 == titles_count) return;

  GameplayNumbers choosen_gameplays =
      GetSavedGameplaysNumber(gameplay_mode, titles_count);

  if (!choosen_gameplays.list) {
    free(choosen_gameplays.list);
    return;
  }

  if (saved_gameplay_action == 1) {
    PrintSavedGameplayBoards(choosen_gameplays, gameplay_mode, titles_count);
  }

  if (saved_gameplay_action == 2) {
    DeleteSavedGameplays(choosen_gameplays, titles_count, gameplay_mode);
    SuccessfulMessagePrinter();
  }

  free(choosen_gameplays.list);
}
