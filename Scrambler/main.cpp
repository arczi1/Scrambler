// main.cpp: definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"

#include "FileReader.h"
#include "Scrambling.h"
#include "DataTransferSimulator.h"
#include "SimpleBitDataGenerator.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>


void showData(std::vector<bool> data)
{
	for (auto bit : data)
	{
		std::cout << bit << " ";
	}
	std::cout << std::endl;
}

void simulateWith000()
{
	auto data{ SimpleBitDataGenerator::generateData(0, 1000) };
}

void simulateWith111()
{

}

void simulateWithMp3()
{

}

int main()
{
	FileReader fileReader{};
	auto mp3Binary{ fileReader.readFile("file.mp3") };
	//std::vector<bool> mp3Binary{ 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 , 0, 1, 0, 0, 0, 0, 0, 1 };
	//auto mp3Binary{SimpleBitDataGenerator::generateData(0, 1000)};

	DataTransferSimulator simulation{};
	simulation.setDataToSend(mp3Binary);
	simulation.simulateSendingData();

	std::cout << "mp3 binary size: " << mp3Binary.size() << std::endl;
	std::cout << "number of bits lost: " << simulation.getNumberOfRandomData() << std::endl;

	auto binarySeriesAfterSim{ simulation.getDataAfterSimulation() };


	Scrambling scrambler;
	std::cout << "Scrambling.." << std::endl;
	auto mp3BinaryAfterScrambling = scrambler.scrambleAdditive(mp3Binary);
	
	
	std::cout << "Preparing data to send.." << std::endl;
	simulation.setDataToSend(mp3BinaryAfterScrambling);
	std::cout << "Sending.." << std::endl;
	simulation.simulateSendingData();
	std::cout << "Data sent." << std::endl;
	std::cout << "number of bits lost: " << simulation.getNumberOfRandomData() << std::endl;

	fileReader.saveToFile(binarySeriesAfterSim, "savedMp3.mp3");
}

