#pragma once
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "DataFrameExceptions.h"


class DataFrame
{
  public:
    DataFrame() = default;

    DataFrame(std::istream &input)
    {
        fill_df(input);
    }

    DataFrame(const std::string &file_name)
    {

        std::ifstream input(file_name);
        try
        {
            input.exceptions(input.failbit);
        }
        catch (std::ios_base::failure &)
        {
            throw;
        }
        fill_df(input);
    }

    std::vector<std::string> get_names() const
    {
        return _names;
    }

    double &operator()(size_t i, size_t j)
    {
        return _values[i][j];
    }
    const double &operator()(size_t i, size_t j) const
    {
        return _values[i][j];
    }

    std::vector<double> &operator[](size_t i)
    {
        return _values[i];
    }
    const std::vector<double> &operator[](size_t i) const
    {
        return _values[i];
    }

    void fill_df(std::istream &input)
    {
        if (!_names.empty())
        {
            _names.clear();
            _values.clear();
        }
        std::stringstream ss;
        std::string input_string;
        std::getline(input, input_string);

        _cols = 0;
        ss << input_string;
        if (!ss)
        {
            throw empty_data_frame();
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
        std::getline(input, input_string);
        if (!input || input_string.find_first_not_of(" \t\n") == std::string::npos)
            throw empty_data_frame("No numbers provided");
        while (input)
        {
            ss.ignore(std::numeric_limits<std::streamsize>::max());
            ss.clear();
            ss << input_string;
            _values.push_back(std::vector<double>(_cols));
            for (size_t i{}; i < _cols; ++i)
            {
                ss >> _values[rows][i];
                switch (ss.rdstate())
                {
                case std::ios_base::failbit:
                    throw invalid_data_frame("Encountered NaN in row " + std::to_string(rows + 1));
                case std::ios_base::eofbit:
                    if (i != _cols - 1)
                        throw invalid_data_frame("Too little elements in row " + std::to_string(rows + 1));
                    break;
                case std::ios_base::goodbit:
                default:
                    break;
                }
            }
            if (ss)
            {
                std::string tmp;
                ss >> tmp;
                if (!tmp.empty())
                {
                    throw invalid_data_frame("Too many elements in row " + std::to_string(rows + 1));
                }
            }

            ++rows;
            std::getline(input, input_string);
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const DataFrame &df)
    {
        const size_t MAX_LEN = std::max_element(df._names.begin(), df._names.end(), [](const auto &a, const auto &b) {
                                   return a.size() < b.size();
                               })->size();
        for (auto &s : df._names)
        {
            os << std::setw(MAX_LEN + 1) << s << ' ';
        }
        os << '\n';
        for (auto &vec : df._values)
        {
            for (auto x : vec)
            {
                os << std::setw(MAX_LEN + 1) << std::setprecision(MAX_LEN - 3) << x << ' ';
            }
            os << '\n';
        }
        return os;
    }

  protected:
    std::vector<std::string> _names;
    std::vector<std::vector<double>> _values;
    size_t _cols;
};
