#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "DataFrame.h"

int main()
{
	std::ifstream input("input.txt");
	DataFrame df(input);
}