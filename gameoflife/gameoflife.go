package main

import (
	"fmt"
	"math/rand"
	"strings"
	"time"
)

const (
	HEIGHT       = 40
	WIDTH        = 80
	UPDATELENGTH = 30000
	ALIVE        = '*'
	DEAD         = ' '
)

var (
	board         = [HEIGHT][WIDTH]int{}
	weightedarray = [10]int{0, 0, 0, 0, 0, 0, 0, 1, 1}
)

func genBoard(board *[HEIGHT][WIDTH]int) {
	for x := 0; x < HEIGHT; x++ {
		for y := 0; y < WIDTH; y++ {
			board[x][y] = weightedarray[rand.Intn(10)]
		}
	}
}

func copyBoard(newB *[HEIGHT][WIDTH]int, oldB [HEIGHT][WIDTH]int) {
	for x := 0; x < HEIGHT; x++ {
		for y := 0; y < WIDTH; y++ {
			newB[x][y] = oldB[x][y]
		}
	}
}

func clearscreen() {
	fmt.Print(strings.Repeat(string(rune(10)), WIDTH*HEIGHT))
}

func updateBoard(board [HEIGHT][WIDTH]int) {
	next_board := [HEIGHT][WIDTH]int{}
	copyBoard(&next_board, board)
	for x := 2; x < HEIGHT; x++ {
		for y := x; y < WIDTH; y++ {
			aliveN := 0
			if !checkbounds(x, y) {
				continue
			}
			neighbours := []int{
				board[x-1][y+1],
				board[x][y+1],
				board[x+1][y+1],
				board[x+1][y],
				board[x+1][y-1],
				board[x][y-1],
				board[x-1][y-1],
				board[x-1][y],
			}

			for _, cell := range neighbours {
				if cell > 0 {
					aliveN++
				}
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
			if board[x][y] == 1 && aliveN < 2 {
				next_board[x][y] = 0
				continue
			}
			if board[x][y] == 1 && (aliveN == 2 || aliveN == 3) {
				continue
			}
			if board[x][y] == 1 && aliveN > 3 {
				next_board[x][y] = 0
				continue
			}
			if board[x][y] != 1 && aliveN == 3 {
				next_board[x][y] = 1
				continue
			}
		}
	}
	copyBoard(&board, next_board)
}

func drawBoard(board [HEIGHT][WIDTH]int) {
	for x := 0; x < HEIGHT; x++ {
		for y := 0; y < WIDTH; y++ {
			if board[x][y] == 0 {
				fmt.Print("0")
			} else {
				fmt.Print("X")
			}
		}
		fmt.Println()
	}
}

func checkbounds(x, y int) bool {
	if x+1 >= HEIGHT || x-1 <= 0 {
		return false
	}
	if y+1 >= WIDTH || y-1 <= 0 {
		return false
	}
	return true
}

func main() {
	genBoard(&board)
	drawBoard(board)
	for {
		time.Sleep(10000000)
		updateBoard(board)
		drawBoard(board)
		clearscreen()
	}
}
