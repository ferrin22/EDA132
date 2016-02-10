#include <stdio.h>
//#include <curses.h>

int board[8][8] = {0};
int score[2] = {0,0};
int game = 0;
int row = 10, col = 10;
char pos[3];
int player = 1;
int legal = 0;
int score1 = 0;
int score2 = 0;
int turn = 1;

void screen();
void newGame();
void isLegal();
void slowScore();
void add();
void possibleMoves();
void opposite(char direction, int player, int x, int y);
void move();

int main(int argc, char const *argv[]) {
	newGame();
	while(game == 0) {
		possibleMoves(player);
		screen();
		scanf("%s", pos);
		row=pos[0] - '1';
		col=pos[2] - '1';
		isLegal(row, col);
		move();
		if (player == 1) {
			player = 2;
		} else {
			player = 1;
		}
	}
	return 0;
}

void move() {
for(int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (i == row && j == col) {
				add(row, col);
			}
		}
	}
}

void screen() {
	printf("\n");
	for(int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}
	slowScore();
	printf("Enter Position (x,y): ");
}

void add(x,y) {
	if (legal == 1) {
		board[x][y] = player;
	}
}

void newGame() {
	for(int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j) {
			board[i][j] = 0;
		}
	}
	board[3][4] = 1;
	board[4][3] = 1;
	board[3][3] = 2;
	board[4][4] = 2;
	turn = 1;
}

void slowScore() {
	score1 = 0;
	score2 = 0;
	for(int i=0; i < 8; ++i){
		for (int j=0; j < 8; ++j) {
			if (board[i][j] == 1) {
				++score1;
			} else if (board[i][j] == 2) {
				++score2;
			}
		}
	}
	//printf("%d, %d\n", score1, score2);
}

void isLegal(x, y) {
	if (x < 0 || x > 7 || y < 0 || y > 7) {
		printf("\n***Invalid Move : Try Again***\n");
		legal = 0;
	} else if (board[x][y] != 0) {
		printf("\n***Invalid Move : Try Again***\n");
		legal = 0;
	} else {
		legal = 1;
	}
}

void possibleMoves(int player) {
	for(int i=0; i < 8; ++i){
		for (int j=0; j < 8; ++j) {
			if (board[i][j] == player) {
				if ((i-1 > 0) && board[i-1][j] != 0 && board[i-1][j] != player) {
					opposite(6, player, i-1, j);
				}
				if ((i+1 < 9) && board[i+1][j] != 0 && board[i+1][j] != player) {
					opposite(7, player, i+1, j);
				}
				if ((j-1 > 0) && board[i][j-1] != 0 && board[i][j-1] != player) {
					opposite(8, player, i, j-1);
				}
				if ((j+1 < 9) && board[i][j+1] != 0 && board[i][j+1] != player) {
					opposite(9, player, i, j+1);
				}
			}
		}
	}
}

void opposite(char direction, int player, int x, int y) {
	//printf("%d,%d,%d\n", direction, x, y);
	if (direction == 6) {
		if (x-1 > 0) {
			if (board[x-1][y] == 0) {
				printf("%d,%d\n", x, y+1);
				board[x-1][y] = 3;
			} else if (board[x-1][y] != 0 && board[x-1][y] != player) {
				printf("here\n");
				opposite(6, player, x-1, y);
			}
		}
	}
	if (direction == 7) {
		if (x+1 > 0) {
			if (board[x+1][y] == 0) {
				printf("%d,%d\n", x+2, y+1);
				board[x+1][y] = 3;
			} else if (board[x+1][y] != 0 && board[x+1][y] != player) {
				printf("here\n");
				opposite(6, player, x+1, y);
			}
		}
	}
	if (direction == 8) {
		if (y-1 > 0) {
			if (board[x][y-1] == 0) {
				printf("%d,%d\n", x+1, y);
				board[x][y-1] = 3;
			} else if (board[x][y-1] != 0 && board[x][y-1] != player) {
				printf("here\n");
				opposite(6, player, x, y-1);
			}
		}
	}
	if (direction == 9) {
		if (y+1 > 0) {
			if (board[x][y+1] == 0) {
				printf("%d,%d\n", x+1, y+2);
				board[x][y+1] = 3;
			} else if (board[x][y+1] != 0 && board[x][y+1] != player) {
				printf("here\n");
				opposite(6, player, x, y+1);
			}
		}
	}
}




