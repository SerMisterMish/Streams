#pragma once
#include <string>
#include <iostream>

class invalid_data_frame : std::domain_error
{
public:
    explicit invalid_data_frame(const char* message = "Invalid data frame provided") noexcept
        : domain_error(message) {};
    explicit invalid_data_frame(std::string message) noexcept
        : domain_error(message) {};

    invalid_data_frame(const invalid_data_frame& other) noexcept : domain_error(other) {};
    invalid_data_frame& operator=(const invalid_data_frame& other) noexcept
    {
        *static_cast<domain_error*>(this) = other;
        return *this;
    }

    const char* what() const noexcept override
    {
        return domain_error::what();
    }
};

class empty_data_frame : public invalid_data_frame
{
public:
    explicit empty_data_frame(const char* message = "Empty data frame provided") noexcept
        : invalid_data_frame(message) {};
    explicit empty_data_frame(std::string message) noexcept
        : invalid_data_frame(message) {};

    empty_data_frame(const empty_data_frame& other) noexcept : invalid_data_frame(other) {};
    empty_data_frame& operator=(const empty_data_frame& other) noexcept
    {
        *static_cast<invalid_data_frame*>(this) = other;
        return *this;
    }
    
    const char* what() const noexcept override
    {
        return invalid_data_frame::what();
    }
};
