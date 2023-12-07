#include "DataFrame.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
    // Correct case with excess whitespace
    std::ifstream input1("input1.txt");

    // Incorrect case with NA
    std::ifstream input2("input2.txt");

    // Incorrect case with NaN
    std::ifstream input3("input3.txt");

    // Incorrect case with too many elements in a row
    std::ifstream input4("input4.txt");

    // Incorrect case with an empty data frame
    std::ifstream input5("input5.txt");

    DataFrame df;
    try
    {
        std::cout << "Input 1:\n";
        df.fill_df(input1);
        std::cout << df << std::endl;
    }
    catch (invalid_data_frame &e)
    {
        std::cerr << e.what() << std::endl;
    }

    try
    {
        std::cout << "Input 2:\n";
        df.fill_df(input2);
        std::cout << df << std::endl;
    }
    catch (invalid_data_frame &e)
    {
        std::cerr << e.what() << std::endl;
    }

    try
    {
        std::cout << "Input 3:\n";
        df.fill_df(input3);
        std::cout << df << std::endl;
    }
    catch (invalid_data_frame &e)
    {
        std::cerr << e.what() << std::endl;
    }

    try
    {
        std::cout << "Input 4:\n";
        df.fill_df(input4);
        std::cout << df << std::endl;
    }
    catch (empty_data_frame& e) 
    {
        std::cerr << e.what() << std::endl;
    }
    catch (invalid_data_frame &e)
    {
        std::cerr << e.what() << std::endl;
    }

    try
    {
        std::cout << "Input 5:\n";
        df.fill_df(input5);
        std::cout << df << std::endl;
    }
    catch (empty_data_frame& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (invalid_data_frame& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
