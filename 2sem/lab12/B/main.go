package main

import (
	"bufio"
	"fmt"
	"os"
)

const inf int = 1000000009

func UpperBound(d []int, n, c int) int {
	l, r := 0, n
	for l < r {
		mid := (l + r) / 2
		if c >= d[mid] {
			l = mid + 1
		} else {
			r = mid
		}
	}
	return l
}

func Solve(reader *bufio.Reader, writer *bufio.Writer) {
	var n int
	fmt.Fscanf(reader, "%d\n", &n)
	a := make([]int, n)
	d := make([]int, n+1)
	prev := make([]int, n)
	last := -1

	d[0] = -inf
	for i := 1; i <= n; i++ {
		d[i] = inf
	}
	mx := 1
	for i := 0; i < n; i++ {
		fmt.Fscanf(reader, "%d ", &a[i])
		if found := UpperBound(d, mx, a[i]); d[found-1] < a[i] && d[found] > a[i] {
			d[found] = a[i]
			if found+1 > mx {
				mx = found + 1
				last = i
			}
			prev[i] = d[found-1]
		}
	}

	defer fmt.Fprintf(writer, "\n")
	fmt.Fprintf(writer, "%d\n", mx-1)
	for {
		defer fmt.Fprintf(writer, "%d ", a[last])
		j := last - 1
		for ; j >= 0 && a[j] != prev[last]; j-- {
		}
		if j < 0 || a[j] != prev[last] {
			break
		}
		last = j
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
