// Scrambler.cpp: definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>

std::vector<bool> scramble(std::vector<bool> input);
std::vector<bool> createSyncWord(int length);

int main()
{
	std::ifstream file{ "file.mp3", std::ios::in | std::ios::binary };

	if (!file.is_open())
	{
		std::cout << "Error while reading file";
		return 0;
	}
	int numOfNums{};
	file.seekg(0);
	char c{};
	while (file.get(c))
	{
		std::string binary{ std::bitset<16>(static_cast<int16_t>(c)).to_string() };
		//std::cout << static_cast<int16_t>(c) << " ";
		std::cout << binary << " ";
		numOfNums++;
	}
	std::cout << std::endl << "num of nums: " << numOfNums << std::endl;

	std::vector<bool> binarySeries{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0};



	std::cout << "Scrambler" << std::endl;
	std::cout << "Przed: ";
	for (bool digit : binarySeries)
	{
		std::cout << digit;
	}

	std::cout << std::endl;

	binarySeries = scramble(binarySeries);

	std::cout << "Po:    ";
	for (bool digit : binarySeries)
	{
		std::cout << digit;
	}
	std::cout << std::endl;

	std::cout << "Descrambler" << std::endl;
	std::cout << "Przed: ";
	for (bool digit : binarySeries)
	{
		std::cout << digit;
	}
	std::cout << std::endl;

	binarySeries = scramble(binarySeries);

	std::cout << "Po:    ";
	for (bool digit : binarySeries)
	{
		std::cout << digit;
	}
	std::cout << std::endl;
}

//additive scrambler
std::vector<bool> scramble(std::vector<bool> input)
{
	int inputLength{ static_cast<int>(input.size()) };
	std::vector<bool> syncWord{ createSyncWord(inputLength) };
	
	std::vector<bool> scrambledInput;

	bool lastSyncWordBit{};
	for (int i{}; i < inputLength; i++)
	{
		lastSyncWordBit = syncWord[14];
		bool scrambledBit{ static_cast<bool>(((int)input[i] + (int)lastSyncWordBit) % 2) };
		scrambledInput.push_back(scrambledBit);

		for (int i{ inputLength - 1 }; i > 0; i--)
		{
			syncWord[i] = syncWord[i - 1];
		}
		syncWord[0] = lastSyncWordBit;
	}

	return scrambledInput;
}

std::vector<bool> createSyncWord(int length)
{
	std::vector<bool> syncWord{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1 };

	return syncWord;
}

