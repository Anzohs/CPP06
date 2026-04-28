/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:17:41 by hladeiro          #+#    #+#             */
/*   Updated: 2026/04/28 17:39:17 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.h"

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter&) {}
ScalarConverter& ScalarConverter::operator=(const ScalarConverter&) { return *this; }
ScalarConverter::~ScalarConverter() {}

static bool isChar(const std::string& s)
{
    return (s.length() == 3 && s[0] == '\'' && s[2] == '\'');
}

static bool isInt(const std::string& s)
{
    if (s.empty()) return false;
    size_t i = 0;
    if (s[0] == '-' || s[0] == '+') i++;
    for (; i < s.length(); ++i)
        if (!std::isdigit(static_cast<unsigned char>(s[i]))) return false;
    return true;
}

static bool isFloat(const std::string& s)
{
    if (s == "-inff" || s == "+inff" || s == "nanf")
        return true;
    if (s.empty() || s[s.length()-1] != 'f') return false;
    std::string tmp = s.substr(0, s.length()-1);
    if (tmp.empty()) return false;
    // Allow one dot and digits
    bool hasDot = false;
    size_t i = 0;
    if (tmp[0] == '-' || tmp[0] == '+') i++;
    for (; i < tmp.length(); ++i)
    {
        if (tmp[i] == '.')
        {
            if (hasDot) return false;
            hasDot = true;
        }
        else if (!std::isdigit(static_cast<unsigned char>(tmp[i]))) return false;
    }
    return true;
}

static bool isDouble(const std::string& s)
{
    if (s == "-inf" || s == "+inf" || s == "nan")
        return true;
    if (s.empty()) return false;
    bool hasDot = false;
    size_t i = 0;
    if (s[0] == '-' || s[0] == '+') i++;
    for (; i < s.length(); ++i)
    {
        if (s[i] == '.')
        {
            if (hasDot) return false;
            hasDot = true;
        }
        else if (!std::isdigit(static_cast<unsigned char>(s[i]))) return false;
    }
    return true;
}

static void printChar(double value)
{
    std::cout << "char: ";
    if (std::isnan(value) || std::isinf(value) || value < 0 || value > 127)
        std::cout << "impossible";
    else if (value < 32 || value > 126)
        std::cout << "Non displayable";
    else
        std::cout << "'" << static_cast<char>(value) << "'";
    std::cout << std::endl;
}

static void printInt(double value)
{
    std::cout << "int: ";
    if (std::isnan(value) || std::isinf(value) || value < INT_MIN || value > INT_MAX)
        std::cout << "impossible";
    else
        std::cout << static_cast<int>(value);
    std::cout << std::endl;
}

static void printFloat(double value)
{
    std::cout << "float: ";
    if (std::isnan(value))
        std::cout << "nanf";
    else if (std::isinf(value))
        std::cout << (value < 0 ? "-inff" : "+inff");
    else
    {
        std::cout << std::fixed << std::setprecision(1)
                  << static_cast<float>(value) << "f";
    }
    std::cout << std::endl;
}

static void printDouble(double value)
{
    std::cout << "double: ";
    if (std::isnan(value))
        std::cout << "nan";
    else if (std::isinf(value))
        std::cout << (value < 0 ? "-inf" : "+inf");
    else
    {
        std::cout << std::fixed << std::setprecision(1) << value;
    }
    std::cout << std::endl;
}

void ScalarConverter::convert(const std::string& literal)
{
    if (literal.empty())
    {
        std::cout << "Error: empty literal" << std::endl;
        return;
    }

    double value = 0.0;

    if (isChar(literal))
    {
        value = static_cast<double>(literal[1]);
    }
    else if (isInt(literal) || isFloat(literal) || isDouble(literal) ||
             literal == "-inff" || literal == "+inff" || literal == "nanf" ||
             literal == "-inf" || literal == "+inf" || literal == "nan")
    {
        char* endptr = NULL;
        value = std::strtod(literal.c_str(), &endptr);

        if (endptr == literal.c_str() || *endptr != '\0')
        {
            std::cout << "Error: invalid literal" << std::endl;
            return;
        }
    }
    else
    {
        std::cout << "Error: invalid literal" << std::endl;
        return;
    }

    printChar(value);
    printInt(value);
    printFloat(value);
    printDouble(value);
}