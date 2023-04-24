#pragma once

#include <cmath>
#include <cstdlib>
#include "AnimationWindow.h"

// The following code is provided as part of the exam in TDT4102
// You are not required to read or understand it.

unsigned char lerp(std::uint8_t begin, std::uint8_t end, std::uint8_t n, std::uint8_t N);

TDT4102::Color lerp_rgb(TDT4102::Color begin, TDT4102::Color end, std::uint8_t n, std::uint8_t N);
