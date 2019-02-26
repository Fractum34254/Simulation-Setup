#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

std::string ReadNumberStr(std::string question)
{
	bool tempB = false;
	std::string tempS;
	do {
		std::cout << question;
		std::cin >> tempS;
		try
		{
			int tempI = std::stoi(tempS);
			tempB = false;
		}
		catch (const std::exception&)
		{
			std::cout << "That is not a number. Please enter again.\n";
			tempS = "";
			tempB = true;
		}
	} while (tempB);
	return tempS;
}
int ReadNumberInt(std::string question)
{
	bool tempB = false;
	int tempI;
	do {
		std::cout << question;
		std::string tempS;
		std::cin >> tempS;
		try
		{
			tempI = std::stoi(tempS);
			tempB = false;
		}
		catch (const std::exception&)
		{
			std::cout << "That is not a number. Please enter again.\n";
			tempB = true;
		}
	} while (tempB);
	return tempI;
}
int ReadNumberIntRestricted(std::string question, int low, int high)
{
	int i;
	bool tempB = false;
	do
	{
		i = ReadNumberInt(question);
		if (i < low || i > high)
		{
			tempB = true;
			std::cout << "This number is not in range from " << low << " to " << high << ".\n";
		}
		else
		{
			tempB = false;
		}
	} while (tempB);
	return i;
}
std::string ReadNumberStrRestricted(std::string question, int low, int high)
{
	std::stringstream ss;
	ss << ReadNumberIntRestricted(question, low, high);
	return ss.str();
}

int main()
{
	/****************************************************** DEKLARATION OF CONSTANTS ********************************************************************/
	//deklaration of strings
	std::string name;
	std::string time;
	std::string yValues;
	std::string repeating;
	std::string axisColor;
	std::string graphColor;
	//definition of constant strings
	const std::string axisColorSet = "Axis Color:";
	const std::string graphColorSet = "Graph Color:";
	const std::string yNameSet = "y Values:";
	const std::string timeName = "Time variable:";
	const std::string repeatingName = "Repeating per second:";
	const std::string settingsEnd = "#Head";
	const std::string headEnd = "#Program";
	const std::string settingsFileName = "files.txt";

	/****************************************************** USERT INTERFACE START ********************************************************************/
	{
		/****************************************************** NAME ********************************************************************/
		{
			std::cout << "What should your new simulation be called?\n";
			std::cin >> name;
			std::string nameDouble = name;
			std::string lastChars;
			if (nameDouble.size() <= 4)
			{
				name += ".txt";
			}
			else {
				for (int i = 0; i < 4; i++)
				{
					lastChars += nameDouble.back();
					nameDouble.pop_back();
				}
				if (lastChars != "txt.")
				{
					name += ".txt";
				}
			}
		}
		/****************************************************** TIME VARIABLE ********************************************************************/
		{
			std::cout << "Which name does your time variable have?\n";
			std::cin >> time;
		}
		/****************************************************** Y VARIABLES ********************************************************************/
		{
			int nIYVars = ReadNumberInt("How many different variables do you want to feature on y axis?\n");
			for (int i = 0; i < nIYVars; )
			{
				std::cout << "Enter your " << ++i << ". y variable! ";
				std::string temp;
				std::cin >> temp;
				yValues += temp + " ";
			}
			yValues.pop_back();
		}
		/****************************************************** REPEATING VALUE ********************************************************************/
		{
			repeating = ReadNumberStr("How often should the program execute your code per second at the start?\n(speed adjustment possible in the program, too)\n");
		}
		/****************************************************** AXIS COLOR ********************************************************************/
		{
			bool tempB = false;
			do {
				std::cout << "Next, enter the color of the axis, please. Do you want to type it in as RGB values?\n";
				std::string tempS;
				std::cin >> tempS;
				if (tempS == "Yes" || tempS == "yes")
				{
					tempB = false;
					axisColor += ReadNumberStrRestricted("Now enter the 'red' part: ", 0, 255) + " ";
					axisColor += ReadNumberStrRestricted("Now enter the 'green' part: ", 0, 255) + " ";
					axisColor += ReadNumberStrRestricted("Now enter the 'blue' part: ", 0, 255);
				}
				else if (tempS == "No" || tempS == "no")
				{
					tempB = false;
					std::string tempS;
					tempS += "These colors are available:\n";
					tempS += "White (1) - Gray (2) - Light Gray (3) - Red (4) - Green (5)\nBlue (6) - Yellow (7) - Cyan (8) - Magenta (9) - Orange (10)\n";
					tempS += "Please pick yours and enter the specific number!\n";
					int tempI = ReadNumberIntRestricted(tempS, 1, 10);
					switch (tempI)
					{
					case 1:
						axisColor = "255 255 255";
						break;
					case 2:
						axisColor = "128 128 128";
						break;
					case 3:
						axisColor = "211 211 211";
						break;
					case 4:
						axisColor = "255 0 0";
						break;
					case 5:
						axisColor = "0 255 0";
						break;
					case 6:
						axisColor = "0 0 255";
						break;
					case 7:
						axisColor = "255 255 0";
						break;
					case 8:
						axisColor = "0 255 255";
						break;
					case 9:
						axisColor = "255 0 255";
						break;
					case 10:
						axisColor = "255 110 13";
						break;
					}
				}
				else
				{
					tempB = true;
					std::cout << "Didn't understand you. Sorry :(\nPlease enter 'yes' or 'no'.\n";
				}
			} while (tempB);
		}
		/****************************************************** GRAPH COLOR ********************************************************************/
		
		{
			bool tempB = false;
			do {
				std::cout << "Last step: enter the color of the graph, please. Do you want to type it in as RGB values?\n";
				std::string tempS;
				std::cin >> tempS;
				if (tempS == "Yes" || tempS == "yes")
				{
					tempB = false;
					graphColor += ReadNumberStrRestricted("Now enter the 'red' part: ", 0, 255) + " ";
					graphColor += ReadNumberStrRestricted("Now enter the 'green' part: ", 0, 255) + " ";
					graphColor += ReadNumberStrRestricted("Now enter the 'blue' part: ", 0, 255);
				}
				else if (tempS == "No" || tempS == "no")
				{
					tempB = false;
					std::string tempS;
					tempS += "These colors are available:\n";
					tempS += "White (1) - Gray (2) - Light Gray (3) - Red (4) - Green (5)\nBlue (6) - Yellow (7) - Cyan (8) - Magenta (9) - Orange (10)\n";
					tempS += "Please pick yours and enter the specific number!\n";
					int tempI = ReadNumberIntRestricted(tempS, 1, 10);
					switch (tempI)
					{
					case 1:
						graphColor = "255 255 255";
						break;
					case 2:
						graphColor = "128 128 128";
						break;
					case 3:
						graphColor = "211 211 211";
						break;
					case 4:
						graphColor = "255 0 0";
						break;
					case 5:
						graphColor = "0 255 0";
						break;
					case 6:
						graphColor = "0 0 255";
						break;
					case 7:
						graphColor = "255 255 0";
						break;
					case 8:
						graphColor = "0 255 255";
						break;
					case 9:
						graphColor = "255 0 255";
						break;
					case 10:
						graphColor = "255 110 13";
						break;
					}
				}
				else
				{
					tempB = true;
					std::cout << "Didn't understand you. Sorry :(\nPlease enter 'yes' or 'no'.\n";
				}
			} while (tempB);
		}
		/****************************************************** FILES.TXT ********************************************************************/
		{
			std::ifstream settingsFile(settingsFileName);
			if (settingsFile)
			{
				std::string setFile;
				while (!settingsFile.eof())
				{
					std::string tempS;
					settingsFile >> tempS;
					setFile += tempS + "\n";
				}
				std::ofstream settingsFileOut(settingsFileName);
				setFile += name;
				setFile.shrink_to_fit();
				settingsFileOut.write(setFile.c_str(), setFile.size());
				std::cout << "Succesfully added this new simulation to your 'files.txt'\n";
			}
			else
			{
				bool tempB = false;
				do {
					std::cout << "There is no 'files.txt'. Would you like to create it?\n";
					std::string tempS;
					std::cin >> tempS;
					if (tempS == "Yes" || tempS == "yes")
					{
						std::ofstream newSettingsFile(settingsFileName);
						newSettingsFile << name;
						std::cout << "Succesfully created a new 'files.txt' for you.\n";
					}
					else if (tempS == "No" || tempS == "no")
					{
						std::cout << "Then you have to add '" << name << "' to your 'files.txt' yourself in order to make it working.\n";
					}
					else
					{
						tempB = true;
						std::cout << "Didn't understand you. Sorry :(\nPlease enter 'yes' or 'no'.\n";
					}
				} while (tempB);
			}
		}
		/****************************************************** SYNTAX INFORMATION ********************************************************************/
		{
			bool tempB = false;
			do {
				std::cout << "You now just have to set up\n-the start variables of your code (between '#Head' and '#Program') and\n-the code itself(after '#Program')\n";
				std::cout << "Shall I inform you about some syntax?\n";
				std::string tempS;
				std::cin >> tempS;
				if (tempS == "Yes" || tempS == "yes")
				{
					tempB = false;
					std::cout << "\nFirst, you are able to use commentaries. Just put '//' in front of a line.\n";
					std::cout << "Second, you have the possibility to use 'sin', 'cos', 'tan' and 'sqrt' (which is the square root) in front of braces.\n";
					std::cout << "Third, if-statements are also an option: just write 'if (-condition-) -term-'!\n\n";
					std::cout << "If you do something wrong, the program will let you know: There are plenty of exceptions build-in.\nRead them carefully to gain as much information about the problem as possible.\nIf you can't find it, contact me and I'll try to help.\n\n";
					std::cout << "Now have fun with your simulation!";
				}
				else if (tempS == "No" || tempS == "no")
				{
					tempB = false;
					std::cout << "Well, then have fun with your new simulation!";
				}
				else
				{
					tempB = true;
					std::cout << "Didn't understand you. Sorry :(\nPlease enter 'yes' or 'no'.\n";
				}
			} while (tempB);
		}
	}
	/****************************************************** CREATING FILE ********************************************************************/
	std::ofstream file(name);
	file << axisColorSet << " " << axisColor << "\n";
	file << graphColorSet << " " << graphColor << "\n";
	file << yNameSet << " " << yValues << "\n";
	file << timeName << " " << time << "\n";
	file << repeatingName << " " << repeating << "\n";
	file << settingsEnd << "\n";
	file << headEnd;

	/****************************************************** END ********************************************************************/
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
}
