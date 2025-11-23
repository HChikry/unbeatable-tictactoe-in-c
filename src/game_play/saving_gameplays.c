/*
  I implemented this saving feature using linked list only to implement this
  knowledge. I'm fully aware that the most efficient implementation of this
  feature in this case will be using an array.
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../include/common/common.h"
#include "../../include/common/form.h"

GameplayNode *SaveTheMove(GameplayNode **head, int new_move) {
  GameplayNode *node = malloc(sizeof(node));
  if (node == NULL) return NULL;

  snprintf(node->the_move, 2, "%d", new_move);
  node->next = *head;

  *head = node;
  return node;
}

int GetGameplayModeName(int game_mode, char *game_mode_name) {
  switch (game_mode) {
    case EASY_GAME_MODE:
      strncpy(game_mode_name, "easy_gameplays", MAX_GAMEPLAY_MODE_NAME_LENGTH);
      break;

    case NORMAL_GAME_MODE:
      strncpy(game_mode_name, "normal_gameplays",
              MAX_GAMEPLAY_MODE_NAME_LENGTH);
      break;

    case UNBEATABLE_GAME_MODE:
      strncpy(game_mode_name, "unbeatable_gameplays",
              MAX_GAMEPLAY_MODE_NAME_LENGTH);
      break;

    default:
      puts("error in GetGameplayModeName");
      return 1;
  }

  return 0;
}

int GetTitleFileName(char *titles_file_name, int game_mode) {
  if (titles_file_name == NULL) return 1;

  char game_mode_name[MAX_GAMEPLAY_MODE_NAME_LENGTH];
  if (GetGameplayModeName(game_mode, game_mode_name)) return 1;

  snprintf(titles_file_name, MAX_FILE_TITLE_LENGTH,
           "data/app/gameplays/%s_titles.txt", game_mode_name);

  return 0;
}

int GetMovesFileName(char *moves_file_name, int game_mode) {
  if (moves_file_name == NULL) return 1;

  char game_mode_name[MAX_GAMEPLAY_MODE_NAME_LENGTH];
  if (GetGameplayModeName(game_mode, game_mode_name)) return 1;

  snprintf(moves_file_name, MAX_FILE_TITLE_LENGTH,
           "data/app/gameplays/%s_moves.txt", game_mode_name);

  return 0;
}

int GetTempTitleFileName(char *temp_titles_file_name, int game_mode) {
  if (temp_titles_file_name == NULL) return 1;

  char game_mode_name[MAX_GAMEPLAY_MODE_NAME_LENGTH];
  if (GetGameplayModeName(game_mode, game_mode_name)) return 1;

  snprintf(temp_titles_file_name, MAX_FILE_TITLE_LENGTH,
           "data/app/gameplays/temp_%s_titles.txt", game_mode_name);

  return 0;
}

int GetTempMovesFileName(char *temp_moves_file_name, int game_mode) {
  if (temp_moves_file_name == NULL) return 1;

  char game_mode_name[22];
  if (GetGameplayModeName(game_mode, game_mode_name)) return 1;

  snprintf(temp_moves_file_name, MAX_FILE_TITLE_LENGTH,
           "data/app/gameplays/temp_%s_moves.txt", game_mode_name);

  return 0;
}

int GetNextGameplayTitleNumber(int game_mode_choice) {
  FILE *titles_file;
  {
    char titles_file_name[MAX_FILE_TITLE_LENGTH] = {0};
    GetTitleFileName(titles_file_name, game_mode_choice);
    titles_file = fopen(titles_file_name, "r");
  }
  if (titles_file == NULL) return 1;

  int next_title_number = 0;
  char title_match[MAX_GAMEPLAY_TITLE_LENGTH + 2] = {0};

  while (fgets(title_match, MAX_GAMEPLAY_TITLE_LENGTH + 1, titles_file)) {
    if (!strncmp(title_match, DEFAULT_SAVED_GAMEPLAY_NAME,
                 DEFAULT_SAVED_GAMEPLAY_LENGTH)) {
      next_title_number =
          strtol(title_match + DEFAULT_SAVED_GAMEPLAY_LENGTH, NULL, 10) + 1;
    }
  }

  fclose(titles_file);
  return next_title_number;
}

static void saving_moves(FILE *moves_file, GameplayNode *head,
                         bool is_it_first_call) {
  if (head == NULL) return;

  saving_moves(moves_file, head->next, false);
  fprintf(moves_file, "%c", head->the_move[0]);
  if (!is_it_first_call) fputs(", ", moves_file);
}

static int count_number_of_saved_games(FILE *file) {
  if (!file) return -1;
  rewind(file);

  char buffer[MAX_FILE_TITLE_LENGTH + 2] = {0};
  int games_count = 0;
  while (fgets(buffer, MAX_GAMEPLAY_TITLE_LENGTH, file)) {
    if (strlen(buffer) == 1) continue;
    ++games_count;
  }

  return games_count;
}

int SaveGameplayIntoFile(GameplayNode *head, int game_mode,
                         const char *game_title, bool is_user_played_first) {
  char moves_file_name[MAX_FILE_TITLE_LENGTH] = {0};
  char titles_file_name[MAX_FILE_TITLE_LENGTH] = {0};
  GetMovesFileName(moves_file_name, game_mode);
  GetTitleFileName(titles_file_name, game_mode);

  // First file
  FILE *titles_file = fopen(titles_file_name, "a+");
  int number_of_saved_games = count_number_of_saved_games(titles_file);
  fclose(titles_file);

  if (number_of_saved_games >= MAX_SAVED_GAMES) return 1;

  titles_file = fopen(titles_file_name, "a");
  fprintf(titles_file, "%s\n", game_title);
  fclose(titles_file);

  // Second file
  FILE *moves_file = fopen(moves_file_name, "a");

  if (is_user_played_first) {
    fputs("U: ", moves_file);
  } else {
    fputs("C: ", moves_file);
  }

  saving_moves(moves_file, head, true);
  fputs("\n", moves_file);
  fclose(moves_file);

  return 0;
}

void DeleteTheGameplay(GameplayNode **head) {
  if (*head == NULL) return;
  GameplayNode *temp = NULL;

  while ((*head) != NULL) {
    temp = *head;
    *head = (*head)->next;
    free(temp);
  }
}

int DeleteSavedGameplays(GameplayNumbers gameplays_to_delete, int titles_count,
                         int gameplay_mode) {
  char titles_file_name[MAX_FILE_TITLE_LENGTH] = {0};
  char moves_file_name[MAX_FILE_TITLE_LENGTH] = {0};
  GetTitleFileName(titles_file_name, gameplay_mode);
  GetMovesFileName(moves_file_name, gameplay_mode);

  if (titles_count == gameplays_to_delete.list_length) {
    FILE *titles_file = fopen(titles_file_name, "w");
    FILE *moves_file = fopen(moves_file_name, "w");
    fclose(titles_file);
    fclose(moves_file);
    return 0;
  }
  FILE *titles_file = fopen(titles_file_name, "r");
  FILE *moves_file = fopen(moves_file_name, "r");

  char temp_titles_file_name[MAX_FILE_TITLE_LENGTH] = {0};
  GetTempTitleFileName(temp_titles_file_name, gameplay_mode);
  FILE *temp_titles_file = fopen(temp_titles_file_name, "w");

  char temp_moves_file_name[MAX_FILE_TITLE_LENGTH] = {0};
  GetTempMovesFileName(temp_moves_file_name, gameplay_mode);
  FILE *temp_moves_file = fopen(temp_moves_file_name, "w");

  if (!titles_file || !moves_file || !temp_moves_file || !temp_titles_file) {
    puts("error of Opening File in DeleteSavedGameplays");
    return 1;
  }

  char title_buffer[MAX_GAMEPLAY_TITLE_LENGTH] = {0};
  char moves_buffer[MAX_MOVES_LENGTH] = {0};
  int count = 0;
  bool is_game_found = false;

  for (int i = 0; i < titles_count; ++i) {
    is_game_found = false;

    fgets(title_buffer, MAX_GAMEPLAY_TITLE_LENGTH, titles_file);
    fgets(moves_buffer, MAX_MOVES_LENGTH, moves_file);

    if (count < gameplays_to_delete.list_length) {
      for (int j = 0; j < gameplays_to_delete.list_length; ++j) {
        if (i + 1 == gameplays_to_delete.list[j]) {
          is_game_found = true;
          ++count;
          break;
        }
      }
    }

    if (is_game_found) continue;
    fputs(title_buffer, temp_titles_file);
    fputs(moves_buffer, temp_moves_file);
  }

  fclose(titles_file);
  fclose(moves_file);
  fclose(temp_moves_file);
  fclose(temp_titles_file);

  remove(titles_file_name);
  remove(moves_file_name);

  rename(temp_titles_file_name, titles_file_name);
  rename(temp_moves_file_name, moves_file_name);

  return 0;
}