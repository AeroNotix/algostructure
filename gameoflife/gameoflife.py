import random
from time import sleep
import copy

HEIGHT = 80
WIDTH = 80
ALIVE = '*'
DEAD = ' '

weightedchoice = [0,0,0,0,0,0,0,1,1,1]

def genBoard():
    b = []
    for row in range(HEIGHT):
        b.append([weightedchoice[random.randint(0,9)] for _ in range(WIDTH)])
    return b

def emptyBoard():
    b = []
    for row in range(HEIGHT):
        b.append([[0] for _ in range(WIDTH)])
    return b
        
def printBoard(board):
    print "\033[2J\033[11H"    
    for row in board:
        out = ''
        for col in row:
            if col:
                out += ALIVE
            else:
                out += DEAD
        print out

def updateBoard(board):
    next_board = copy.deepcopy(board)
    for x in range(HEIGHT):
        for y in range(WIDTH):
            try:
                aliveN = 0
                neighbours = [
                    board[x-1][y+1],
                    board[x][y+1],
                    board[x+1][y+1],
                    board[x+1][y],
                    board[x+1][y-1],
                    board[x][y-1],
                    board[x-1][y-1],
                    board[x-1][y]
                    ]
                for cell in neighbours:
                    if cell:
                        aliveN += 1
            except IndexError:
                pass

            if (board[x][y] == 1) and (aliveN < 2):
		next_board[x][y] = 0
		continue
	    if (board[x][y] == 1) and (aliveN == 2 or aliveN == 3):
		continue
	    if (board[x][y] == 1) and (aliveN > 3):
		next_board[x][y] = 0
                continue
	    if (board[x][y] == 0) and (aliveN == 3):
		next_board[x][y] = 1
		continue
    return next_board

board = genBoard()
while 1:
    printBoard(board)
    sleep(0.1)
    board = updateBoard(board)


