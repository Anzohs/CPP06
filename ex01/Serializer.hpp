/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serialize.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:31:52 by hladeiro          #+#    #+#             */
/*   Updated: 2026/04/28 18:33:53 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "Data.h"
#include <stdint.h>

class Serializer
{
	private:
 	   Serializer();
 	   Serializer(const Serializer& other);
 	   Serializer& operator=(const Serializer& other);
 	   ~Serializer();
	public:
	    static uintptr_t serialize(Data* ptr);
	    static Data*     deserialize(uintptr_t raw);
};

#endif