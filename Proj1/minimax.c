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

//int turn = 5;
int depth = 0;
//int board[8][8] = {{0,5,0,0,0,0,0,0}, 
				   // {0,0,0,0,0,5,0,0},
				   // {0,0,0,0,0,0,0,0},
				   // {0,0,0,2,1,0,0,0},
				   // {0,0,0,1,2,0,0,0},
				   // {0,0,0,0,0,0,0,0},
				   // {0,0,0,0,0,0,0,0},
				   // {0,0,0,5,0,0,0,0}};


void minimax();
unsigned concatenate();

//int main(int argc, char const *argv[]) {
//	minimax(1, board);
//	return 0;
//}

void minimax(int player, int board[8][8], int suggest) {
	//if depth is 0, search for the current 
	//highest ranked move
	int bestMove = 0;
	int bestValue = -1000000;
	int moves = 0;
	if (depth == 0) {

		for(int x = 0; x < 8; ++x) {
			for (int y = 0; y < 8; ++y) {
				printf("%d\n", bestValue);
				if (board[x][y] == suggest) {
					moves = 1;

					int coordinate = concatenate(x+1,y+1);

					for (int co = 0; co < 4; co++) {
						if (corners[co] == coordinate) {
							if (cornerWeight > bestValue) {
								bestValue = cornerWeight;
								bestMove = coordinate;
							}
						}
					}
					for (int si = 0; si < 16; si++) {
						if (sides[si] == coordinate) {
							if (sideWeight > bestValue) {
								bestValue = sideWeight;
								bestMove = coordinate;
							}
						}
					}
					for (int mi = 0; mi < 12; mi++) {
						if (middle[mi] == coordinate) {
							if (middleWeight > bestValue) {
								bestValue = middleWeight;
								bestMove = coordinate;
							}
						}
					}
					for (int ce = 0; ce < 4; ce++) {
						if (center[ce] == coordinate) {
							if (centerWeight > bestValue) {
								bestValue = centerWeight;
								bestMove = coordinate;
							}
						}
					}
					for (int da = 0; da < 12; da++) {
						if (danger[da] == coordinate) {
							if (dangerWeight > bestValue) {
								bestValue = dangerWeight;
								bestMove = coordinate;
							}
						}
					}
					for (int ne = 0; ne < 16; ne++) {
						if (netural[ne] == coordinate) {
							if (neturalWeight > bestValue) {
								bestValue = neturalWeight;
								bestMove = coordinate;
							}
						}
					}
				}
			}
		}
		if (moves == 0) {
			printf("No Possible Moves!\n");
		} else {
			int yy = bestMove % 10;
			yy = yy - 1;
			int xx = bestMove / 10;
			xx = xx -1;
			board[xx][yy] = player;
		}
		printf("\n");
	for(int i=0; i < 8; ++i){
		for (int j=0; j < 8; ++j)
		{
			printf("%d ",board[i][j]);
		}
		printf("\n");
	}
	}
}





unsigned concatenate(unsigned x, unsigned y) {
    unsigned pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;        
}















//http://mnemstudio.org/game-reversi-example-2.htm
//www.samsoft.org.uk/reversi/strategy.htm
//http://www.riscos.com/support/developers/agrm/chap09.htm
//stackoverflow concatenate