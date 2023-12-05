#pragma once
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class DataFrame
{
  public:
    DataFrame() = default;

    DataFrame(std::istream &input)
    {
        try
        {
            fill_df(input);
        }
        catch (const std::exception &e)
        {
            throw;
        }
    }

    DataFrame(const std::string &file_name)
    {

        try
        {
            std::ifstream input(file_name);
            fill_df(input);
        }
        catch (const std::exception &e)
        {
            throw;
        }
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
        std::getline(input, input_string);
        if (!input)
            throw std::exception("No numbers provided");
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
                    throw std::exception(("Encountered NaN in row " + std::to_string(rows + 1)).c_str());
                case std::ios_base::eofbit:
                    if (i != _cols - 1)
                        throw std::exception(("Too little elements in row " + std::to_string(rows + 1)).c_str());
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
                    throw std::exception(("Too many elements in row " + std::to_string(rows + 1)).c_str());
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
