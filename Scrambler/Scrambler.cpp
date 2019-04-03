// Scrambler.cpp: definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>

std::string changeSequency(int pulse)
{
	if (pulse == 1)
		return "00011011";
	else
		return "00011011";
}


//bipolar with 8-zeros substitution
std::vector<bool> B8ZS(std::vector<bool> binaryInput)
{
	int lastPulse{ -1 };
	int zeros; 
	int digitIndex; 
	
	for (bool binaryDigit : binaryInput)
	{
		if (binaryDigit == 0)
		{
			zeros++;
			if (zeros >= 8)
				changeSequency(lastPulse);
		}
		else
		{
			lastPulse *= -1;
			zeros = 0;
		}

		digitIndex++; 
	}
	return; 
}


std::vector<bool> HDB3(std::vector<bool> binaryInput);
std::string setSubstitutionNumbers(int numberOfOnesSinceLastSubstitution);

int main()
{
	std::vector<bool> binarySeries{};
	binarySeries.push_back(1);
	binarySeries.push_back(1);
	binarySeries.push_back(0);
	binarySeries.push_back(0);
	binarySeries.push_back(0);
	binarySeries.push_back(0);
	binarySeries.push_back(0);
	binarySeries.push_back(0);
	binarySeries.push_back(0);
	binarySeries.push_back(0);
	binarySeries.push_back(0);
	binarySeries.push_back(0);
	binarySeries.push_back(1);
	binarySeries.push_back(0);
	binarySeries.push_back(0);
	binarySeries.push_back(0);
	binarySeries.push_back(0);
	binarySeries.push_back(1);

	for (bool digit : binarySeries)
	{
		std::cout << digit;
	}
	std::cout << std::endl;

	binarySeries = HDB3(binarySeries);

	for (bool digit : binarySeries)
	{
		std::cout << digit;
	}
}

std::vector<bool> HDB3(std::vector<bool> binaryInput)
{
	int numberOfOnesSinceLastSubstitution{};
	//int lastPulse{-1};
	int numberOfZerosSinceLastOne{};
	int actualDigitIndex{};

	for (bool binaryDigit : binaryInput)
	{
		if (binaryDigit == 1)
		{
			//lastPulse *= -1;
			numberOfOnesSinceLastSubstitution++;
			numberOfZerosSinceLastOne = 0;
		}
		else
		{
			numberOfZerosSinceLastOne++;
		}

		std::string newNumbers{setSubstitutionNumbers(numberOfOnesSinceLastSubstitution)};

		if (numberOfZerosSinceLastOne == 4)
		{
			numberOfZerosSinceLastOne = 0;
			std::cout << "zamiana" << std::endl;
			binaryInput[actualDigitIndex] = newNumbers[3]; 
			binaryInput[actualDigitIndex] = newNumbers[2];
			binaryInput[actualDigitIndex] = newNumbers[1]; 
			binaryInput[actualDigitIndex] = newNumbers[0];
		}

		actualDigitIndex++;
	}
	
	return binaryInput;
}

std::string setSubstitutionNumbers(int numberOfOnesSinceLastSubstitution)
{
	if (numberOfOnesSinceLastSubstitution % 2)
	{
		//odd
		return "0001";
	}
	else
	{
		//even
		return "1001";
	}

    return 0;
}

