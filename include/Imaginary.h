#pragma once

struct Imaginary {
	double imaginary;
	double real;

	Imaginary();
	Imaginary(double r, double i);
	Imaginary(Imaginary* b);

	void add(Imaginary& b);
	void multiply(Imaginary& b);
	void square();
	void printVal();
};
