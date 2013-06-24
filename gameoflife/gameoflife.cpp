#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <ncurses.h>

#define HEIGHT 80
#define WIDTH 180
#define UPDATELENGTH 30000

#define ALIVE '*'
#define DEAD ' '

int board[HEIGHT][WIDTH];

int weightedarray[10] = {0,0,0,0,0,0,0,1,1};

void genBoard(int (board)[HEIGHT][WIDTH]) {

	std::ifstream ifs ("/dev/urandom", std::ifstream::in);

	for (int x = 0; x < HEIGHT; ++x) {
		for (int y = 0; y < WIDTH; ++y) {
			board[x][y] = weightedarray[(int) ifs.get() % 10];
		}
	}
	ifs.close();
}

void copyBoard(int (newB)[HEIGHT][WIDTH], int (oldB)[HEIGHT][WIDTH]) {
	for (int x = 0; x < HEIGHT; ++x) {
		for (int y = 0; y < WIDTH; ++y) {
			newB[x][y] = oldB[x][y];
		}
	}
}

void updateBoard(int (board)[HEIGHT][WIDTH]) {
	int next_board[HEIGHT][WIDTH];
	copyBoard(next_board, board);
	for (int x = 0; x < HEIGHT; ++x) {
		for (int y = 0; y < WIDTH; ++y) {
		    int aliveN = 0;
		    std::vector<int> neighbours = {
			board[x-1][y+1],
			board[x][y+1],
			board[x+1][y+1],
			board[x+1][y],
			board[x+1][y-1],
			board[x][y-1],
			board[x-1][y-1],
			board[x-1][y],
		    };
		    for (auto cell : neighbours) {
			if (cell)
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
			if (board[x][y] == 1 && aliveN < 2) {
				next_board[x][y] = 0;
 				continue;
			}
			if (board[x][y] == 1 && (aliveN == 2 || aliveN == 3))
			        continue;
			if (board[x][y] == 1 && aliveN > 3) {
				next_board[x][y] = 0;
				continue;
			}
			if (!board[x][y] == 1 && aliveN == 3) {
				next_board[x][y] = 1;
				continue;
			}
		}
	}
	copyBoard(board, next_board);
}

void drawBoard(int (board)[HEIGHT][WIDTH]) {
	for (int x = 0; x < HEIGHT; ++x) {
		for (int y = 0; y < WIDTH; ++y) {
			if (board[x][y] == 0) {
				mvaddch(x,y,DEAD);
			} else {
				mvaddch(x,y,ALIVE);
			}
		}
	}
	refresh();
}


int main() {
		initscr();
		noecho();
		genBoard(board);
		int ch;
		timeout(100);
		while (1) {
			ch = getch();
			if (ch == 32) /* spacebar */
				usleep(5);
			else
                usleep(10000);

			updateBoard(board);
			drawBoard(board);
			usleep(UPDATELENGTH);
		}
		endwin();
		return 0;
}
