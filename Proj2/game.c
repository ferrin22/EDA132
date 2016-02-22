#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int n=5,m=8,xRob,yRob,wall;
int board[5][8];
int posRobot[2];
float probaBoard[5][8],error;
int sensor[4]; // N S W E
char inp[1];
int stop = 0;
int firstMove = 0;
int direction = 5;


void randomBoard();
void screen();
void reset();
void sense();
void move(int x, int y);
void seventy(int x, int y, int direction);
int thirty(int x, int y, int direction);
int walls(int x, int y, int direction);
void noisySensor(int x, int y);

int main(){
	reset();
	randomBoard();
	

	int x = (rand() % n);
	int y = (rand() % m);
	xRob=x;yRob=y;
	
	while (stop == 0) {
		screen();
		printf("Robot is at %d, %d\n", xRob, yRob);
		printf("\n");
		noisySensor(xRob, yRob);
		
		scanf("%s", inp);
		char yup = inp[0];
		if(yup == 'c') {
			move(xRob, yRob);
			//noisySensor(x, y);
		}
	}
	if(board[xRob][yRob]==0){
		wall=1;
	}else{
		wall=0;
	}
	sense();
	
	return 0;
}

void noisySensor(int x, int y) {
	int probability = (rand() % 100);
	if(probability >= 0 && probability < 10) {
		printf("Noisy Sensor Approximates (%d, %d)\n", x, y);
	}
	if(probability >= 10 && probability < 15) {
		if(x - 1 >= 0 && y - 1 >= 0) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x - 1, y - 1);
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			return;
		}
	}
	if(probability >= 15 && probability < 20) {
		if(x - 1 >= 0) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x - 1, y);
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			return;
		}
	}
	if(probability >= 20 && probability < 25) {
		if(x - 1 >= 0 && y + 1 < m) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x - 1, y + 1);
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			return;
		}
	}
	if(probability >= 25 && probability < 30) {
		if(y - 1 >= 0) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x, y - 1);
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			return;
		}
	}
	if(probability >= 30 && probability < 35) {
		if(y + 1 < m) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x, y + 1);
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			return;
		}
	}
	if(probability >= 35 && probability < 40) {
		if(x + 1 < n && y - 1 >= 0) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x + 1, y - 1);
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			return;
		}
	}
	if(probability >= 40 && probability < 45) {
		if(x + 1 < n) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x + 1, y);
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			return;
		}
	}
	if(probability >= 45 && probability < 50) {
		if(x + 1 >= n && y + 1 >= m) {
			printf("Noisy Sensor Approximates (%d, %d)\n", x + 1, y + 1);
			return;
		} else {
			printf("Noisy Sensor Approximates 'nothing'\n");
			return;
		}
	}
}












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

int thirty(int x, int y, int direction) {
	printf("Changed Direction\n");
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

void screen(){
	printf("\n");
	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j){
			printf("%d ",board[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j){
			printf("%1.4f ",probaBoard[i][j]);
		}
		printf("\n");
	}
	
}

void reset(){
	float p;
	p=m*n;
	p=1/p;
	
	for(int i=0; i<4; ++i){
		sensor[i]=0;
	}
	
	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j){
			probaBoard[i][j]=p;
			board[i][j]=1;
		}
	}
}

void sense(){
	
	//check N
	if((yRob-1)>=0 && board[yRob-1][xRob]==wall){
		sensor[0]=1;				
	}
	//Check S
	if((yRob+1)<n && board[yRob+1][xRob]==wall){
		sensor[1]=1;				
	}
	//check W
	if((xRob-1)>=0 && board[yRob][xRob-1]==wall){
		sensor[2]=1;				
	}
	//Check E
	if((xRob+1)<m && board[yRob][xRob+1]==wall){
		sensor[3]=1;				
	}	
	
	printf("N:%d S:%d W:%d E:%d ",sensor[0],sensor[1],sensor[2],sensor[3]);
}


