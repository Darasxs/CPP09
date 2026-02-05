/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:20:31 by dpaluszk          #+#    #+#             */
/*   Updated: 2026/02/05 21:21:26 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

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

bool PmergeMe::isValidNumber(const std::string &str)
{
    if (str.empty())
        return false;
    
    for (size_t i = 0; i< str.length(); i++)
    {
        if (!std::isdigit(str[i]))
            return false;
    }

    std::stringstream ss(str);
    long num;
    ss >> num;

    if (ss.fail() || num < 0 || num > 2147483647)
        return false;

    return true;
}

void PmergeMe::parseInput(int argc, char **argv)
{
    if (argc < 2)
        throw std::invalid_argument("Error: No input provided");
    for (int i = 1; i < argc; i++)
    {
        std::string arg(argv[i]);
        
        if (!isValidNumber(arg))
            throw std::invalid_argument("Error: Invalid input.");
        
        int num = std::atoi(arg.c_str());
        vectorData.push_back(num);
        dequeData.push_back(num);
    }
    
    std::vector<int> temp = vectorData;
    std::sort(temp.begin(), temp.end());
    for (size_t i = 1; i < temp.size(); i++)
    {
        if (temp[i] == temp[i - 1])
            throw std::invalid_argument("Error: Duplicate numbers.");
    }
}

void PmergeMe::sort(void)
{
    std::cout << "Before: ";
    for (size_t i = 0; i < vectorData.size(); i++)
        std::cout << vectorData[i] << " ";
    std::cout << std::endl;
    clock_t startVector = clock();
    vectorSort();
    clock_t endVector = clock();

    clock_t startDeque = clock();
    dequeSort();
    clock_t endDeque = clock();

    std::cout << "After: ";
    for (size_t i = 0; i < vectorData.size(); i++)
        std::cout << vectorData[i] << " ";
    std::cout << std::endl;

    double vectorTimeUs = static_cast<double>(endVector - startVector) * 1000000.0 / CLOCKS_PER_SEC;
    double dequeTimeUs = static_cast<double>(endDeque - startDeque) * 1000000.0 / CLOCKS_PER_SEC;

    std::cout << "Time to process a range of " << vectorData.size()
              << " elements with std::vector : " << vectorTimeUs << " us" << std::endl;
    std::cout << "Time to process a range of " << dequeData.size()
              << " elements with std::deque : " << dequeTimeUs << " us" << std::endl;
}
