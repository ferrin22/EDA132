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

void screen();
void newgame();
void islegal();
void slowScore();

int main(int argc, char const *argv[]) {
	newgame();
	screen();
	while(game==0) {
		scanf("%s",pos);
		row=pos[0]-'1';
		col=pos[2]-'1';
		islegal(row,col);
		screen();
	}
	return 0;
}

void screen() {
	printf("\n");
	for(int i=0; i < 8; ++i) {
		for (int j=0; j < 8; ++j)
		{
			if (i==row && j==col)
			{
				if (legal == 1) {
					board[i][j]=player;
					
					if (player == 1) {
						player = 2;
					} else {
						player = 1;
					}
				}
			}
			printf("%d ",board[i][j]);
		}
		printf("\n");
	}
	slowScore();
	printf("Enter Position (x,y): ");
}


void newgame() {
	for(int i=0; i < 8; ++i){
		for (int j=0; j < 8; ++j) {
			board[i][j]=0;
		}
	}
	board[3][4]=1;
	board[4][3]=1;
	board[3][3]=2;
	board[4][4]=2;
}


void islegal(x, y) {
	if (x < 0 || x > 7 || y < 0 || y > 7) {
		printf("\n***Invalid Move***\n");
		legal=0;
	} else if (board[x][y] != 0) {
		printf("\n***Invalid Move***\n");
		legal=0;
	} else {
		legal=1;
	}
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
	printf("%d, %d\n", score1, score2);
}

void checkMove(){
	for(int i=0; i < 8; ++i){
		for (int j=0; j < 8; ++j) {
			if (board[i][j]==0){}
			if (board[i][j]==player)
			{
				
			}


//void add(x, y) {
//	board[x][y] = 1;
//	}

