/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmerge.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:20:31 by dpaluszk          #+#    #+#             */
/*   Updated: 2026/01/25 17:55:03 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pmerge.hpp"

PmergeMe::PmergeMe(void) {}

PmergeMe::PmergeMe(int argc, char **argv)
{
    parseInput(argc, argv);
}

PmergeMe::PmergeMe(PmergeMe const &copy)
{
    *this = copy;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &copy)
{
    if (this != &copy)
    {
        this->vectorData = copy.vectorData;
        this->dequeData = copy.dequeData;
    }
    return *this;
}

PmergeMe::~PmergeMe(void) {}

void PmergeMe::parseInput(int argc, char **argv)
{
    if (argc < 2)
        throw std::invalid_argument("Error: No input provided");
    for (int i = 1; i < argc; i++)
    {
        // check each argument if it's integer and add them to the containers
    }
}

void PmergeMe::sort(void)
{
    // to be implemented
}