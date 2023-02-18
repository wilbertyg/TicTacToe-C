#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
const char empty[][15] = {{218, 196, 196, 196, 194, 196, 196, 196, 194, 196, 196, 196, 191, '\n'},
                	{179, ' ', ' ', ' ', 179, ' ', ' ', ' ', 179, ' ', ' ', ' ', 179, '\n'},
           	    	{195, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 180, '\n'},
                	{179, ' ', ' ', ' ', 179, ' ', ' ', ' ', 179, ' ', ' ', ' ', 179, '\n'},
            		{195, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 180, '\n'},
                	{179, ' ', ' ', ' ', 179, ' ', ' ', ' ', 179, ' ', ' ', ' ', 179, '\n'},
                	{192, 196, 196, 196, 193, 196, 196, 196, 193, 196, 196, 196, 217, '\n'}};
void emptyBox(char box[][15], char boxValue[4][4], int *turn) {
	*turn = 1;
	for (int i = 0; i < 7; i++) {
		strcpy(box[i], empty[i]);
	}
	for (int i = 0; i < 3; i++) {
    	strcpy(boxValue[i], "###");
	}
}
void printBox(char box[][15], int x ,int y) {
	system("cls");
	printf("\tTIC-TAC-TOE\n");
	printf("Made by: Wilbert Yang (2602093802)\n\n");
	printf("KEY PRESS:\n");
	for (int i = 0; i < 7; i++) {
		switch(i) {
			case 0:
				printf("'W' to move up    ");
				break;
			case 1:
				printf("'A' to move left  ");
				break;
			case 2:
				printf("'S' to move down  ");
				break;
			case 3:
				printf("'D' to move right ");
				break;
			case 4:
				printf("'R' to reset      ");
				break;
			case 5:
				printf("SPACEBAR to fill  ");
				break;
			case 6:
				printf("'M' to exit       ");
				break;
		}
		printf("\t");
    	for (int j = 0; j < 14; j++) {
    		if (j == x - 2 && i == y) {
    			printf(">");
			} else if (j == x + 2 && i == y) {
				printf("<");
			} else if (i == y + 1 && j == x) {
				printf("|");
			} else if (i == y - 1 && j == x) {
				printf("|");
			} else {
				printf("%c", box[i][j]);
			}
		}
	}
}
void resetValue(int* x, int* y) {
	*x = 1;
	*y = 1;
}
bool checkValue(char x) {
	return (x == 'X' || x == 'O')? true : false;  
}
bool checkWinner(char box[][4], char* win) {
	if ((box[0][0] == box[1][1] && box [1][1] == box[2][2] || box[0][2] == box[1][1] && box[1][1] == box[2][0]) && checkValue(box[1][1])) {
		*win = box[1][1];
		return true;
	}
	for (int i = 0; i < 3; i++) {
		if (box[i][0] == box[i][1] && box[i][1] == box[i][2] && checkValue(box[i][1])) {
			*win = box[i][1];
			return true;
		}
		if (box[0][i] == box[1][i] && box[1][i] == box[2][i] && checkValue(box[1][i])) {
			*win = box[1][i];
			return true;
		}
	}
	int count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (box[i][j] == '#') {
				count++;
			}
		}
	}
	if (count == 0) {
		*win = '#';
		return true;
	}
	return false;
}
void setBox(int* turn, char box[7][15], char boxValue[4][4], int x, int y, int posX, int posY) {
	char c = (*turn > 0)? 'X' : 'O';
	box[y][x] = c;
	boxValue[posY][posX] = c;
	(*turn)*=-1;
}
int main() {
    int posX = 1, posY = 1, x = 0, y = 0, turn = 1;
    char box[7][15];
    char boxValue[4][4];
    emptyBox(box, boxValue, &turn);
    while (true) {
    	x = posX*4 + 2, y = posY*2 + 1;
    	printBox(box, x, y);
    	printf("\t\t\t  %c's turn", (turn > 0)? 'X' : 'O');
    	char choice = getch();
    	if (choice == 'm' || choice == 'M') {
    		//exit
    		break;
		} else if (choice == 'W' || choice == 'w') {
			if (posY > 0) posY--;
		} else if (choice == 'S' || choice == 's') {
			if (posY < 2) posY++;
		} else if (choice == 'A' || choice == 'a') {
			if (posX > 0) posX--;
		} else if (choice == 'D' || choice == 'd') {
			if (posX < 2) posX++;
		} else if (choice == 'R' || choice == 'r') {
			//reset box
			emptyBox(box, boxValue, &turn);
			resetValue(&posX, &posY);
		} else if (choice == ' ') {
			if (boxValue[posY][posX] == '#') {
				setBox(&turn, box, boxValue, x, y, posX, posY);
				resetValue(&posX, &posY);
			} else {
				continue;
			}
		} else {
			continue;
		}
		char win = ' ';
		bool over = checkWinner(boxValue, &win);
		if (over) {
			printBox(box, -99, -99);
			fflush(stdin);
			if (win == '#') {
				printf("\n\t  Draw, press ENTER to reset.\n");
			} else {
				printf("\n\t%c is the winner, press ENTER to reset.\n", win);
			}
			getchar();
			emptyBox(box, boxValue, &turn);
			resetValue(&posX, &posY);
		}
	}
	system("cls");
	printf("\n\n\n\n");
	puts("		Thank you for playing!");
    printf("\n\n\n\n");
	return 0;
}
