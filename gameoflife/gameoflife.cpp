#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#define HEIGHT 30
#define WIDTH 30
#define UPDATELENGTH 150000

int board[HEIGHT][WIDTH];
int weightedarray[10] = {0,0,0,0,0,0,0,0,1};

void genBoard(int (board)[HEIGHT][WIDTH]) {
    for (int x = 0; x < HEIGHT; ++x) {
	for (int y = 0; y < WIDTH; ++y) {
	    board[x][y] = weightedarray[rand() % 10];
	}
    }
}

void updateBoard(int (board)[HEIGHT][WIDTH]) {
    for (int x = 0; x < HEIGHT; ++x) {
	for (int y = 0; y < WIDTH; ++y) {
	    int aliveN = 0;
	    int deadN = 0;
	    if (!board[x-1][y+1]) {
		deadN++;
	    } else {
		aliveN++;
	    }
	    if (!board[x][y+1]) {
		deadN++;
	    } else {
		aliveN++;
	    }
	    if (!board[x+1][y+1]) {
		deadN++;
	    } else {
		aliveN++;
	    }
	    if (!board[x+1][y]) {
		deadN++;
	    } else {
		aliveN++;
	    }
	    if (!board[x+1][y-1]) {
		deadN++;
	    } else {
		aliveN++;
	    }
	    if (!board[x][y-1]) {
		deadN++;
	    } else {
		aliveN++;
	    }
	    if (!board[x-1][y-1]) {
		deadN++;
	    } else {
		aliveN++;
	    }
	    if (!board[x-1][y]) {
		deadN++;
	    } else {
		aliveN++;
	    }
	    /*
	      Rules
	      =====

	      1. Any live cell with fewer than two live neighbours
	         dies, as if caused by under-population.

	      2. Any live cell with two or three live neighbours lives
	         on to the next generation.

	      3. Any live cell with more than three live neighbours
	         dies, as if by overcrowding.

	      4. Any dead cell with exactly three live neighbours
	         becomes a live cell, as if by reproduction.
	    */
	    if ((board[x][y] && aliveN < 2)) {
		board[x][y] = 0;
		continue;
	    }
	    if ((board[x][y]) && ((aliveN == 2) || (aliveN == 3)))
		continue;
	    if ((board[x][y]) && (aliveN > 3)) {
		board[x][y] = 0;
		continue;
	    }
	    if ((!board[x][y]) && (aliveN == 3)) {
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
	drawBoard(board);
	usleep(UPDATELENGTH);
    }
    return 0;
}
