/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:17:41 by hladeiro          #+#    #+#             */
/*   Updated: 2026/04/28 18:14:50 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.h"

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter&) {}
ScalarConverter& ScalarConverter::operator=(const ScalarConverter&) { return *this; }
ScalarConverter::~ScalarConverter() {}

static bool isChar(const std::string& s)
{
    if (s.length() == 3 && s[0] == '\'' && s[2] == '\'')
        return true;
    if (s.length() == 1 && std::isprint(static_cast<unsigned char>(s[0])))
        return true;
    return false;
}

static bool isPseudoLiteral(const std::string& s)
{
    return (s == "-inff" || s == "+inff" || s == "nanf" ||
            s == "-inf"  || s == "+inf"  || s == "nan");
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
        std::cout << std::fixed << std::setprecision(1) << static_cast<float>(value) << "f";
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
        std::cout << std::fixed << std::setprecision(1) << value;
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
        value = static_cast<double>(literal.length() == 1 ? literal[0] : literal[1]);
    else if (isPseudoLiteral(literal))
    {
        if (literal == "nan" || literal == "nanf")
            value = NAN;
        else if (literal[0] == '-')
            value = -INFINITY;
        else
            value = INFINITY;
    }
    else
    {
        char* endptr = NULL;
        value = std::strtod(literal.c_str(), &endptr);

        std::string remaining(endptr);
        if (!remaining.empty() && !(remaining == "f" && literal[literal.size()-1] == 'f'))
        {
            std::cout << "Error: invalid literal" << std::endl;
            return;
        }
    }

    printChar(value);
    printInt(value);
    printFloat(value);
    printDouble(value);
}