#ifndef GRAPHIC_H
#define GRAPHIC_H

// Behind the scenes
void TerminalCleaner(void);

// Messages
void LogoPrinter(void);
void WelcomePage(void);
void ErrorMessagePrinter(void);
void GameIntro(void);

void WinnerMessagePrinter(int game_mode, int game_result);

int PickRandomlyWhoWillPlayFirst(void);

void BoardPrinter(char *board, char computer_playing_symbol);


#endif