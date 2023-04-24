#include "utilities.h"
#include <iostream>
#include <cmath>

// The following code is provided as part of the exam in TDT4102
// You are not required to read or understand it.

// We use the following code to perform linear interpolation on RGB Colors.

unsigned char lerp(std::uint8_t begin, std::uint8_t end, std::uint8_t n, std::uint8_t N)
{
	// Linear interpolation
	// Returns a number in the interval [begin, end]
	// with N total steps ([0, N-1])
	// n = 0 => begin
	// n = N => end
	return (end - begin) * n / N + begin;
}

TDT4102::Color lerp_rgb(TDT4102::Color begin, TDT4102::Color end, std::uint8_t n, std::uint8_t N)
{

	unsigned char r = lerp(begin.redChannel, end.redChannel, n, N);
	unsigned char g = lerp(begin.greenChannel, end.greenChannel, n, N);
	unsigned char b = lerp(begin.blueChannel, end.blueChannel, n, N);

	return TDT4102::Color(r, g, b);
}