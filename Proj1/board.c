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
int turn=5,moves=0,cantMove[2],xx,yy;
int inp[1];

void screen();
void newgame();
void islegal(int x, int y);
void slowScore();
void checkMove();
void retZero();
void putPiece(int x, int y);
void inst();
int letToNum(char let);

int main(int argc, char const *argv[])
{
	newgame();
	inst();
	printf("\n\nHow Many Milliseconds Per Move Would You Like Your Opponent To Take?\n");
	scanf("%d",inp);
	int mils = *inp;
	
	while(game==0) {

		checkMove();
		if(moves==0){
			cantMove[0]=1;
			legal=1;
		}
		screen();
		scanf("%s",pos);
		row=pos[0]-'1';
		col=letToNum(pos[2])-1;
		islegal(row,col);
		if(legal==1){
			retZero();
			putPiece(row,col);
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
			clock_t begin = clock(), runningTime;
			int ai = minimax(player, board, 6, turn, begin, runningTime, mils)[0];
			if (ai != 0) {
				yy = ai % 10;
			 	yy = yy - 1;
			 	xx = ai / 10;
			 	xx = xx - 1;
		 		printf("\n");
				printf("Opponent Moved To %d,%d\n", (xx + 1), (yy + 1));
				putPiece(xx, yy);
				retZero();
				player = 1;
			}
			legal=0;
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
	int r=1;
	printf("\n\n");
	printf("      a b c d e f g h\n\n");
	for(int i=0; i < 8; ++i){
		printf(" %d    ",r);
		for (int j=0; j < 8; ++j)
		{
			printf("%d ",board[i][j]);
		}
		++r;
		printf("\n");
	}
	printf("\n\n");
	slowScore();
	printf("\nEnter Position (x,y): ");
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
	printf("Score Player: %d   Score AI: %d\n", score1, score2);
}

void retZero(){
	int turns=0;
	while(turns<5){
	for(int i=0; i < 8; ++i){
		for (int j=0; j < 8; ++j) {
			if(board[i][j]==turn){
				board[i][j]=0;
			}
		}
	}
	++turns;
}
}

void checkMove(){
	int stopCheck=0, ic, jc,check;
	
	moves=0;
	for(int i=0; i < 8; ++i){
		for (int j=0; j < 8; ++j) {
			if(board[i][j]==player){
				
				//-------- Check South
				ic=i+1;
				
				if(ic<8 && board[ic][j]!=player && board[ic][j]!=0 && board[ic][j]!=turn){
					while(stopCheck==0){
						if(board[ic][j]==player || ic>=8){
							stopCheck=1;
						}
						if(board[ic][j]!=player && board[ic][j]!=0 && board[ic][j]!=turn){
							ic=ic+1;
							check=1;
						}
						if(board[ic][j]==0 || board[ic][j]==turn){
							stopCheck=1;
							if(check==1){
								board[ic][j]=turn;
								++moves;
							}
						}
					}
				}
				stopCheck=0;
				
				//-------- Check North
				ic=i-1;
				
				if(ic>=0 && board[ic][j]!=player && board[ic][j]!=0 && board[ic][j]!=turn){
					while(stopCheck==0){
						if(board[ic][j]==player || ic<0){
							stopCheck=1;
						}
						if(board[ic][j]!=player && board[ic][j]!=0 && board[ic][j]!=turn){
							ic=ic-1;
							check=1;
						}
						if(board[ic][j]==0 || board[ic][j]==turn){
							stopCheck=1;
							if(check==1){
								board[ic][j]=turn;
								++moves;
							}
						}
					}
				}
				stopCheck=0;
				
				//-------- Check East
				jc=j+1;
				check=0;
				if(jc<8 && board[i][jc]!=player && board[i][jc]!=0 && board[i][jc]!=turn){
					while(stopCheck==0){
						
						if(board[i][jc]==player || jc>=8){
							stopCheck=1;
						}
						if(board[i][jc]!=player && board[i][jc]!=0 && board[i][jc]!=turn){
							jc=jc+1;
							check=1;
						}
						if(board[i][jc]==0 || board[i][jc]==turn){
							stopCheck=1;
							if(check==1){
								board[i][jc]=turn;
								++moves;
							}
						}
					}
				}
				stopCheck=0;
				
				//-------- Check West
				jc=j-1;
				check=0;
				if(jc>=0 && board[i][jc]!=player && board[i][jc]!=0 && board[i][jc]!=turn){
					while(stopCheck==0){
						if(board[i][jc]==player || jc<0){
							stopCheck=1;
						}
						if(board[i][jc]!=player && board[i][jc]!=0 && board[i][jc]!=turn){
							jc=jc-1;
							check=1;
						}
						if(board[i][jc]==0 || board[i][jc]==turn){
							stopCheck=1;
							if(check==1){
							
							board[i][jc]=turn;
							++moves;}
						}
					}
				}
				stopCheck=0;
				
			}
		}
	
	}
}
	
void putPiece(int x, int y){
	int ic, jc,stopCheck=0,full=0;
	board[x][y]=player;
	
	for(int i=0;i<8;++i){
		for(int j=0; j<8 ;++j){
			
			if(i==x && j==y){
				
				
				//----------------South
				ic=i+1;
				if(ic<8 && board[ic][j]!=player && board[ic][j]!=0){
					//printf("s ");
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
					//printf("n ");
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
					//printf("e ");
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
					//printf("w ");
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
					//printf("se ");
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
					//printf("sw ");
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
				if(ic>=0 && jc<8 && board[ic][jc]!=player && board[ic][jc]!=0 && board[ic][jc]!=turn){
					//printf("ne ");
					while(stopCheck==0){
						if(board[ic][jc]==player || ic<0 || jc>=8){
							stopCheck=1;
						}
						if(board[ic][jc]!=player && board[ic][jc]!=0 && board[ic][jc]!=turn){
							ic=ic-1;
							jc=jc+1;
							full=1;
						}else if(board[ic][jc]==0 || board[ic][jc]==turn){
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
					//printf("nw ");
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
						for(int fx=i;fx<=ic;++fx){
							board[fx][fy]=player;
							fy=fy-1;
						}
					}
				}
				full=0;
				stopCheck=0;
//				screen();
		
			
		}
	}
	}
}

void inst(){
	printf(" Instructions: \n - 0 is an empty space on the board \n - 1 is the player's piece");
	printf("\n - 2 is the AI's piece \n - 5 is a possible move");
	printf("\n - Just write the possition you want to play ie (5,a)");
}

int letToNum(char let){
	if(let=='a'){
		return 1;
	}else if(let=='b'){
		return 2;
	}else if(let=='c'){
		return 3;
	}else if(let=='d'){
		return 4;
	}else if(let=='e'){
		return 5;
	}else if(let=='f'){
		return 6;
	}else if(let=='g'){
		return 7;
	}else if(let=='h'){
		return 8;
	}else{
		return 100;
	}
	
}



