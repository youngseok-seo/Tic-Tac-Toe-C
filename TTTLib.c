#include <stdio.h>
#include <stdlib.h>

int errorCheck(int *T, int size);
int *genBoard(void);
int printBoard(int *T, int size);
int analyzeBoard(int *T, int size);
int opponent(int player);
int *copyList(int *T, int size);
int genWinningMove(int *T, int size, int player);
int genNonLosingMove(int *T, int size, int player);
int genOpenMove(int *T, int size, int player);
int genRandomMove(int *T, int size, int player);


int errorCheck(int *T, int size){

	/*Helper function #1: check for errors*/
	
	int i = 0;

	if (T == NULL){
		return -1;
	}
	if (size != 9){
		return -1;
	}
	for (i = 0; i < size; i++){
		if ((T[i] != 0)&&(T[i] != 1)&&(T[i] != 2)){
			return -1;
		}
	}
	return 0;
}

int *genBoard(void){

	int i = 0;
	int *T;

	T = (int *)malloc(9 * sizeof(int));
	for (i = 0; i < 9; i++){
		T[i] = 0;
	}

	return T;
}

int printBoard(int *T, int size){

	/*check for errors*/

	if (errorCheck(T,size) == -1){
		return -1;
	}

	/*return 0 for success, -1 for ERROR*/

	char board[9];
	int i = 0;

	/*create board shown to user*/
	
	board[0] = '0';
	board[1] = '1';
	board[2] = '2';
	board[3] = '3';
	board[4] = '4';
	board[5] = '5';
	board[6] = '6';
	board[7] = '7';
	board[8] = '8';

	/*insert "X" or "O" into user-assigned slot*/

	for (i = 0; i < size; i++){
		if (T[i] == 1){
			board[i] = 'X';
		}
		else if (T[i] == 2){
			board[i] = 'O';
		}
	}

	/*print new board*/

	printf(" %c | %c | %c \n",board[0],board[1],board[2]);
	printf("---|---|---\n");
	printf(" %c | %c | %c \n",board[3],board[4],board[5]);
	printf("---|---|---\n");
	printf(" %c | %c | %c \n",board[6],board[7],board[8]);

	return 0;
}

int analyzeBoard(int *T, int size){

	/*check for errors*/

	if (errorCheck(T,size) == -1){
		return -1;
	}

	/*return 0 for In-play
	  return 1 for "X" wins
	  return 2 for "O" wins
	  return 3 for Draw
	  return -1 for ERROR*/

	int i = 0;
	int row = 0;
	int col = 0;
	int diag1 = 0;
	int diag2 = 0;

	/*analyze rows*/

	for (i = 0; i < 7; i = i + 3){
		row = (T[i] * T[i+1] * T[i+2]);
		if (row == 1){
			return 1;
		}
		if (row == 8){
			return 2;
		}
	}

	/*analyze columns*/

	for (i = 0; i < 3; i = i + 1){
		col = (T[i] * T[i+3] * T[i+6]);
		if (col == 1){
			return 1;
		}
		if (col == 8){
			return 2;
		}
	}

	/*analyze diagonals*/

	diag1 = T[0] * T[4] * T[8];
	diag2 = T[2] * T[4] * T[6];
	if ((diag1 == 1)||(diag2 == 1)){
		return 1;
	}
	else if ((diag1 == 8)||(diag2 == 8)){
		return 2;
	}

	/*check if the game is In-play*/

	for (i = 0; i < size; i++){
		if (T[i] == 0){
			return 0;
		}
	}

	/*if the above conditions are not met, the game is a Draw*/

	return 3;
}

int opponent(int player){

	/*Helper function #2: return the opponent*/

	if (player == 1){
		return 2;
	}
	if (player == 2){
		return 1;
	}
}

int *copyList(int *T, int size){

	/*Helper function #3: copy a list*/

	int i = 0;
	int *copyT;
	copyT = (int *)malloc(size * sizeof(int));

	for (i = 0; i < size; i++){
		copyT[i] = T[i];
	}
	return copyT;
}


int genWinningMove(int *T, int size, int player){

	/*check for errors*/

	if (errorCheck(T,size) == -1){
		return -1;
	}

	/*generate an offensive move that will win the game
     return -1 for ERROR*/

	int i = 0;
	int *copyT;
	
	for (i = 0; i < 9; i++){

		copyT = copyList(T,9);
		if (copyT[i] == 0){
			copyT[i] = player;
			if (analyzeBoard(copyT,9) == player){
				return i;
			}
		}

	}

	return -1;
}

int genNonLosingMove(int *T, int size, int player){

	/*generate a defensive move that will prevent the opponent from winning*/

	return genWinningMove(T,size,opponent(player));
}

int genOpenMove(int *T, int size, int player){

	/*check for errors*/

	if (errorCheck(T,size) == -1){
		return -1;
	}

	/*generate the first open slot
	  return -1 for ERROR*/

	int i = 0;

	for (i = 0; i < size; i++){
		if (T[i] == 0){
			return i;
		}
	}

	return -1;
}

int genRandomMove(int *T, int size, int player){

	/*check for errors*/

	if (errorCheck(T,size) == -1){
		return -1;
	}

	/*check if there is an empty slot
	  return -1 for ERROR*/

	int empty;
	int i = 0;
	int randmove;

	empty = 0;
	for (i = 0; i < size; i++){
		if (T[i] == 0){
			empty = 1;
			break;
		}
	}
	if (empty == 0){
		return -1;
	}

	/*generate a random move
	  use recursion if necessary*/

	randmove = (rand() % 9);
	if (T[randmove] == 0){
		return randmove;
	}
	else{
		return genRandomMove(T,size,player);
	}
}