#include <stdio.h>

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
int depth = 0;
//int board[8][8] = {{0,5,0,0,0,0,0,0}, 
				   //{0,0,0,0,0,5,0,0},
				   //{0,0,0,0,0,0,0,0},
				   //{0,0,0,2,1,0,0,0},
				   //{0,0,0,1,2,0,0,0},
				   //{0,0,0,0,0,0,0,0},
				   //{0,0,0,0,0,0,0,0},
				   //{0,0,0,5,0,0,0,0}};


int * basecase();
unsigned concatenate();
int * minimax();
void checkMove();
void zero();


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
	if (depth == 0) {

		for(int x = 0; x < 8; ++x) {
			for (int y = 0; y < 8; ++y) {
				//printf("%d\n", bestValue);
				if (board[x][y] == suggest) {
					moves = 1;

					coordinate = concatenate(x+1,y+1);

					for (int ne = 0; ne < 16; ne++) {
						if (netural[ne] == coordinate) {
							found = 1;
							if (neturalWeight > bestValue) {
								bestValue = neturalWeight;
								bestMove = coordinate;
							}
						}
					}
					if (found == 0) {
						for (int mi = 0; mi < 12; mi++) {
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
						for (int si = 0; si < 16; si++) {
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
						for (int da = 0; da < 12; da++) {
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
						for (int co = 0; co < 4; co++) {
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
						for (int ce = 0; ce < 4; ce++) {
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
	}
	return 0;
}

unsigned concatenate(unsigned x, unsigned y) {
    unsigned pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;        
}






//time limit will be like: at the beginning of this iteration,
//if I have enough time, continue, else

int * minimax(int player, int board[8][8], int depth, int suggest) {
	int opposite = 0;
	if (player == 1) {
		opposite = 2;
	} else {
		opposite = 1;
	}


	if (depth == 0) {
		nextMove[0] = basecase(player, board, suggest)[0];
		nextMove[1] = basecase(player, board, suggest)[1];
		if (nextMove[0] == 0) {
			return 0;
		}
		return nextMove;
		// yy = nextMove[0] % 10;
		// yy = yy - 1;
		// xx = nextMove[0] / 10;
		// xx = xx - 1;
		// board[xx][yy] = player;
		// printf("\n");
		// printf("Opponent Moved To %d,%d\n", (xx + 1), (yy + 1));
	} else {

		//for every possible move
		for(int x = 0; x < 8; ++x) {
			for (int y = 0; y < 8; ++y) {
		  		if (board[x][y] == suggest) {
		  			//make that move
		  			printf("a\n");
		  			for(int i=0; i < 8; ++i) {
						for (int j=0; j < 8; ++j) {
							printf("%d ",board[i][j]);
						}
						printf("\n");
					}
		  			board[x][y] = player;
		  			zero(board, suggest);
		  			checkMove(board, player, suggest);
		  			for(int i=0; i < 8; ++i){
		  				for (int j=0; j < 8; ++j)
		  				{
		  					printf("%d ",board[i][j]);
		  				}
		  				printf("\n");
		  			}
		  			printf("b\n");
		  			//make opponents move
		  			response[0] = minimax(opposite, board, depth - 1, suggest)[0];
		  			printf("c\n");
		  			response[1] = minimax(opposite, board, depth - 1, suggest)[1];
		  			printf("d\n");
			 		//undo move
		  			board[x][y] = 5;
		  			printf("e\n");
		  			//compare values
		  			if (-response[1] >= bestSoFar[1]) {
		  				printf("f\n");
		  				bestSoFar[1] = response[1];
		  				printf("g\n");
		  				bestSoFar[0] = response[0];
		  			}
		  		}
		  	}
		}
		//pick the best move so far because it has the best value
		//out of all the possible moves.
	}
	return bestSoFar;
}






void zero(int theboard[8][8], int suggest){
	for(int i=0; i < 8; ++i){
		for (int j=0; j < 8; ++j) {
			if(theboard[i][j]==suggest){
				theboard[i][j]=0;
			}
		//
		}
	}
}


void checktheMove(int theboard[8][8], int player, int turn){
	int stopCheck=0, ic, jc;
	
	for(int i=0; i < 8; ++i){
		for (int j=0; j < 8; ++j) {
			if(theboard[i][j]==player){
				
				//-------- Check South
				ic=i+1;
				
				if(ic<8 && theboard[ic][j]!=player && theboard[ic][j]!=0 && theboard[ic][j]!=turn){
					while(stopCheck==0){
						if(theboard[ic][j]==player){
							stopCheck=1;
						}
						if(theboard[ic][j]!=player && theboard[ic][j]!=0&& theboard[ic][j]!=turn){
							++ic;
						}else if(theboard[ic][j]==0){
							theboard[ic][j]=turn;
							stopCheck=1;
						}
					}
				}
				
				//-------- Check North
				stopCheck=0;
				ic=i-1;
				
				if(ic>=0 && theboard[ic][j]!=player && theboard[ic][j]!=0 && theboard[ic][j]!=turn){
						while(stopCheck==0){
						if(theboard[ic][j]==player){
							stopCheck=1;
						}
						if(theboard[ic][j]!=player && theboard[ic][j]!=0 && theboard[ic][j]!=turn){
							--ic;
						}else if(theboard[ic][j]==0){
							theboard[ic][j]=turn;
							stopCheck=1;
						}
					}
				}
				
				//-------- Check East
				stopCheck=0;
				jc=j+1;
				
				if(jc<8 && theboard[i][jc]!=player && theboard[i][jc]!=0 && theboard[i][jc]!=turn){
					while(stopCheck==0){
						if(theboard[i][jc]==player){
							stopCheck=1;
						}
						if(theboard[i][jc]!=player && theboard[i][jc]!=0 && theboard[i][jc]!=turn){
							++jc;
						}else if(theboard[i][jc]==0){
							theboard[i][jc]=turn;
							stopCheck=1;
						}
					}
				}
				
				//-------- Check West
				stopCheck=0;
				jc=j-1;
				
				if(jc>=0 && theboard[i][jc]!=player && theboard[i][jc]!=0 && theboard[i][jc]!=turn){
					while(stopCheck==0){
						if(theboard[i][jc]==player){
							stopCheck=1;
						}
						if(theboard[i][jc]!=player && theboard[i][jc]!=0 && theboard[i][jc]!=turn){
							--jc;
						}else if(theboard[i][jc]==0){
							theboard[i][jc]=turn;
							stopCheck=1;
						}
					}
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































//http://mnemstudio.org/game-reversi-example-2.htm
//That we were linked to
//www.samsoft.org.uk/reversi/strategy.htm
//http://www.riscos.com/support/developers/agrm/chap09.htm
//stackoverflow concatenate