#pragma once

int numDigits(int number)
{
	if (number == 0) { return 1; }

	int digits = 0;

	while (number != 0) {
		number /= 10;
		digits++;
	}
	return digits;
}