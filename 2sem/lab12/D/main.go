package main

import (
	"bufio"
	"fmt"
	"os"
)

var desk [][]int
var steps []Cords = []Cords{
	{2, 1},
	{2, -1},
	{1, 2},
	{-1, 2},
}

func is_possible(x, y int) bool {
	return x >= 0 && y >= 0 && x < len(desk) && y < len(desk[x])
}

func is_end(x, y int) bool {
	return x == len(desk)-1 && y == len(desk[x])-1
}

type Cords struct {
	x, y int
}

type Queue []Cords

func (q *Queue) Push(c Cords) {
	*q = append(*q, c)
}

func (q Queue) Get() Cords {
	return q[0]
}

func (q *Queue) Pop() Cords {
	var ans Cords
	ans, *q = (*q)[0], (*q)[1:]
	return ans
}

func Solve(reader *bufio.Reader, writer *bufio.Writer) {
	var n, m int
	fmt.Fscanf(reader, "%d %d\n", &n, &m)
	desk = make([][]int, n)
	for i := 0; i < n; i++ {
		desk[i] = make([]int, m)
	}
	q := Queue{}
	desk[0][0] = 1
	q.Push(Cords{0, 0})
	for len(q) > 0 {
		c := q.Pop()
		// fmt.Println(c)
		if is_end(c.x, c.y) {
			continue
		}
		for _, s := range steps {
			if is_possible(c.x+s.x, c.y+s.y) {
				q.Push(Cords{c.x + s.x, c.y + s.y})
				desk[c.x+s.x][c.y+s.y]++
			}
		}
	}
	fmt.Fprintf(writer, "%d\n", desk[n-1][m-1])
}

func main() {
	var reader *bufio.Reader
	var writer *bufio.Writer

	filename_in := "knight2.in"
	filename_out := "knight2.out"

	stdinout := false
	readtests := false
	tests := 1

	if (!stdinout || inArgs("local")) && !inArgs("std") {
		infile, inerr := os.Open(filename_in)
		if inerr != nil {
			if os.IsNotExist(inerr) {
				os.Create(filename_in)
			}
			fmt.Println(inerr)
			return
		}
		defer infile.Close()

		outfile, outerr := os.OpenFile(filename_out, os.O_WRONLY, os.ModeAppend)
		if outerr != nil {
			if os.IsNotExist(outerr) {
				outfile, outerr = os.Create(filename_out)
				if outerr != nil {
					fmt.Println(outerr)
					return
				}
			}
		}
		defer outfile.Close()

		reader = bufio.NewReader(infile)
		writer = bufio.NewWriter(outfile)
	} else if stdinout || inArgs("std") {
		reader = bufio.NewReader(os.Stdin)
		writer = bufio.NewWriter(os.Stdout)
	}
	defer func() {
		err := writer.Flush()
		if err != nil {
			fmt.Println(err)
		}
	}()

	if readtests || inArgs("local") {
		fmt.Fscanf(reader, "%d\n\n", &tests)
	}

	for i := 0; i < tests; i++ {
		Solve(reader, writer)
		fmt.Fscanf(reader, "\n")
	}

}

func inArgs(arg string) bool {
	for _, a := range os.Args {
		if a == arg {
			return true
		}
	}
	return false
}
