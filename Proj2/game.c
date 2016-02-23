#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int n=5,m=8,xRob,yRob,wall;
int board[5][8];
int posRobot[2];
float probaBoard[5][8],error;
float newBoard[5][8];
int sensor[4]; // N S W E
char inp[1];
int stop = 0;
int firstMove = 0;
int direction = 5;
int xsen;
int ysen;
int xTrack;
int yTrack;
int firstT = 1;


void randomBoard();
void screen();
void reset();
void sense();
void move(int x, int y);
void seventy(int x, int y, int direction);
int thirty(int x, int y, int direction);
int walls(int x, int y, int direction);
void noisySensor(int x, int y);
void tracking(int x, int y, float board[n][m]);
void show();
void merger(float old[n][m], float newB[n][m]);


int main(){
	reset();
	randomBoard();

	printf("\n-----\n");
	printf("The room is %d by %d (indexed from 0)\n", n, m);
	printf("Type \"c\" for the robot to make its next move\n");
	printf("-----\n");

	int x = (rand() % n);
	int y = (rand() % m);
	xRob=x;yRob=y;
	
	while (stop == 0) {
		//screen();
		printf("\nRobot is at %d, %d", xRob, yRob);
		printf("\n");
		noisySensor(xRob, yRob);
		if(firstT == 0) {
			tracking(xsen, ysen, newBoard);
			merger(probaBoard, newBoard);
		} else {
			tracking(xsen, ysen, probaBoard);
			firstT = 0;
		}
		printf("Tracker Guesses %d, %d\n", xTrack, yTrack);
		//show();
		
		scanf("%s", inp);
		char yup = inp[0];
		if(yup == 'c') {
			move(xRob, yRob);
			//noisySensor(x, y);
		}
	}
	// if(board[xRob][yRob]==0){
	// 	wall=1;
	// }else{
	// 	wall=0;
	// }
	// sense();
	
	return 0;
}


void merger(float old[n][m], float newB[n][m]) {
	if(xsen != -1) {
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				old[i][j] = newB[i][j] - old[i][j];
				newB[i][j] = 0;
			}
		}
		int ibest = 0;
		int jbest = 0;
		float tbest = 0;
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				if(old[i][j] >= tbest) {
					tbest = old[i][j];
					ibest = i;
					jbest = j;
				}
			}
		}
		xTrack = ibest;
		yTrack = jbest;
	}
}


void show() {
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
	 		printf("  %1.3f", probaBoard[i][j]);
	 	}
	 	printf("\n");
	}
}



void tracking(int x, int y, float board[n][m]) {
	if(x != -1 && y != -1) {
		board[x][y] = 0.1;

		if(x - 1 >= 0 && y - 1 >= 0) {
			board[x - 1][y - 1] = 0.05;
		}
		if(x - 1 >= 0) {
		board[x - 1][y] = 0.05;
		}
		if(x - 1 >= 0 && y + 1 < m) {
		board[x - 1][y + 1] = 0.05;
		}
		if(y - 1 >= 0) {
		board[x][y - 1] = 0.05;
		}
		if(y + 1 < m) {
		board[x][y + 1] = 0.05;
		}
		if(x + 1 < n && y - 1 >= 0) {
		board[x + 1][y - 1] = 0.05;
		}
		if(x + 1 < n) {
		board[x + 1][y] = 0.05;
		}
		if(x + 1 < n && y + 1 < m) {
		board[x + 1][y + 1] = 0.05;
		}

		if(x - 2 >= 0 && y - 2 >= 0) {
		board[x - 2][y - 2] = 0.025;
		}
		if(x - 2 >= 0 && y - 1 >= 0) {
		board[x - 2][y - 1] = 0.025;
		}
		if(x - 2 >= 0) {
		board[x - 2][y] = 0.025;
		}
		if(x - 2 >= 0 && y + 1 < m) {
		board[x - 2][y + 1] = 0.025;
		}
		if(x - 2 >= 0 && y + 2 < m) {
		board[x - 2][y + 2] = 0.025;
		}
		if(x - 1 >= 0 && y - 2 >= 0) {
		board[x - 1][y - 2] = 0.025;
		}
		if(x - 2 >= 0 && y + 2 < m) {
		board[x - 1][y + 2] = 0.025;
		}
		if(y - 2 >= 0) {
		board[x][y - 2] = 0.025;
		}
		board[x][y + 2] = 0.025;
		if(x + 1 < n && y - 2 >= 0) {
		board[x + 1][y - 2] = 0.025;
		}
		if(x + 1 < n && y + 2 < m) {
		board[x + 1][y + 2] = 0.025;
		}
		if(x + 2 < n && y - 2 >= 0) {
		board[x + 2][y - 2] = 0.025;
		}
		if(x + 2 < n && y - 1 >= 0) {
		board[x + 2][y - 1] = 0.025;
		}
		if(x + 2 < n) { 
		board[x + 2][y] = 0.025;
		}
		if(x + 2 < n && y + 1 < m) {
		board[x + 2][y + 1] = 0.025;
		}
		if(x + 2 < n && y + 2 < m) {
		board[x + 2][y + 2] = 0.025;
		}
	}
	int xbest = 0;
	int ybest = 0;
	float best = 0;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(board[i][j] > best) {
				best = board[i][j];
					xbest = i;
					ybest = j;
			}
		}
	}
	if(best != 0) {
		xTrack = xbest;
		yTrack = ybest;
	}
	//for(int i = 0; i < n; ++i) {
	//	for(int j = 0; j < m; ++j) {
	//		board[i][j] = 0;
	//	}
	//}
}


/*  
 * Takes the robot's current location as input
 * and determines the robot's next move.
*/
void move(int x, int y) {
	if(firstMove == 0) {
		direction = (rand() % 4);
		//printf("\nDirection is %d\n", direction);
		if(direction == 0 && x - 1 >= 0) {
			xRob = x - 1;
			firstMove = 1;
			return;
		} 
		else if(direction == 1 && y + 1 < m) {
			yRob = y + 1;
			firstMove = 1;
			return;
		}
		else if(direction == 2 && x + 1 < n) {
			xRob = x + 1;
			firstMove = 1;
			return;
		}
		else if(direction == 3 && y - 1 >= 0) {
			yRob = y - 1;
			firstMove = 1;
			return;
		} else {
			move(x, y);
		}
	} else {
		if(walls(x, y, direction) == 1) {
			//printf("Wall\n");
			firstMove = 0;
			move(x, y);
		} else {
			//printf("\nDirection is %d\n", direction);
			int changeDir = (rand() % 10);
			if(changeDir >= 0 && changeDir < 8) {
				seventy(x, y, direction);
			} else {
				direction = thirty(x, y, direction);
				if(direction == 99) {
					firstMove = 0;
					move(x, y);
				}
			}
		}
	}
}


/*
 * Determines whether the robot hits a wall.
 * Takes the current location and the direction
 * that the robot is traveling in as input.
 * Called by move()
*/
int walls(int x, int y, int direction) {
	if(direction == 0 && x - 1 < 0) {
		return 1;
	} 
	else if(direction == 1 && y + 1 >= m) {
		return 1;
	}
	else if(direction == 2 && x + 1 >= n) {
		return 1;
	}
	else if(direction == 3 && y - 1 < 0) {
		return 1;
	} else {
		return 0;
	}
}


/*
 * Logic for the next robot move assuming
 * the robot is continuing in the same
 * direction as it does 70% of the time.
 * Called by move();
*/
void seventy(int x, int y, int direction) {
	//printf(".7\n");
	if(direction == 0 && x - 1 >= 0) {
		xRob = x - 1;
		return;
	} 
	else if(direction == 1 && y + 1 < m) {
		yRob = y + 1;
		return;
	}
	else if(direction == 2 && x + 1 < n) {
		xRob = x + 1;
		return;
	}
	else if(direction == 3 && y - 1 >= 0) {
		yRob = y - 1;
		return;
	} else {
		//printf("Corner\n");
		firstMove = 0;
		move(x, y);
	}
}


/*
 * Logic for the next robot move assuming
 * the robot is changing  direction as it 
 * does 70% of the time.
 * Called by move();
*/
int thirty(int x, int y, int direction) {
	printf("***Robot Changed Direction***\n");
	int newDirection = direction;
	while(direction == newDirection) {
		newDirection = (rand() % 4);
		//printf("New: %d\n", newDirection);
	}
	if(walls(x, y, newDirection) == 0) {

		if(newDirection == 0 && x - 1 >= 0) {
			xRob = x - 1;
			return newDirection;
		} 
		else if(newDirection == 1 && y + 1 < m) {
			yRob = y + 1;
			return newDirection;
		}
		else if(newDirection == 2 && x + 1 < n) {
			xRob = x + 1;
			return newDirection;
		}
		else if(newDirection == 3 && y - 1 >= 0) {
			yRob = y - 1;
			return newDirection;
		}
	}
	return 99;
}

void randomBoard(){
	int r;
	srand(time(NULL));
	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j){
			r=(rand()%1001);
			if(r<=300){
				board[i][j]=0;
			}
		}
	}
}

// void screen(){
// 	printf("\n");
// 	for(int i=0; i<n; ++i){
// 		for(int j=0; j<m; ++j){
// 			printf("%d ",board[i][j]);
// 		}
// 		printf("\n");
// 	}
// 	printf("\n\n");
// 	for(int i=0; i<n; ++i){
// 		for(int j=0; j<m; ++j){
// 			printf("%1.4f ",probaBoard[i][j]);
// 		}
// 		printf("\n");
// 	}
	
// }

void reset(){
	float p;
	p=m*n;
	p=1/p;
	
	for(int i=0; i<4; ++i){
		sensor[i]=0;
	}
	
	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j){
			probaBoard[i][j]= 0.0;
			board[i][j]=1;
		}
	}
}

// void sense(){
	
// 	//check N
// 	if((yRob-1)>=0 && board[yRob-1][xRob]==wall){
// 		sensor[0]=1;				
// 	}
// 	//Check S
// 	if((yRob+1)<n && board[yRob+1][xRob]==wall){
// 		sensor[1]=1;				
// 	}
// 	//check W
// 	if((xRob-1)>=0 && board[yRob][xRob-1]==wall){
// 		sensor[2]=1;				
// 	}
// 	//Check E
// 	if((xRob+1)<m && board[yRob][xRob+1]==wall){
// 		sensor[3]=1;				
// 	}	
	
// 	printf("N:%d S:%d W:%d E:%d ",sensor[0],sensor[1],sensor[2],sensor[3]);
// }





/*
 * Contains all logic for the sensor.  
 * Takes the robot's current location as
 * input and outputs the noisy sensor 
 * approximation.
*/
void noisySensor(int x, int y) {
	int probability = (rand() % 100);

	//true location L with probability 0.1----------------------------------------------
	if(probability >= 0 && probability < 10) {
		printf("Noisy Sensor Approximates (%d, %d)\n", x, y);
		xsen = x;
		ysen = y;
		return;
	}

	//8 surrounding fields L_s with probability 0.05 each-------------------------------
	if(probability >= 10 && probability < 15) {
		if(x - 1 >= 0 && y - 1 >= 0) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x - 1, y - 1);
			xsen = x - 1;
			ysen = y - 1;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}
	if(probability >= 15 && probability < 20) {
		if(x - 1 >= 0) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x - 1, y);
			xsen = x - 1;
			ysen = y;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}
	if(probability >= 20 && probability < 25) {
		if(x - 1 >= 0 && y + 1 < m) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x - 1, y + 1);
			xsen = x - 1;
			ysen = y + 1;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}
	if(probability >= 25 && probability < 30) {
		if(y - 1 >= 0) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x, y - 1);
			xsen = x;
			ysen = y - 1;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}
	if(probability >= 30 && probability < 35) {
		if(y + 1 < m) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x, y + 1);
			xsen = x;
			ysen = y + 1;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}
	if(probability >= 35 && probability < 40) {
		if(x + 1 < n && y - 1 >= 0) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x + 1, y - 1);
			xsen = x + 1;
			ysen = y - 1;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}
	if(probability >= 40 && probability < 45) {
		if(x + 1 < n) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x + 1, y);
			xsen = x + 1;
			ysen = y;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}
	if(probability >= 45 && probability < 50) {
		if(x + 1 >= n && y + 1 >= m) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x + 1, y + 1);
			xsen = x + 1;
			ysen = y + 1;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}

	//16 surrounding fields L_s2 with probability 0.025 each----------------------------------------------
	if(probability >= 50 && probability < 53) {
		if(x - 2 >= 0 && y - 2 >= 0) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x - 2, y - 2);
			xsen = x - 2;
			ysen = y - 2;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}
	if(probability >= 53 && probability < 56) {
		if(x - 2 >= 0 && y -1 >= 0) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x - 2, y - 1);
			xsen = x - 2;
			ysen = y - 1;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}
	if(probability >= 56 && probability < 59) {
		if(x - 2 >= 0) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x - 2, y);
			xsen = x - 2;
			ysen = y;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}
	if(probability >= 59 && probability < 62) {
		if(x - 2 >= 0 && y + 1 < m) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x - 2, y + 1);
			xsen = x - 2;
			ysen = y + 1;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}
	if(probability >= 62 && probability < 65) {
		if(x - 2 >= 0 && y + 2 < m) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x - 2, y + 2);
			xsen = x - 2;
			ysen = y + 2;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}
	//-----------------------------------------
	if(probability >= 65 && probability < 68) {
		if(x - 1 >= 0 && y - 2 >= 0) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x - 1, y - 2);
			xsen = x - 1;
			ysen = y - 2;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}
	if(probability >= 68 && probability < 71) {
		if(x - 1 >= 0 && y + 2 < m) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x - 1, y + 2);
			xsen = x - 1;
			ysen = y + 2;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}
	if(probability >= 71 && probability < 74) {
		if(y - 2 >= 0) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x, y - 2);
			xsen = x;
			ysen = y - 2;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}
	if(probability >= 95 && probability < 98) {
		if(y + 2 < m) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x, y + 2);
			xsen = x;
			ysen = y + 2;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}
	if(probability >= 74 && probability < 77) {
		if(x + 1 < n && y - 2 >= 0) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x + 1, y - 2);
			xsen = x + 1;
			ysen = y - 2;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}
	if(probability >= 77 && probability < 80) {
		if(x + 1 < n && y + 2 < m) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x + 1, y + 2);
			xsen = x + 1;
			ysen = y + 2;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}
	//-----------------------------------------
	if(probability >= 80 && probability < 83) {
		if(x + 2 < n && y - 2 >= 0) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x + 2, y - 2);
			xsen = x + 2;
			ysen = y - 2;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}
	if(probability >= 83 && probability < 86) {
		if(x + 2 < n && y - 1 >= 0) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x + 2, y - 1);
			xsen = x + 2;
			ysen = y - 1;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}
	if(probability >= 86 && probability < 89) {
		if(x + 2 < n) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x + 2, y);
			xsen = x + 2;
			ysen = y;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}
	if(probability >= 89 && probability < 92) {
		if(x + 2 < n && y + 1 < m) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x + 2, y + 1);
			xsen = x + 2;
			ysen = y + 1;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}
	if(probability >= 92 && probability < 95) {
		if(x + 2 < n && y + 2 < m) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x + 2, y + 2);
			xsen = x + 2;
			ysen = y + 2;
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			xsen = -1;
			ysen = -1;
			return;
		}
	}

	//"nothing" with probability 0.1----------------------------------------------
	if(probability >= 98 && probability < 100) {
		printf("Noisy Sensor Approximates 'nothing'\n");
		xsen = -1;
		ysen = -1;
		return;
	}

}
