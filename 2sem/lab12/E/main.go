package main

import (
	"bufio"
	"fmt"
	"os"
)

type possibilities struct {
	in  int
	out int
}

var kids [][]int
var pos []possibilities

func Max(a, b int) int {
	if a > b {
		return a
	} else {
		return b
	}
}

func dfs(v int) {
	if len(kids[v]) == 0 {
		pos[v].in = 1
		pos[v].out = 0
		return
	}

	for _, k := range kids[v] {
		dfs(k)
		if pos[k].in < pos[k].out {
			pos[v].out += pos[k].out
		} else {
			pos[v].out += pos[k].in
		}
		pos[v].in += pos[k].out
	}
	pos[v].in++

}

func Solve(reader *bufio.Reader, writer *bufio.Writer) {
	var n int
	fmt.Fscanf(reader, "%d\n", &n)
	// parent := make([]int, n)
	kids = make([][]int, n)
	pos = make([]possibilities, n)
	var root int

	for i := 0; i < n; i++ {
		var parent int
		fmt.Fscanf(reader, "%d\n", &parent)
		if parent != 0 {
			kids[parent-1] = append(kids[parent-1], i)
		} else {
			root = i
		}
	}

	dfs(root)

	fmt.Fprintf(writer, "%d\n", Max(pos[root].in, pos[root].out))
}

func main() {
	var reader *bufio.Reader
	var writer *bufio.Writer

	filename_in := "data.in"
	filename_out := "data.out"

	stdinout := true
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
