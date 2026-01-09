/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:42:32 by dpaluszk          #+#    #+#             */
/*   Updated: 2026/01/09 18:40:02 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
 
RPN::RPN(void)
{}

RPN::RPN(const std::string &input) : input(input)
{}

RPN::RPN(RPN const &copy)
{
    *this = copy;
}

RPN &RPN::operator=(RPN const &copy)
{
    if (this != &copy)
    {
        this->input = copy.input;
    }
    return *this;
}

RPN::~RPN(void)
{}

