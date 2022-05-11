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

type index struct {
	i, j int16
}

type bitarray struct {
	colums int
	rows   int
	bits   []byte
}

// func (ba *bitarray) NewBitArray(n, m int) {
// 	ba.bits = make([]byte, n*m/8+1)
// }

// func (ba *bitarray) Put(x, y int, up, left bool) {
// 	bits[(x*ba.rows+y)*2] = up
// }

// func (ba *bitarray) Get(x, y int) (bool, bool) {
// 	return
// }

func Solve(reader *bufio.Reader, writer *bufio.Writer) {
	// var str1, str2 string
	// fmt.Fscanf(reader, "%s\n%s\n", &str1, &str2)
	// m := make([][]int16, len(str1)+1)
	// // prev := make([][]byte, len(str1)+1)
	// prev := NewBitArray(((len(str1) + 1) * (len(str2) + 1)) * 2)
	// m[0] = make([]int16, len(str2)+1)
	// prev[0] = make([]byte, len(str2)+1)
	// mx := index{0, 0}
	// for i, s1 := range str1 {
	// 	prev[i+1] = make([]byte, len(str2)+1)
	// 	m[i+1] = make([]int16, len(str2)+1)
	// 	for j, s2 := range str2 {
	// 		if s1 == s2 {
	// 			m[i+1][j+1] = m[i][j] + 1
	// 			prev[i+1][j+1] = 3
	// 			if m[i+1][j+1] > m[mx.i][mx.j] {
	// 				mx.i = int16(i + 1)
	// 				mx.j = int16(j + 1)
	// 			}
	// 		} else {
	// 			if m[i][j+1] > m[i+1][j] {
	// 				m[i+1][j+1] = m[i][j+1]
	// 				prev[i+1][j+1] = 2
	// 			} else {
	// 				m[i+1][j+1] = m[i+1][j]
	// 				prev[i+1][j+1] = 1
	// 			}
	// 		}
	// 	}
	// }

	// // for _, a := range m {
	// // 	for _, b := range a {
	// // 		fmt.Printf("%d ", b)
	// // 	}
	// // 	// fmt.Println()
	// // }
	// // fmt.Println()
	// // for _, a := range prev {
	// // 	for _, b := range a {
	// // 		switch b {
	// // 		case 0:
	// // 			fmt.Printf(". ")
	// // 		case 1:
	// // 			fmt.Printf("→ ")
	// // 		case 2:
	// // 			fmt.Printf("↓ ")
	// // 		case 3:
	// // 			fmt.Printf("↘ ")
	// // 		}
	// // 	}
	// // 	// fmt.Println()
	// // }

	// pr := prev[mx.i][mx.j]
	// for m[mx.i][mx.j] != 0 {

	// 	pr = prev[mx.i][mx.j]
	// 	if pr == 3 {
	// 		defer fmt.Fprintf(writer, "%c", str1[mx.i-1])
	// 	}
	// 	mx.j -= int16(pr % 2)
	// 	mx.i -= int16(pr / 2)
	// 	// fmt.Println("pr", pr, "i", pr%2, "j", pr/2, "ans", mx.i, mx.j)
	// }
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
			return
		}
		defer infile.Close()

		// outfile, outerr := os.OpenFile(filename_out, os.O_WRONLY, os.ModeAppend)
		outfile, outerr := os.Create(filename_out)
		if outerr != nil {
			if os.IsNotExist(outerr) {
				outfile, outerr = os.Create(filename_out)
				if outerr != nil {
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
