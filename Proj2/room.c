#include <stdio.h>

char nBYm[3];
int game = 0;
int row;
int col;

void ello();

int main(int argc, char const *argv[])
{
	printf("\n\nEnter Size of the Room: (n,m)\n");
	scanf("%s", nBYm);
	printf("%s\n", nBYm);
	row = *nBYm[0];
	col = *nBYm[2];
	printf("%d\n", row);
	printf("%d\n", col);
	ello(row, col);	
	//while(game == 0) {

	//}
	return 0;
}


void ello(int x, int y) {
	printf("%d\n", x);
	printf("%d\n", y);

}