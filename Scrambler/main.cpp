// main.cpp: definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"

#include "FileReader.h"
#include "Scrambling.h"
#include "DataTransferSimulator.h"
#include "SimpleBitDataGenerator.h"
#include "Histogram.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>


bool areBothDataSame(std::vector<bool> data1, std::vector<bool> data2)
{
	if (data1.size() != data2.size())
	{
		return false;
	}

	auto sizeOfData{ data1.size() };

	for (int i{ 0 }; i < sizeOfData; i++)
	{
		if (data1[i] != data2[i])
		{
			return false;
		}
	}
	
	return true;
}

void showData(std::vector<bool> data)
{
	for (auto bit : data)
	{
		std::cout << bit << " ";
	}
	std::cout << std::endl;
}

void simulateWith(std::vector<bool> data)
{
	DataTransferSimulator simulation{};
	Scrambling scrambler;
	Histogram histogram;

	
	std::cout << "\n\nBegin simulation 1\n";
	//Przesłanie danych bez scramblera
	std::cout << "Preparing data to send.." << std::endl;
	simulation.setDataToSend(data);
	std::cout << "Sending.." << std::endl;
	simulation.simulateSendingData('B');
	std::cout << "Data sent." << std::endl;

	std::cout << "data size: " << data.size() << std::endl;
	std::cout << "number of bits lost: " << simulation.getNumberOfRandomData() << std::endl;

	//Przesłanie danych ze scramblerem
	std::cout << "Scrambling.." << std::endl;
	auto dataAfterScrambling = scrambler.scrambleAdditive(data);
	std::cout << "Preparing data to send.." << std::endl;
	simulation.setDataToSend(dataAfterScrambling);
	std::cout << "Sending.." << std::endl;
	simulation.simulateSendingData('B');
	std::cout << "Data sent." << std::endl;

	std::cout << "data size: " << dataAfterScrambling.size() << std::endl;
	std::cout << "number of bits lost: " << simulation.getNumberOfRandomData() << std::endl;

	std::cout << "\n\nBegin simulation 2\n";
	//Przesłanie danych bez scramblera
	std::cout << "Preparing data to send.." << std::endl;
	simulation.setDataToSend(data);
	std::cout << "Sending.." << std::endl;
	simulation.simulateSendingData('A');
	std::cout << "Data sent." << std::endl;

	std::cout << "data size: " << data.size() << std::endl;
	std::cout << "number of bits lost: " << simulation.getNumberOfRandomData() << std::endl;

	//Przesłanie danych ze scramblerem
	std::cout << "Scrambling.." << std::endl;
	dataAfterScrambling = scrambler.scrambleAdditive(data);
	std::cout << "Preparing data to send.." << std::endl;
	simulation.setDataToSend(dataAfterScrambling);
	std::cout << "Sending.." << std::endl;
	simulation.simulateSendingData('A');
	std::cout << "Data sent." << std::endl;

	std::cout << "data size: " << dataAfterScrambling.size() << std::endl;
	std::cout << "number of bits lost: " << simulation.getNumberOfRandomData() << std::endl;

	std::cout << "\nHistogramy\n";
	histogram.create(data, 1);
	histogram.create(dataAfterScrambling, 1);
}



int main()
{
	FileReader reader;
	std::cout << "MP3 File Simulation\n";
	simulateWith(reader.readFile("file.mp3"));

	std::cout << "Only Zeros Series Simulation\n";
	simulateWith(SimpleBitDataGenerator::generateData(0, 1000));

	std::cout << "Only Ones Series Simulation\n";
	simulateWith(SimpleBitDataGenerator::generateData(1, 1000));
}

