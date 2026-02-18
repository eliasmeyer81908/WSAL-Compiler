#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <cctype>

int memory[26];
int data[26];
char ch;
void firstparse(std::ifstream file);

int main()
{
	std::ifstream input("input.txt");
	
	for ( int i = 0; i < 26; i++)
	{
		memory[i] = -1;
		data[i] = -1;
	}

	memory['S'-'A'] = -2;
	memory['G'-'A'] = -2;
	memory['P'-'A'] = -2;
	memory['N'-'A'] = -2;
	memory['C'-'A'] = -2;
	memory['A'-'A'] = -2;

	data['S'-'A'] = -2;
	data['G'-'A'] = -2;
	data['P'-'A'] = -2;
	data['N'-'A'] = -2;
	data['C'-'A'] = -2;
	data['A'-'A'] = -2;
	
	

	return 0;
}

void firstprase(std::ifstream file)
{
	int line{0};
	char ch;

	file >> ch;
	
	while ( ch != 'S' )
	{
		if ( ch == '@' )
		{
			file >> ch;
			if ( std::abs(ch-'A') > 25 )
			{
				throw std::out_of_range("Didn't use either an upper case letter or used some other character");
			}
			else if ( memory[ch-'A'] != -1 )
			{
				throw std::runtime_error("Used invalid name for memory");
			}

			int value{0};
			char temp = ch;
			file >> ch;

			while ( std::isdigit(ch) )
			{
				value += (ch-'0');
				value *= 10;
				file >> ch;
			}

			if ( memory[ch-'A'] != -2 )
			{
				throw std::logic_error("Syntax error on line: " + line);
			}

			data[temp-'A'] = value;
			memory[temp-'A'] = line;
		}
		else if ( ch == ':' )
		{
			file >> ch;
			if ( std::abs(ch-'A') > 25 )
			{
				throw std::logic_error("Character is not valid");
			}
			if ( memory[ch] != -1 )
			{
				throw std::runtime_error("Invalid label name");
			}

			memory[ch-'A'] = line;
			file >> ch;
		}
		else 
		{
			file >> ch;
			file >> ch;
		}
		line++;
	}

}