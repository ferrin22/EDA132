#include <stdio.h>
//#include <conio.h>
//#include "minimax.c"

int board[8][8];
int score[2]={0,0};
int game=0,row=10,col=10;
int legalMoves[64][64];
char pos[3];
int player=1;
int legal=0;
int score1=0;
int score2=0;
int turn=5,moves=0,cantMove[2],xx,yy;

void screen();
void newgame();
void islegal(int x, int y);
void slowScore();
void checkMove();
void retZero();
void putPiece(int x, int y);
void minimax();

int main(int argc, char const *argv[])
{
	newgame();
	while(game==0) {
		checkMove();
		printf("%d",moves);
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
		if(legal==1){
			retZero();
			putPiece(row,col);
			board[row][col]=player;	
		}
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
			minimax();
			//printf("k\n");
			//yy = ai % 10;
		 	//yy = yy - 1;
		 	//xx = ai / 10;
		 	//xx = xx - 1;
		 	//board[xx][yy] = player;
	 		//printf("\n");
			//printf("Opponent Moved To %d,%d\n", (xx + 1), (yy + 1));
		//minimax3(player, board, turn);
			//printf("1\n");
			putPiece(xx, yy);
			//screen();
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
			game=1;
			if(cantMove[0]==0){
				printf("\nPlayer 1 Wins");
			}else{
				printf("\n AI Wins");
			}
		}else{
			game=0;
			cantMove[0]=0;
			cantMove[1]=0;
		}
	}
	return 0;
}

void screen(){
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

void minimax() {
	for(int x = 0; x < 8; ++x) {
		for (int y = 0; y < 8; ++y) {
			if (board[x][y] == 5) {
				board[x][y] = 2;
				return;
			}
		}
	}
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
	} else if ( board[x][y]!=turn) {
		printf("\n***Invalid Move***\n");
		legal=0;
	} else if(board[x][y]==turn){
		legal=1;
	
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
	int turns=0;
	while(turns<5){
	for(int i=0; i < 8; ++i){
		for (int j=0; j < 8; ++j) {
			if(board[i][j]==turn){
				board[i][j]=0;
			}
		//
		}
	}
	++turns;
}
}

void checkMove(){
	int stopCheck=0, ic, jc;
	
	moves=0;
	for(int i=0; i < 8; ++i){
		for (int j=0; j < 8; ++j) {
			if(board[i][j]==player){
				
				//-------- Check South
				ic=i+1;
				
				if(ic<8 && board[ic][j]!=player && board[ic][j]!=0 && board[ic][j]!=turn){
					while(stopCheck==0){
						if(board[ic][j]==player){
							stopCheck=1;
						}else						if(board[ic][j]!=player && board[ic][j]!=0&& board[ic][j]!=turn){
							++ic;
						}
						if(board[ic][j]==0){
							board[ic][j]=turn;
							++moves;
							stopCheck=1;
						}
					}
				}
				
				//-------- Check North
				stopCheck=0;
				ic=i-1;
				
				if(ic>=0 && board[ic][j]!=player && board[ic][j]!=0 && board[ic][j]!=turn){
						while(stopCheck==0){
						if(board[ic][j]==player){
							stopCheck=1;
						}else						if(board[ic][j]!=player && board[ic][j]!=0 && board[ic][j]!=turn){
							--ic;
						}
						 if(board[ic][j]==0){
							board[ic][j]=turn;
							++moves;
							stopCheck=1;
						}
					}
				}
				
				//-------- Check East
				stopCheck=0;
				jc=j+1;
				
				if(jc<8 && board[i][jc]!=player && board[i][jc]!=0 && board[i][jc]!=turn){
					while(stopCheck==0){
						if(board[i][jc]==player){
							stopCheck=1;
						}else						if(board[i][jc]!=player && board[i][jc]!=0 && board[i][jc]!=turn){
							++jc;
						}
						 if(board[i][jc]==0){
							board[i][jc]=turn;
							++moves;
							stopCheck=1;
						}
					}
				}
				
				//-------- Check West
				stopCheck=0;
				jc=j-1;
				
				if(jc>=0 && board[i][jc]!=player && board[i][jc]!=0 && board[i][jc]!=turn){
					while(stopCheck==0){
						if(board[i][jc]==player){
							stopCheck=1;
						}else						if(board[i][jc]!=player && board[i][jc]!=0 && board[i][jc]!=turn){
							--jc;
						}
						 if(board[i][jc]==0){
							board[i][jc]=turn;
							++moves;
							stopCheck=1;
						}
					}
				}
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
//	screen();
//	getch();
	
	for(int i=0;i<8;++i){
		for(int j=0; j<8 ;++j){
			
			if(board[i][j]==player){
				
				
				//----------------South
				ic=i+1;
				if(ic<8 && board[ic][j]!=player && board[ic][j]!=0){
					while(stopCheck==0){
						if(board[ic][j]==player || ic>=8){
							stopCheck=1;
						}
						if(board[ic][j]!=player && board[ic][j]!=0){
							ic=ic+1;
							full=1;
						}else if(board[ic][j]==0){
							stopCheck=1;
							full=0;
						}
					}
					if(full==1){
						for(int fx=i;fx<=ic;++fx){
							board[fx][j]=player;
						}
					}
				}
				full=0;
				stopCheck=0;
				
				
				//----------------North
				ic=i-1;
				if(ic>=0 && board[ic][j]!=player && board[ic][j]!=0){
					while(stopCheck==0){
						if(board[ic][j]==player || ic<0){
							stopCheck=1;
						}
						if(board[ic][j]!=player && board[ic][j]!=0){
							ic=ic-1;
							full=1;
						}else if(board[ic][j]==0){
							stopCheck=1;
							full=0;
						}
					}
					if(full==1){
						for(int fx=ic;fx<=i;++fx){
							board[fx][j]=player;
						}
					}
				}
				full=0;
				stopCheck=0;
				
				//----------------East
				jc=j+1;
				if(jc<8 && board[i][jc]!=player && board[i][jc]!=0){
					while(stopCheck==0){
						if(board[i][jc]==player || jc>=8){
							stopCheck=1;
						}
						if(board[i][jc]!=player && board[i][jc]!=0){
							jc=jc+1;
							full=1;
						}else if(board[i][jc]==0){
							stopCheck=1;
							full=0;
						}
					}
					if(full==1){
						for(int fy=j;fy<=jc;++fy){
							board[i][fy]=player;
						}
					}
				}
				full=0;
				stopCheck=0;
				
				//----------------West
				jc=j-1;
				if(jc>=0 && board[i][jc]!=player && board[i][jc]!=0){
					while(stopCheck==0){
						if(board[i][jc]==player || jc<0){
							stopCheck=1;
						}
						if(board[i][jc]!=player && board[i][jc]!=0){
							jc=jc-1;
							full=1;
						}else if(board[i][jc]==0){
							stopCheck=1;
							full=0;
						}
					}
					if(full==1){
						for(int fy=jc;fy<=j;++fy){
							board[i][fy]=player;
						}
					}
				}
				full=0;
				stopCheck=0;
				
				//----------------South-East
				ic=i+1;
				jc=j+1;
				if(ic<8 && jc<8 && board[ic][jc]!=player && board[ic][jc]!=0){
					while(stopCheck==0){
						if(board[ic][jc]==player || ic>=8 || jc>=8){
							stopCheck=1;
						}
						if(board[ic][jc]!=player && board[ic][jc]!=0){
							ic=ic+1;
							jc=jc+1;
							full=1;
						}else if(board[ic][jc]==0){
							stopCheck=1;
							full=0;
						}
					}
					if(full==1){
						int fy=y;
						for(int fx=i;fx<=ic;++fx){
							board[fx][fy]=player;
							fy=fy+1;
						}
					}
				}
				full=0;
				stopCheck=0;
				
				//----------------South-West
				ic=i+1;
				jc=j-1;
				if(ic<8 && jc>=0 && board[ic][jc]!=player && board[ic][jc]!=0){
					while(stopCheck==0){
						if(board[ic][jc]==player || ic>=8 || jc<0){
							stopCheck=1;
						}
						if(board[ic][jc]!=player && board[ic][jc]!=0){
							ic=ic+1;
							jc=jc-1;
							full=1;
						}else if(board[ic][jc]==0){
							stopCheck=1;
							full=0;
						}
					}
					if(full==1){
						int fy=y;
						for(int fx=i;fx<=ic;++fx){
							board[fx][fy]=player;
							fy=fy-1;
						}
					}
				}
				full=0;
				stopCheck=0;
				
				//----------------North-East
				ic=i-1;
				jc=j+1;
				if(ic>=0 && jc<8 && board[ic][jc]!=player && board[ic][jc]!=0){
					while(stopCheck==0){
						if(board[ic][jc]==player || ic<0 || jc>=8){
							stopCheck=1;
						}
						if(board[ic][jc]!=player && board[ic][jc]!=0){
							ic=ic-1;
							jc=jc+1;
							full=1;
						}else if(board[ic][jc]==0){
							stopCheck=1;
							full=0;
						}
					}
					if(full==1){
						int fy=y;
						for(int fx=ic;fx<=i;++fx){
							board[fx][fy]=player;
							fy=fy+1;
						}
					}
				}
				full=0;
				stopCheck=0;
				
				//----------------North-West
				ic=i-1;
				jc=j-1;
				if(ic>=0 && jc>=0 && board[ic][jc]!=player && board[ic][jc]!=0){
					while(stopCheck==0){
						if(board[ic][jc]==player || ic<0 || jc<0){
							stopCheck=1;
						}
						if(board[ic][jc]!=player && board[ic][jc]!=0){
							ic=ic-1;
							jc=jc-1;
							full=1;
						}else if(board[ic][jc]==0){
							stopCheck=1;
							full=0;
						}
					}
					if(full==1){
						int fy=y;
						for(int fx=ic;fx<=i;++fx){
							board[fx][fy]=player;
							fy=fy-1;
						}
					}
				}
				full=0;
				stopCheck=0;
			}					
		}
	}
}







