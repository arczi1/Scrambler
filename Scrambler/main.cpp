// main.cpp: definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"

#include "FileReader.h"
#include "Scrambling.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>


int main()
{
	FileReader fileReader{};
	try
	{
		std::vector<bool> bits{ fileReader.readFile("file.mp3") };
		for (bool bit : bits)
		{
			std::cout << bit << " ";
		}
		std::cout << std::endl << "number of bits: " << bits.size() << std::endl;
	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
	}
	
	std::vector<bool> binarySeries{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0};

	std::cout << "Scrambler" << std::endl << "Przed: ";
	for (bool digit : binarySeries)
	{
		std::cout << digit;
	}
	std::cout << std::endl;

	Scrambling scrambler{};
	binarySeries = scrambler.scrambleAdditive(binarySeries);

	std::cout << "Po:    ";
	for (bool digit : binarySeries)
	{
		std::cout << digit;
	}
	std::cout << std::endl;

	std::cout << "Descrambler" << std::endl << "Przed: ";
	for (bool digit : binarySeries)
	{
		std::cout << digit;
	}
	std::cout << std::endl;

	binarySeries = scrambler.scrambleAdditive(binarySeries);

	std::cout << "Po:    ";
	for (bool digit : binarySeries)
	{
		std::cout << digit;
	}
	std::cout << std::endl;
}

