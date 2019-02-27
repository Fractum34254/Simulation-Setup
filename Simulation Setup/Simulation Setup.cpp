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
			std::cout << "Das ist keine Zahl. Bitte gibt es erneut ein.\n";
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
			std::cout << "Das ist keine Zahl. Bitte gibt es erneut ein.\n";
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
			std::cout << "Diese Zahl liegt nicht zwischen " << low << " und " << high << ".\n";
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

template<typename T>
std::string Crop(T in, unsigned int n)
{
	std::stringstream s_in;
	s_in << in;
	std::string sstr = s_in.str();
	while (sstr.length() < n)
	{
		sstr += " ";
	}
	while (sstr.length() > n)
	{
		sstr.pop_back();
	}
	return sstr;
}

void WhiteLine()
{
	std::cout << "\n";
}

int main()
{
	/****************************************************** DEKLARATION OF CONSTANTS ********************************************************************/
	//deklaration of numbers
	const unsigned int maxLength = 80;
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
			std::cout << Crop("Was soll der Name deiner neuen Simulation sein?", maxLength);
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
			WhiteLine();
		}
		/****************************************************** TIME VARIABLE ********************************************************************/
		{
			std::cout << Crop("Welchen Namen hat deine Zeitvariable?", maxLength);
			std::cin >> time;
			WhiteLine();
		}
		/****************************************************** Y VARIABLES ********************************************************************/
		{
			int nIYVars = ReadNumberInt(Crop("Wie viele Variablen sollen auf der y-Achse dargestellt werden?", maxLength));
			for (int i = 0; i < nIYVars; )
			{
				std::stringstream tempSS("");
				tempSS << "Gib deine " << ++i << ". y Variable ein!";
				std::cout << Crop(tempSS.str(), maxLength);
				std::string temp;
				std::cin >> temp;
				yValues += temp + " ";
			}
			yValues.pop_back();
			WhiteLine();
		}
		/****************************************************** REPEATING VALUE ********************************************************************/
		{
			std::cout << "Die Engine berechnet deinen Code mehrmals pro Sekunde.\nDu kannst dies nachher noch beschleunigen oder verlangsamen.\nDies reicht von 5 bis 1200 Berechnungen pro Sekunde.\n";
			repeating = ReadNumberStrRestricted(Crop("Also, wie oft soll das Programm deinen Code zu Beginn berechnen?", maxLength), 5, 1200);
			WhiteLine();
		}
		/****************************************************** AXIS COLOR ********************************************************************/
		{
			bool tempB = false;
			do {
				std::cout << "Gib jetzt bitte die Farbe der Achsen ein.\n" << Crop("Willst du das RGB-codiert machen (mehr Auswahl)?", maxLength);
				std::string tempS;
				std::cin >> tempS;
				if (tempS == "Ja" || tempS == "ja")
				{
					tempB = false;
					axisColor += ReadNumberStrRestricted(Crop("Gib nun den roten Teil ein:", maxLength), 0, 255) + " ";
					axisColor += ReadNumberStrRestricted(Crop("Gib nun den gr\x81nen Teil ein:", maxLength), 0, 255) + " ";
					axisColor += ReadNumberStrRestricted(Crop("Gib nun den blauen Teil ein: ", maxLength), 0, 255);
				}
				else if (tempS == "Nein" || tempS == "nein" || tempS == "ne")
				{
					tempB = false;
					std::string tempS;
					tempS += "Diese Farben gibt es zur Auswahl:\n";
					tempS += "Weiss (1) - Grau (2) - Hellgrau (3) - Rot (4) - Gr\x81n (5)\nBlau (6) - Gelb (7) - Cyan (8) - Magenta (9) - Orange (10)\n";
					tempS += Crop("Such deine aus und gib die entsprechende Nummer ein!", maxLength);
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
					std::cout << "Das habe ich nicht verstanden. Sorry :(\nBitte gib 'ja' oder 'nein' ein.\n";
				}
			} while (tempB);
			WhiteLine();
		}
		/****************************************************** GRAPH COLOR ********************************************************************/
		
		{
			bool tempB = false;
			do {
				std::cout << "Letzter Schritt: Gib bitte die Farbe des Graphen ein.\n" << Crop("Willst du das RGB-codiert machen (mehr Auswahl)?", maxLength);
				std::string tempS;
				std::cin >> tempS;
				if (tempS == "Ja" || tempS == "ja")
				{
					tempB = false;
					graphColor += ReadNumberStrRestricted(Crop("Gib nun den roten Teil ein:", maxLength), 0, 255) + " ";
					graphColor += ReadNumberStrRestricted(Crop("Gib nun den gr\x81nen Teil ein: ", maxLength), 0, 255);
					graphColor += ReadNumberStrRestricted(Crop("Gib nun den blauen Teil ein:", maxLength), 0, 255) + " ";
				}
				else if (tempS == "Nein" || tempS == "nein" || tempS == "ne")
				{
					tempB = false;
					std::string tempS;
					tempS += "Diese Farben gibt es zur Auswahl:\n";
					tempS += "Weiss (1) - Grau (2) - Hellgrau (3) - Rot (4) - Gr\x81n (5)\nBlau (6) - Gelb (7) - Cyan (8) - Magenta (9) - Orange (10)\n";
					tempS += Crop("Such deine aus und gib die entsprechende Nummer ein!", maxLength);
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
					std::cout << "Das habe ich nicht verstanden. Sorry :(\nBitte gib 'ja' oder 'nein' ein.\n";
				}
			} while (tempB);
			WhiteLine();
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
				std::cout << "Diese Simulation wurde erfolgreich in dein 'files.txt' hinzugef\x81gt.\n";
			}
			else
			{
				bool tempB = false;
				do {
					std::cout << Crop("Ich kann keine 'files.txt' finden. Soll sie erstellt werden?", maxLength);
					std::string tempS;
					std::cin >> tempS;
					if (tempS == "Ja" || tempS == "ja")
					{
						std::ofstream newSettingsFile(settingsFileName);
						newSettingsFile << name;
						std::cout << "Ich habe 'files.txt' erfolgreich f\x81r dich bereitgestellt.\n";
					}
					else if (tempS == "Nein" || tempS == "nein" || tempS == "ne")
					{
						std::cout << "Dann musst du '" << name << "' selbst zu deiner 'files.txt' hinzuf\x81gen um die Engine korrekt arbeiten zu lassen.\n";
					}
					else
					{
						tempB = true;
						std::cout << "Das habe ich nicht verstanden. Sorry :(\nBitte gib 'ja' oder 'nein' ein.\n";
					}
				} while (tempB);
			}
			WhiteLine();
		}
		/****************************************************** SYNTAX INFORMATION ********************************************************************/
		{
			bool tempB = false;
			do {
				std::cout << "Du musst jetzt nur noch\n-die Startvariablen (zwischen '#Head' und '#Program') und\n-den Code selbst(nach '#Program')\nhinzuf\x81gen\n";
				std::cout << Crop("Soll ich dich ein bisschen \x81 \bber den Syntax informieren?", maxLength);
				std::string tempS;
				std::cin >> tempS;
				if (tempS == "Ja" || tempS == "ja")
				{
					tempB = false;
					std::cout << "\n1.) Kommentare sind eingebaut. Schreibe einfach '//' an den Zeilenanfang.\n";
					std::cout << "2.) Weiterhin sind Winkelfunktionen vorhanden: du musst nur  'sin', 'cos', 'tan' oder 'sqrt' (das ist die Quadratwurzel) vor eine Klammer schreiben.\n";
					std::cout << "3.) If-Pr\x81 \bfungen sind auch existent: du musst einfach nur 'if (-Bedingung-) -Term-' schreiben!\n\n";
					std::cout << "Sollte ein Fehler auftreten, gibt das Programm eine Meldung aus: Es wurden viele Sicherheitspr\x81 \bfungen eingebaut.\nLies sie dir genau durch, um alle Informationen zu gewinnen.\nWenn du den Fehler trotzdem nicht findest, erstelle einen Issue auf GitHub (@Fractum34254)\noder schreib mir und ich werde versuchen zu helfen.\n\n";
					std::cout << "Jetzt viel Freude mit deiner neuen Simulation!";
				}
				else if (tempS == "Nein" || tempS == "nein" || tempS == "ne")
				{
					tempB = false;
					std::cout << "Dann viel Freude mit deiner neuen Simulation!";
				}
				else
				{
					tempB = true;
					std::cout << "Das habe ich nicht verstanden. Sorry :(\nBitte gib 'ja' oder 'nein' ein.\n";
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
	file << time << " = 0\n";
	file << headEnd;

	/****************************************************** END ********************************************************************/
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
}
