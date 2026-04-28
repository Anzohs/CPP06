/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:35:32 by hladeiro          #+#    #+#             */
/*   Updated: 2026/04/28 18:43:49 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include <iostream>
#include <iomanip>

int main(void)
{
    Data* original = new Data(42, "Hello42", 3.14159265359);

    std::cout << "=== Original ===" << std::endl;
    std::cout << "Pointer : " << original << std::endl;
    std::cout << "Content : id=" << original->id
              << ", name=\"" << original->name
              << "\", value=" << original->value << std::endl << std::endl;

    uintptr_t serialized = Serializer::serialize(original);
    std::cout << "Serialized uintptr_t : 0x" << std::hex << serialized << std::dec << std::endl << std::endl;

    Data* deserialized = Serializer::deserialize(serialized);

    std::cout << "=== Deserialized ===" << std::endl;
    std::cout << "Pointer : " << deserialized << std::endl;
    std::cout << "Content : id=" << deserialized->id
              << ", name=\"" << deserialized->name
              << "\", value=" << deserialized->value << std::endl;

    if (deserialized == original)
        std::cout << "\nPointers match!" << std::endl;
    else
        std::cout << "\nPointers do not match!" << std::endl;

    delete original;
    return 0;
}