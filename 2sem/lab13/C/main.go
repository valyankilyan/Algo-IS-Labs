package main

import (
	"bufio"
	"fmt"
	"os"
)

func Solve(reader *bufio.Reader, writer *bufio.Writer) {
	var str string
	fmt.Fscanf(reader, "%s ", &str)
	pi := make([]int, len(str))
	for i := 1; i < len(str); i++ {
		j := pi[i-1]
		for j > 0 && str[i] != str[j] {
			j = pi[j-1]
		}
		if str[i] == str[j] {
			j++
		}
		pi[i] = j
	}
	for _, p := range pi {
		fmt.Fprintf(writer, "%d ", p)
	}
	fmt.Fprintf(writer, "\n")
}

func main() {
	var reader *bufio.Reader
	var writer *bufio.Writer

	filename_in := "prefix.in"
	filename_out := "prefix.out"

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
