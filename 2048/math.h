// Mark Morra
// 2019

#pragma once

int numDigits(int number) //returns the number of digits in a number
{
	if (number == 0) { return 1; }

	int digits = 0;

	while (number != 0) {
		number /= 10;
		digits++;
	}
	return digits;
}
