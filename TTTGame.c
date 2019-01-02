#include <stdio.h>
#include <stdlib.h>
#include "TTTLib.c"

int main(void){

	int *T;
	int Xmove = 0;
	int state = 0;
	int winmove = 0;
	int nonlosemove = 0;
	int randmove = 0;

	T = genBoard();

	while (1){

		/*Player "X" (user)*/

		printf("%d\n", printBoard(T,9));
		printf("Player X, where would you like to play?\n");
		
		/*take in user input, check if the indicated slot is valid*/
		
		while (1){

			scanf("%d", &Xmove);

			if ((Xmove >= 0) && (Xmove <= 8)){
				if (T[Xmove] == 0){
					break;
				}
				else{
					printf("Invalid entry: The slot is already taken.\n");
					printf("Please enter a new number:\n");
				}
			}
			else{
				printf("Invalid entry: The number you entered is out of range.\n");
				printf("Please enter a valid number from 0 to 8:\n");
			}
		}

		/*place X in the indicated slot*/

		if (T[Xmove] == 0){
			T[Xmove] = 1;
		}

		/*analyze the game state after X move*/

		state = analyzeBoard(T,9);

		if (state == 1){
			printf("%d\n", printBoard(T,9));
			printf("Player X wins!\n");
			break;
		}

		if (state == 3){
			printf("%d\n", printBoard(T,9));
			printf("Draw\n");
			break;
		}


		/*Player "O" (computer)*/

		printf("%d\n", printBoard(T,9));

		/*place O in the best spot as analyzed by the simulation functions*/

		while (1){

			winmove = genWinningMove(T,9,2);
			if (winmove != -1){
				T[winmove] = 2;
				break;
			}

			nonlosemove = genNonLosingMove(T,9,2);
			if (nonlosemove != -1){
				T[nonlosemove] = 2;
				break;
			}

			randmove = genRandomMove(T,9,2);
			if (T[randmove] == 0){
				T[randmove] = 2;
				break;
			}
		}

		/*analyze the game state after O move*/

		state = analyzeBoard(T,9);

		if (state == 2){
			printf("%d\n", printBoard(T,9));
			printf("Player O wins!\n");
			break;
		}

		if (state == 3){
			printf("%d\n", printBoard(T,9));
			printf("Draw\n");
			break;
		}
	}
}