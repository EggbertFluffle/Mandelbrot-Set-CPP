#include <iostream>

#include "../include/Imaginary.h"

Imaginary::Imaginary() {
	real = 0.0;
	imaginary = 0.0;
}

Imaginary::Imaginary(double r, double i) {
	real = r;
	imaginary = i;
}

Imaginary::Imaginary(Imaginary* b) {
	real = b->real;
	imaginary = b->imaginary;
}

void Imaginary::add(Imaginary& b) {
	imaginary += b.imaginary;
	real += b.real;
}

void Imaginary::multiply(Imaginary& b) {
	double r = (real * b.real) - (imaginary * b.imaginary);
	double i = (imaginary * b.real) + (real * b.imaginary);
	real = r;
	imaginary = i;
}

void Imaginary::square() {
	multiply(*this);
}

void Imaginary::printVal() {
	std::cout << real << " + " << imaginary << "i";
}
