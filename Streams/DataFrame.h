#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class DataFrame
{
public:
	DataFrame() = default;

	DataFrame(std::istream& input) 
	{
		try
		{
			fill_df(input);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what();
		}
	}

	DataFrame(const std::string& file_name) 
	{
		
		try
		{
			std::ifstream input(file_name);
			fill_df(input);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what();
		}
	}
	
	std::vector<std::string> get_names() const { return _names; }

	double& operator()(size_t i, size_t j) { return _values[i][j]; }
	const double& operator()(size_t i, size_t j) const { return _values[i][j]; }

	std::vector<double>& operator[](size_t i) { return _values[i]; }
	const std::vector<double>& operator[](size_t i) const { return _values[i]; }

	void fill_df(std::istream& input)
	{
		std::stringstream ss;
		std::string input_string;
		std::getline(input, input_string);

		_cols = 0;
		ss << input_string;
		if (!ss) 
		{
			throw std::exception("Empty input");
		}
		while (ss) 
		{
			_names.push_back(std::string());
			ss >> _names[_cols++];
			if (_names.back().empty())
			{
				_names.pop_back();
				--_cols;
			}
		}
		size_t rows{};
		while (input) 
		{
			std::getline(input, input_string);
			ss.clear();
			ss << input_string;

			_values.push_back(std::vector<double>(_cols));
			for (size_t i{}; i < _cols; ++i)
			{
				ss >> _values[rows][i];
			}
			if (ss)
			{
				std::string tmp;
				ss >> tmp;
				if (!tmp.empty())
				{
					std::string err = "Too many elements in row " + std::to_string(rows);
					throw std::exception(err.c_str());
				}
			}

			++rows;
		}
	}

protected:
	std::vector<std::string> _names;
	std::vector<std::vector<double>> _values;
	size_t _cols;
};

