/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:29:11 by hladeiro          #+#    #+#             */
/*   Updated: 2026/04/28 18:30:55 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_HPP
#define DATA_HPP

#include <string>

struct Data
{
    int         id;
    std::string name;
    double      value;

    Data() : id(0), name("Default"), value(0.0) {}
    Data(int i, const std::string& n, double v)
        : id(i), name(n), value(v) {}
};

#endif