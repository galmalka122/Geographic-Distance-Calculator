#include <iostream>
#include <fstream>
#include "NearByCities.h"

int main()
{
	ifstream inputFile("data.txt");
	try
	{
		if (!inputFile)
		{
			throw std::runtime_error("Failed to open the file.");
		}
		NearbyCities nbc;
		nbc.addCities(inputFile);
		while (true)
		{
			try
			{
				if (!nbc.run()) break;
			}
			catch (const std::out_of_range& e)
			{
				std::cout << e.what() << std::endl;
			}
			catch (const std::invalid_argument& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}

	catch (const std::exception& e)
	{
		// Catch other general exceptions
		std::cerr << e.what() << std::endl;
		inputFile.clear();
		inputFile.close();
		return EXIT_FAILURE;
	}

	inputFile.close();

	return EXIT_SUCCESS;
}
