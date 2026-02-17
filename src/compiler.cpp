#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>

constexpr int size = 10;
void clearbuffer(char buff[size+1]);

int main()
{
	std::ifstream input("input.txt");
	char ch;

	char buffer[size+1];
	
	clearbuffer(buffer);

	

	return 0;
}

void clearbuffer(char buff[size+1])
{
	for (int i = 0; i < size + 1; i++)
	{
		buff[i] = '\0';
	}
}
