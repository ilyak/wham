# WHAM - Weighted Histogram Analysis Method

This program implements Weighted Histogram Analysis Method.

WHAM allows you to calculate the Potential of Mean Force from a series of
constrained molecular dynamics simulations. The algorithm used in this program
is described in reference [1].

### Compilation

Use standard make utility to compile the program:

	make

The program can be tested using the included butane sample:

	wham -v -p 6.28 -i butane.dat > butane.out
	diff butane.out butane.ref

### Program Options

To obtain the description of program options use the following command:

	wham --help

### Input Format Description

Input data is assumed to be in free format. White space is not meaningful.
Lines at the beginning of input which are empty (no white space allowed on
these lines) or which start with '#' symbol will be ignored. The following
data are expected in input:

	Integer (m)
		Number of windows.

	Repeat (m) times:

		Floating point
			The coordinate value of the center of biasing
			potential for the current window (this value is
			named x0 in the expression below).

		Floating point
			The value of biasing constant (this value is named
			k in the expression below).

		Integer (n)
			Number of data points.

		Repeat (n) times:

			Floating point
				Distribution of the coordinate for the
				current window (this value is named x in the
				expression below).

For a sample input, see butane.dat file.

The biasing potential used in molecular dynamic simulations is assumed to
be in standard quadratic form:

	U = 1/2 * k * (x - x0) * (x - x0)

Be sure to account for 1/2 in front of the biasing constant in case your
biasing potential does not include it.

### References

1. Benoit Roux. The calculation of the potential of mean force using
computer simulations. Computer Physics Communications 91 (1995), 275-282.
