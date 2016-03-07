#include <stdio.h>
#include <string.h>
#include <time.h>

int corners[] = {11,18,81,88};
int sides[] = {13,14,15,16,83,84,85,86,31,41,51,61,38,48,58,68};
int middle[] = {33,34,35,36,43,53,63,64,65,66,56,46};
int center[] = {44,45,54,55};
int danger[] = {12,22,21,17,27,28,71,72,82,87,77,78};
int netural[] = {23,24,25,26,62,52,42,32,73,74,75,76,67,57,47,37};

int cornerWeight = 100;
int sideWeight = 10;
int middleWeight = 5;
int centerWeight = 0;
int dangerWeight = -25;
int neturalWeight = -5;

static int combo[2] = {0, -10000};
int nextMove[2] = {0,-10000};
int response[2] = {0,-10000};
int bestSoFar[2] = {0,-10000};

//int turn = 5;
//int depth = 0;
//int board[8][8] = {{0,5,0,0,0,0,0,0}, 
				   //{0,0,0,0,0,5,0,0},
				   //{0,0,0,0,0,0,0,0},
				   //{0,0,0,2,1,0,0,0},
				   //{0,0,0,1,2,0,0,0},
				   //{0,0,0,0,0,0,0,0},
				   //{0,0,0,0,0,0,0,0},
				   //{0,0,0,5,0,0,0,0}};


int * basecase();
unsigned concatenate(unsigned x, unsigned y);
int * minimax();
void zero(int board[8][8], int suggest);
void checkforMoves(int board[8][8], int player, int turn);


//int main(int argc, char const *argv[]) {
//	basecase(1, board);
//	return 0;
//}

int * basecase(int player, int board[8][8], int suggest) {
	//if depth is 0, search for the current 
	//highest ranked move
	int found = 0;
	int coordinate = 0;
	int bestMove = 0;
	int bestValue = -1000000;
	int moves = 0;
	
	int x,y,ne,mi,si,da,co,ce;
	for(x = 0; x < 8; ++x) {
		for (y = 0; y < 8; ++y) {
			if (board[x][y] == suggest) {
				moves = 1;

				coordinate = concatenate(x+1,y+1);

				for (ne = 0; ne < 16; ne++) {
					if (netural[ne] == coordinate) {
						found = 1;
						if (neturalWeight > bestValue) {
							bestValue = neturalWeight;
							bestMove = coordinate;
						}
					}
				}
				if (found == 0) {
					for (mi = 0; mi < 12; mi++) {
						if (middle[mi] == coordinate) {
							found = 1;
							if (middleWeight > bestValue) {
								bestValue = middleWeight;
								bestMove = coordinate;
							}
						}
					}
				}
				if (found == 0) {
					for (si = 0; si < 16; si++) {
						if (sides[si] == coordinate) {
							found = 1;
							if (sideWeight > bestValue) {
								bestValue = sideWeight;
								bestMove = coordinate;
							}
						}
					}
				}
				if (found == 0) {
					for (da = 0; da < 12; da++) {
						if (danger[da] == coordinate) {
							found = 1;
							if (dangerWeight > bestValue) {
								bestValue = dangerWeight;
								bestMove = coordinate;
							}
						}
					}
				}
				if (found == 0) {
					for (co = 0; co < 4; co++) {
						if (corners[co] == coordinate) {
							found = 1;
							if (cornerWeight > bestValue) {
								bestValue = cornerWeight;
								bestMove = coordinate;
							}
						}
					}
				}	
				if (found == 0) {
					for (ce = 0; ce < 4; ce++) {
						if (center[ce] == coordinate) {
							found = 1;
							if (centerWeight > bestValue) {
								bestValue = centerWeight;
								bestMove = coordinate;
							}
						}
					}
				}
			}
		}
	}
	found = 0;
	if (moves != 0) {
		//yy = bestMove % 10;
		//yy = yy - 1;
		//xx = bestMove / 10;
		//xx = xx - 1;
		//board[xx][yy] = player;
		//printf("\n");
		//printf("Opponent Moved To %d,%d\n", (xx + 1), (yy + 1));
		combo[0] = bestMove;
		combo[1] = bestValue;
		return combo;
	}
	return 0;
}

unsigned concatenate(unsigned x, unsigned y) {
    unsigned pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;        
}



int * minimax(int player, int board[8][8], int depth, int suggest, clock_t start, clock_t runTime, int limit) {

	int opposite = 0;
	if (player == 1) {
		opposite = 2;
	} else {
		opposite = 1;
	}

	runTime = clock() - start;
	int msec = runTime * 1000 / CLOCKS_PER_SEC;
	int milli = msec%1000;
	int x,y;
	if (depth == 0) {
		memcpy(nextMove, basecase(player, board, suggest), 2);
		if (nextMove[0] == 0) {
			return 0;
		}
		return nextMove;
	} else {
		if (milli < limit) {
		//for every possible move
			for(x = 0; x < 8; ++x) {
				for (y = 0; y < 8; ++y) {
			  		if (board[x][y] == suggest) {
			  			memcpy(response, minimax(opposite, board, depth - 1, suggest, start, runTime, limit), 2);
			  			board[x][y] = 5;
			  			checkforMoves(board, player, suggest);
			  			zero(board, suggest);
			  			if (-response[1] >= bestSoFar[1]) {
			  				bestSoFar[1] = response[1];
			  				bestSoFar[0] = response[0];
			  			}
			  		}
			  	}
			  }
			}
	}
	return bestSoFar;
}



void zero(int theboard[8][8], int suggest){
	int i,j;
	for(i=0; i < 8; ++i){
		for (j=0; j < 8; ++j) {
			if(theboard[i][j]==suggest){
				theboard[i][j]=0;
			}
		//
		}
	}
}




void checkforMoves(int board[8][8], int player, int turn){
	int stopCheck=0, ic, jc,check;
	int i,j;
	for(i=0; i < 8; ++i){
		for (j=0; j < 8; ++j) {
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
							}
						}
					}
				}
				stopCheck=0;
				
			}
		}
	
	}
}
