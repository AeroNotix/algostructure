#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#define HEIGHT 5
#define WIDTH 30
#define UPDATELENGTH 150000

int board[HEIGHT][WIDTH];

void genBoard(int (board)[HEIGHT][WIDTH]) {
    for (int x = 0; x < HEIGHT; ++x) {
	for (int y = 0; y < WIDTH; ++y) {
	    board[x][y] = rand() % 2;
	}
    }
}

void updateBoard(int (board)[HEIGHT][WIDTH]) {
    for (int x = 0; x < HEIGHT; ++x) {
	for (int y = 0; y < WIDTH; ++y) {
	    int aliveN = 0;
	    int deadN = 0;
	    if (board[x-1][y+1] == 0) {
		deadN++;
	    } else {
		aliveN++;
	    }
	    if (board[x][y+1] == 0) {
		deadN++;
	    } else {
		aliveN++;
	    }
	    if (board[x+1][y+1] == 0) {
		deadN++;
	    } else {
		aliveN++;
	    }
	    if (board[x+1][y] == 0) {
		deadN++;
	    } else {
		aliveN++;
	    }
	    if (board[x+1][y-1] == 0) {
		deadN++;
	    } else {
		aliveN++;
	    }
	    if (board[x][y-1] == 0) {
		deadN++;
	    } else {
		aliveN++;
	    }
	    if (board[x-1][y-1] == 0) {
		deadN++;
	    } else {
		aliveN++;
	    }
	    if (board[x-1][y] == 0) {
		deadN++;
	    } else {
		aliveN++;
	    }
	    if ((board[x][y] == 1 && aliveN < 2)) {
		board[x][y] = 0;
		continue;
	    }
	    if ((board[x][y] == 1) && ((aliveN == 2) || (aliveN == 3)))
		continue;
	    if ((board[x][y] == 1) && (aliveN > 3)) {
		board[x][y] = 0;
		continue;
	    }
	    if ((board[x][y] == 0) && (aliveN == 3)) {
		board[x][y] = 1;
		continue;
	    }
	}
    }
}

void drawBoard(int (board)[HEIGHT][WIDTH]) {
    std::cout << "\033[2J\033[1;1H";
    for (int x = 0; x < HEIGHT; ++x) {
	for (int y = 0; y < WIDTH; ++y) {
	    if (board[x][y] == 0) {
		std::cout << ".";
	    } else {
		std::cout << "*";
	    }
	}
	std::cout << std::endl;
    }
}
    

int main() {
    genBoard(board);
    while (1) {
	updateBoard(board);
	usleep(UPDATELENGTH);
	drawBoard(board);
    }
    return 0;
}
