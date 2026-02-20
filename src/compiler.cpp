#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <cctype>
#include <cassert>

int memory[26];
int data[26];
int reg{0};
char ch;
bool isLessEqual{false};
void firstparse(std::ifstream& file);
void validCheck(char c, int cLine);
void goToLine( std::ifstream& file , char c );

int main()
{
	std::ifstream input("input.txt");
	if ( !input.is_open() )
	{
		throw std::invalid_argument("File not found");
	}
	
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
	memory['J'-'A'] = -2;

	data['S'-'A'] = -2;
	data['G'-'A'] = -2;
	data['P'-'A'] = -2;
	data['N'-'A'] = -2;
	data['C'-'A'] = -2;
	data['A'-'A'] = -2;
	data['J'-'A'] = -2;
	
	firstparse(input);

	input >> ch;
	int currLine{0};

	while ( ch != 'S' )
	{
		int newValue{0};
		switch (ch)
		{
			case '@':
				std::cerr << "@ loop\n";
				input >> ch;
				input >> ch;
				while ( std::isdigit(ch) )
				{
					input >> ch;
				}
				currLine++;
				continue;
			case 'G':
				std::cerr << "G loop\n";
				input >> ch;
				validCheck(ch, currLine);
				reg = data[ch-'A'];
				break;
			case 'P':
				std::cerr << "P Loop";
				input >> ch;
				validCheck(ch, currLine);
				data[ch-'A'] = reg;
				break;
			case 'N':
				std::cerr << "N loop\n";
				char bits[9];
				bits[9] = '\0';

				for ( int i = 128, j = 0; i > 0; i /= 2 )
				{
					bits[j++] = ( data[ch-'A'] > i ) ? '0' : '1';
				}

				for ( int i = 128, j = 0; i > 0; i /= 2 )
				{
					if ( bits[j++] == '1' )
					{
						newValue += i;
					}
				}

				reg = newValue;
				break;
				
			case 'C':
				std::cerr << "C loop\n";
				input >> ch;
				validCheck(ch, currLine);
				isLessEqual = reg < data[ch-'A'];
				break;
			
			case 'A':
				std::cerr << "A loop\n";
				input >> ch;
				validCheck(ch, currLine);
				reg += data[ch-'A'];
				if ( reg > 256 )
				{
					reg -= 256;
				}
				break;
			case 'J':
				std::cerr << "J loop\n";
				input >> ch;
				assert( std::abs(ch-'A') < 25 && memory[ch-'A'] >= 0 );
				if ( isLessEqual )
					(input, ch);
				break;
			default:
				throw std::runtime_error("Invalid instruction");
		}
		isLessEqual = false;
		currLine++;
		input >> ch;
	}

	return 0;
}

void goToLine( std::ifstream& file , char c )
{
	file.clear();
	file.seekg( 0 , std::ios::beg );

	char temp;
	int cLine{0};

	file >> temp;

	while ( temp != 'S' )
	{
		if ( temp == ':' )
		{
			file >> temp;
			if ( temp == ch )
			{
				return;
			}
		}
		file >> ch;
	}
}

void validCheck(char c, int cLine)
{
	assert( std::abs(ch-'A') < 25 && memory[ch-'A'] >= 0 && data[ch-'A'] >= 0 && cLine > memory[ch-'A'] );
}

void firstparse(std::ifstream& file)
{
	std::cerr << "First parsing\n";
	int line{0};
	char c;

	file >> c;
	std::cerr << "Read char: " << c << "\n";
	
	while ( c != 'S' )
	{
		std::cerr << "Working with character: " << c << '\n';
		if ( c == '@' )
		{
			std::cerr << "Working with @ in first parse\n";
			file >> c;
			if ( std::abs(c-'A') > 25 )
			{
				throw std::out_of_range("Didn't use either an upper case letter or used some other character");
			}
			else if ( memory[c-'A'] != -1 )
			{
				throw std::runtime_error("Used invalid name for memory");
			}

			int value{0};
			char temp = c;
			file >> c;

			std::cerr << "Checking @ digit: " << c << "\n";

			if ( !std::isdigit(c) )
			{
				throw std::logic_error("No negative numbers or invalid number");
			}

			while ( std::isdigit(c) )
			{
				value += (c-'0');
				value *= 10;
				file >> c;
			}

			// std::cerr << "temp is: " << temp << "\n";
			// std::cerr << "memory[temp-'A']: " << memory[temp-'A'] << '\n';

			if ( memory[temp-'A'] != -1 )
			{
				std::cerr << "Syntax error on line: " << line << "\n";
				throw std::logic_error("Syntax Error");
			}
			
			if ( value > 255 ) 
			{
				throw std::logic_error("Value cannot be greater than 8 bits or 255 in decimal");
			}
			
			data[temp-'A'] = value;
			memory[temp-'A'] = line;
			line++;
			
			std::cerr << "Done with @\n";

			continue;
		}
		else if ( c == ':' )
		{
			std::cerr << "WOrking with :\n";
			file >> c;
			if ( std::abs(ch-'A') > 25 )
			{
				throw std::logic_error("Character is not valid");
			}
			else if ( memory[c] != -1 )
			{
				throw std::runtime_error("Invalid label name");
			}

			memory[c-'A'] = line;
			file >> c;
		}
		else if ( memory[c-'A'] == -2 )
		{
			file >> c;
			file >> c;
		}
		else
		{
			throw std::runtime_error("Unexpected first instruction");
		}
		line++;
	}
	
	file.clear();
	file.clear();
	file.seekg(0, std::ios::beg);

}