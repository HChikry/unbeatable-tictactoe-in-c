#ifndef SAVING_GAMEPLAYS_H
#define SAVING_GAMEPLAYS_H

#include <stdbool.h>

#include "../common/common.h"

GameplayNode *SaveTheMove(GameplayNode **top, int new_move);

int GetNextGameplayTitleNumber(int game_mode_choice);

int SaveGameplayIntoFile(GameplayNode *top, int game_mode,
                         const char *game_title, bool is_user_played_first);

void DeleteTheGameplay(GameplayNode **top);

int GetGameplayModeName(int game_mode, char *game_mode_name);
int GetTitleFileName(char *titles_file_name, int game_mode);
int GetMovesFileName(char *moves_file_name, int game_mode);
int GetTempTitleFileName(char *temp_titles_file_name, int game_mode);
int GetTempMovesFileName(char *temp_moves_file_name, int game_mode);

int DeleteSavedGameplays(GameplayNumbers saved_gameplays_number,
                         int titles_count, int gameplay_mode);

#endif