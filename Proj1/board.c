#include <stdio.h>
//#include <conio.h>
#include "minimax.c"

int board[8][8];
int score[2]={0,0};
int game=0,row=10,col=10;
int legalMoves[64][64];
char pos[3];
int player=1;
int legal=0;
int score1=0;
int score2=0;
int turn=5,moves=0,cantMove[2];

void screen();
void newgame();
void islegal(int x, int y);
void slowScore();
void checkMove();
void retZero();
void putPiece(int x, int y);

int main(int argc, char const *argv[])
{
	newgame();
	while(game==0) {
		
		checkMove();
		//printf("%d",moves);
		if(moves==0){
			cantMove[0]=1;
			legal=1;
			goto nextTurn;
		}
		screen();
		scanf("%s",pos);
		//system("cls");
		row=pos[0]-'1';
		col=pos[2]-'1';
		islegal(row,col);
	nextTurn:
		retZero();

		if (legal == 1) {
			player = 2;
			checkMove();
			if(moves==0){
				cantMove[1]=1;
				legal=0;
				goto nextTurn1;
			}
			printf("1\n");
			minimax(player, board, 0, turn);
			printf("2\n");
			//printf("1\n");
			putPiece(xx, yy);
			//printf("2\n");
			retZero();
			//printf("3\n");
			player = 1;
			//printf("4\n");
			legal=0;
			//printf("5\n");
		}
	nextTurn1:
		if(cantMove[0]==1 && cantMove[1]==1){
			if (score1 > score2) {
				printf("Player 1 Wins!\n");
			} else if (score2 > score1) {
				printf("Player 2 Wins!\n");
			} else {
				printf("Game Over!\n");
			}
			game=1;
		}else{
			game=0;
			cantMove[0]=0;
			cantMove[1]=0;
		}
	}
	return 0;
}

void screen()
{
	printf("\n");
	for(int i=0; i < 8; ++i){
		for (int j=0; j < 8; ++j)
		{
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

void islegal(int x, int y) {
	if (x < 0 || x > 7 || y < 0 || y > 7) {
		printf("\n***Invalid Move***\n");
		legal=0;
	} else if (board[x][y] == 1 || board[x][y] == 2) {
		printf("\n***Invalid Move***\n");
		legal = 0;
	} else if (board[x][y] == 0 && board[x][y]!= turn) {
		printf("\n***Invalid Move***\n");
		legal=0;
	} else if(board[x][y] == turn){
		legal=1;
	
		putPiece(x,y);
		//board[x][y]=player;
		
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

void retZero(){
	for(int i=0; i < 8; ++i){
		for (int j=0; j < 8; ++j) {
			if(board[i][j]==turn){
				board[i][j]=0;
			}
		//
		}
	}
}

void checkMove(){
	int stopCheck=0, ic, jc;
	
	moves=0;
	for(int i=0; i < 8; ++i){
		for (int j=0; j < 8; ++j) {
			if(board[i][j]==player){
				//printf("1");
				//-------- Check South
				ic=i+1;
				
				if(ic<8 && board[ic][j]!=player && board[ic][j]!=0 && board[ic][j]!=turn){
					do{
						if(board[ic][j]==player){
							stopCheck=1;
						}
						if(board[ic][j]!=player && board[ic][j]!=0&& board[ic][j]!=turn){
							++ic;
						}else if(board[ic][j]==0){
							board[ic][j]=turn;
							++moves;
							stopCheck=1;
						}
					}while(stopCheck==0);
				}
				
				//printf("2");
				//-------- Check North
				stopCheck=0;
				ic=i-1;
				
				if(ic>=0 && board[ic][j]!=player && board[ic][j]!=0 && board[ic][j]!=turn){
					do{
						if(board[ic][j]==player){
							stopCheck=1;
						}
						if(board[ic][j]!=player && board[ic][j]!=0 && board[ic][j]!=turn){
							--ic;
						}else if(board[ic][j]==0){
							board[ic][j]=turn;
							++moves;
							stopCheck=1;
						}
					}while(stopCheck==0);
				}
				//printf("3");
				
				//-------- Check East
				stopCheck=0;
				jc=j+1;
				
				if(jc<8 && board[i][jc]!=player && board[i][jc]!=0 && board[i][jc]!=turn){
					do{
						if(board[i][jc]==player){
							stopCheck=1;
						}
						if(board[i][jc]!=player && board[i][jc]!=0 && board[i][jc]!=turn){
							++jc;
						}else if(board[i][jc]==0){
							board[i][jc]=turn;
							++moves;
							stopCheck=1;
						}
					}while(stopCheck==0);
				}
				
				//printf("4	");
				//-------- Check West
				stopCheck=0;
				jc=j-1;
				
				if(jc>=0 && board[i][jc]!=player && board[i][jc]!=0 && board[i][jc]!=turn){
					do{
						if(board[i][jc]==player){
							stopCheck=1;
						}
						if(board[i][jc]!=player && board[i][jc]!=0 && board[i][jc]!=turn){
							--jc;
						}else if(board[i][jc]==0){
							board[i][jc]=turn;
							++moves;
							stopCheck=1;
						}
					}while(stopCheck==0);
				}
				ic=0;
				jc=0;
//				//-------- Check South-East
//				stopCheck=0;
//				ic=i+1;
//				jc=j+1;
//				
//				if(ic<8 && jc<8 && board[ic][jc]!=player && board[ic][jc]!=0&& board[ic][jc]!=turn){
//					do{
//						if(board[ic][jc]!=player && board[ic][jc]!=0 ){
//							++ic;
//							++jc;
//						}else if(board[ic][jc]==0){
//							board[ic][jc]=turn;
//							stopCheck=1;
//						}
//					}while(stopCheck==0);
//				}
			}
		}
	}
}

void putPiece(int x, int y){
	int ic, jc,stopCheck=0,full=0;
	board[x][y]=player;
	//---- Full South
	stopCheck=0;
	ic=x-1;
	
	if(ic>=0){
		if(board[ic][y]!=player || board[ic][y]!=0 || board[ic][y]!=turn){
			do{
				if(board[ic][y]==player){
					stopCheck=1;
					full=1;
				}
				if(board[ic][y]!=player && board[ic][y]!=0 && board[ic][y]!=turn){
					--ic;
				}else{
					stopCheck=1;
				}				
			}while(stopCheck==0);
			if(full==1){
				for(int fullx=ic;fullx<=x;++fullx){
					board[fullx][y]=player;
				}
			}
			full=0;
		}		
	}
	
	//---- Full North
	stopCheck=0;
	ic=x+1;
	
	if(ic<8){
		if(board[ic][y]!=player || board[ic][y]!=0 || board[ic][y]!=turn){
			do{
				if(board[ic][y]==player){
					stopCheck=1;
					full=1;
				}
				if(board[ic][y]!=player && board[ic][y]!=0 && board[ic][y]!=turn){
					++ic;
				}else{
					stopCheck=1;
				}				
			}while(stopCheck==0);
			if(full==1){
				for(int fullx=x;fullx<=ic;++fullx){
					board[fullx][y]=player;
				}
			}
			full=0;
		}		
	}
	
	//---- Full East
	stopCheck=0;
	jc=y-1;
	
	if(jc>0){
		if(board[x][jc]!=player || board[x][jc]!=0 || board[x][jc]!=turn){
			do{
				if(board[x][jc]==player){
					stopCheck=1;
					full=1;
				}
				if(board[x][jc]!=player && board[x][jc]!=0 && board[x][jc]!=turn){
					--jc;
				}else{
					stopCheck=1;
				}				
			}while(stopCheck==0);
			if(full==1){
				for(int fully=jc;fully<=y;++fully){
					board[x][fully]=player;
				}
			}
			full=0;
		}		
	}
	
	//---- Full West
	stopCheck=0;
	jc=y+1;
	
	if(jc<8){
		if(board[x][jc]!=player || board[x][jc]!=0 || board[x][jc]!=turn){
			do{
				if(board[x][jc]==player){
					stopCheck=1;
					full=1;
				}
				if(board[x][jc]!=player && board[x][jc]!=0 && board[x][jc]!=turn){
					++jc;
				}else{
					stopCheck=1;
				}				
			}while(stopCheck==0);
			if(full==1){
				for(int fully=y;fully<=jc;++fully){
					board[x][fully]=player;
				}
			}
			full=0;
		}		
	}
	
	//---- Full South-East
	stopCheck=0;
	ic=x-1; //Check South of the piece is already on the board
	jc=y-1; //Check East
	
	if(jc>=0 && ic>=0){
		if(board[ic][jc]!=player && board[ic][jc]!=0 && board[ic][jc]!=turn){
			while(stopCheck==0 ){
				if(board[ic][jc]==player){
					stopCheck=1;
					full=1;
					
				}else				if(board[ic][jc]!=player && board[ic][jc]!=0 && board[ic][jc]!=turn){
					board[ic][jc]=player;
					ic=ic-1;
					jc=jc-1;
				}else{
					stopCheck=1;
				}
			}
			full=0;
		}		
	}
	
		//---- Full South-West
	stopCheck=0;
	ic=x-1;
	jc=y+1;
	
	if(jc<8 && ic>=0){
		if(board[ic][jc]!=player && board[ic][jc]!=0 && board[ic][jc]!=turn){
			while(stopCheck==0 ){
				if(board[ic][jc]==player){
					stopCheck=1;
					full=1;
					
				}else				if(board[ic][jc]!=player && board[ic][jc]!=0 && board[ic][jc]!=turn){
					board[ic][jc]=player;
					ic=ic-1;
					jc=jc+1;
				}else{
					stopCheck=1;
				}
			}
			full=0;
		}		
	}
	
		//---- Full North East
	stopCheck=0;
	ic=x+1;
	jc=y-1;
	
	if(jc>=0 && ic<8){
		if(board[ic][jc]!=player && board[ic][jc]!=0 && board[ic][jc]!=turn){
			while(stopCheck==0 ){
				if(board[ic][jc]==player){
					stopCheck=1;
					full=1;
					
				}else				if(board[ic][jc]!=player && board[ic][jc]!=0 && board[ic][jc]!=turn){
					board[ic][jc]=player;
					ic=ic+1;
					jc=jc-1;
				}else{
					stopCheck=1;
				}
			}
			full=0;
		}		
	}
	
		//---- Full North-West
	stopCheck=0;
	ic=x+1;
	jc=y+1;
	
	if(jc<8 && ic<8){
		if(board[ic][jc]!=player && board[ic][jc]!=0 && board[ic][jc]!=turn){
			while(stopCheck==0 ){
				if(board[ic][jc]==player){
					stopCheck=1;
					full=1;
					
				}else				if(board[ic][jc]!=player && board[ic][jc]!=0 && board[ic][jc]!=turn){
					board[ic][jc]=player;
					ic=ic+1;
					jc=jc+1;
				}else{
					stopCheck=1;
				}
			}
			full=0;
		}		
	}
}







