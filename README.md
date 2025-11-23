# Unbeatable TicTacToe in C

I made this for fun :)

## About the Game

This a CLI game that is similar to the TicTacToe game you can play in Google search engine. However, it has more features such as playing with your friends up to 5 players. In addition, it has the possibility of saving the gameplays you play against the computer.

## How to Run The Game

1. Download the code of the master branch.
2. Open the program folder in the terminal.
3. Run the game using this command:

-   For MacOS

```
bin/src/mac/./main
```

-   For Windows (not added yet)

```
bin/src/win/./main.exe
```

## Compile The Game (If You Couldn't Run It)

1. You will need to have a gcc compiler installed in your machine.
2. Open the repository folder in the terminal.
3. Compile the game using this command:

-   For MaxOS

```
gcc -o bin/src/mac/main ./src/main.c ./src/computer_turn/unbeatable_mode.c ./src/computer_turn/normal_mode.c ./src/computer_turn/computer_moves.c ./src/computer_turn/computer_turn.c ./src/common/err.c ./src/common/graphic.c ./src/common/form.c ./src/game_play/game_checkers.c ./src/game_play/user_turn.c ./src/game_play/game_play.c ./src/game_play/saving_gameplays.c ./src/friends_gameplay/friends_gameplay.c ./src/friends_gameplay/multiple_player_game_checkers.c
```

-   For Windows

```
gcc -o bin/src/win/main.exe ./src/main.c ./src/computer_turn/unbeatable_mode.c ./src/computer_turn/normal_mode.c ./src/computer_turn/computer_moves.c ./src/computer_turn/computer_turn.c ./src/common/err.c ./src/common/graphic.c ./src/common/form.c ./src/game_play/game_checkers.c ./src/game_play/user_turn.c ./src/game_play/game_play.c ./src/game_play/saving_gameplays.c ./src/friends_gameplay/friends_gameplay.c ./src/friends_gameplay/multiple_player_game_checkers.c
```

3. Now, run the game using the previous commands.

## Contributing

Please follow the following steps to contribute to this project. There are some important procedures.

1. Fork and clone this repository.
2. Create a branch from the `dev` branch, not the master.
3. Make you changes
4. Open a pull request to the `dev` branch, not the master.
5. Voila, your almost done!

## Issues I'm aware of

-   none.
