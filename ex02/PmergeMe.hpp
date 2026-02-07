#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <deque>
# include <sstream>
# include <ctime>
# include <algorithm>
# include <stdexcept>
# include <utility>

class PmergeMe
{
    private:
        std::vector<int> vectorData;
        std::deque<int> dequeData;

        bool isValidNumber(const std::string &str);
        void parseInput(int argc, char **argv);

        void vectorSort() { mergeInsertSort(vectorData); }
        void dequeSort() { mergeInsertSort(dequeData); }
        template <typename Container> void mergeInsertSort(Container &data);

    public:
        PmergeMe(void);
        PmergeMe(int argc, char **argv);
        PmergeMe(PmergeMe const &copy);
        PmergeMe &operator=(PmergeMe const &copy);
        ~PmergeMe(void);

        void sort(void);
};

template <typename Container> void PmergeMe::mergeInsertSort(Container &data)
{
    if (data.size() <= 1)
        return;

    bool hasOddNumber = (data.size() % 2 != 0);
    typename Container::value_type oddNumber = 0;

    if (hasOddNumber)
    {
        oddNumber = data.back();
        data.pop_back();
    }

    std::vector<std::pair<typename Container::value_type, typename Container::value_type>> pairs;

    for (size_t i = 0; i + 1 < data.size(); i+= 2)
    {
        typename Container::value_type a = data[i];
        typename Container::value_type b = data[i + 1];
        typename Container::value_type minVal;
        typename Container::value_type maxVal;
        if (a < b)
        {
            minVal = a;
            maxVal = b;
        }
        else
        {
            minVal = b;
            maxVal = a;            
        }
        pairs.push_back(std::make_pair(maxVal, minVal));
    }
    // std::cout << "PIERWSZY: ";
    // for (size_t i = 0; i < pairs.size(); i++)
    // {
    //     std::cout << "(" << pairs[i].first << ", " << pairs[i].second << ") ";
    // }    
    // std::cout << std::endl;
    std::sort(pairs.begin(), pairs.end(),
    [](const std::pair<typename Container::value_type, typename Container::value_type> &lhs,
       const std::pair<typename Container::value_type, typename Container::value_type> &rhs)
    {
        return lhs.first < rhs.first;
    });

    Container mainChain;
    Container pend;

    for (size_t i = 0; i < pairs.size(); i++)
    {
        mainChain.push_back(pairs[i].first);
        pend.push_back(pairs[i].second);
    }

    // std::cout << "main chain: " << std::endl;
    // for (size_t i = 0; i < mainChain.size(); i++)
    // {
    //     std::cout << mainChain[i] << " ";
    // }
    // std::cout << std::endl;
    // std::cout << "pend : " << std::endl;
    // for (size_t i = 0; i < pend.size(); i++)
    // {
    //     std::cout << pend[i] << " ";
    // }
    // std::cout << std::endl;

    if (!pend.empty())
    {
        mainChain.insert(mainChain.begin(), pend[0]);
    }

    if (pend.size() > 1)
    {
        std::vector<size_t> jacobsthal;
        jacobsthal.push_back(0);
        jacobsthal.push_back(1);
        size_t limit = pend.size() - 1;
        while(true)
        {
            size_t next = jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2];
            jacobsthal.push_back(next);
            if(next >= limit)
                break;
        }
    }
    

    // std::cout << "DRUGI: ";
    // for (size_t i = 0; i < pairs.size(); i++)
    // {
    //     std::cout << "(" << pairs[i].first << ", " << pairs[i].second << ") ";
    // }    
    // std::cout << std::endl;

}

#endif