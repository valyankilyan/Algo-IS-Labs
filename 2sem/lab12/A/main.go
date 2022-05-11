package main

import (
	"bufio"
	"fmt"
	"os"
)

const inf int = 1000000009

func Solve(reader *bufio.Reader, writer *bufio.Writer) {
	var n int
	fmt.Fscanf(reader, "%d\n", &n)
	a := make([]int, n)
	d := make([]int, n)
	prev := make([]int, n)
	max := 0

	for i := 0; i < n; i++ {
		fmt.Fscanf(reader, "%d ", &a[i])
		d[i] = 1
		prev[i] = -1
		for j := 0; j < i; j++ {
			if a[j] < a[i] && d[j] >= d[i] {
				prev[i] = j
				d[i] = d[j] + 1
			}
		}
		if d[i] > d[max] {
			max = i
		}
	}

	defer fmt.Fprintf(writer, "\n")
	fmt.Fprintf(writer, "%d\n", d[max])
	for i := max; ; i = prev[i] {
		defer fmt.Fprintf(writer, "%d ", a[i])
		if prev[i] == -1 {
			break
		}
	}
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
		fmt.Fprintf(writer, "\n")
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
