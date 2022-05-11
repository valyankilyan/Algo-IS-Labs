package main

import (
	"bufio"
	"fmt"
	"os"
)

func max(a, b int) int {
	if a > b {
		return a
	} else {
		return b
	}
}

func Solve(reader *bufio.Reader, writer *bufio.Writer) {
	var s, n int
	fmt.Fscanf(reader, "%d %d\n", &s, &n)
	weight := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Fscanf(reader, "%d ", &weight[i])
	}
	fmt.Fscanf(reader, "\n")
	a := make([][]int, n+1)
	a[0] = make([]int, s+1)
	for i, w := range weight {
		a[i+1] = make([]int, s+1)
		for j := 1; j <= s; j++ {
			if j > w {
				a[i+1][j] = max(a[i][j], a[i][j-w]+w)
			} else {
				a[i+1][j] = a[i][j]
			}
		}
	}

	fmt.Fprintf(writer, "%d\n", a[n][s])
}

func main() {
	var reader *bufio.Reader
	var writer *bufio.Writer

	filename_in := "knapsack.in"
	filename_out := "knapsack.out"

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
