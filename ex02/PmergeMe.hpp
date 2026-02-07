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
        std::vector<size_t> order;
        if (limit >= 1)
            order.push_back(1);
        for (size_t k = 3; k < jacobsthal.size(); ++k)
        {
            size_t start = jacobsthal[k - 1] + 1;
            size_t end = std::min(jacobsthal[k], limit);
            if (start > end)
                continue;
            for (size_t i = end; ; --i)
            {
                order.push_back(i);
                if (i == start)
                    break;
            }
        }
        for (size_t idx = 0; idx < order.size(); ++idx)
        {
            size_t i = order[idx];
            typename Container::iterator maxPosIt = std::find(mainChain.begin(), mainChain.end(), pairs[i].first);
            size_t maxPos = static_cast<size_t>(maxPosIt - mainChain.begin());
            typename Container::iterator insertPos = std::lower_bound(mainChain.begin(), mainChain.begin() + maxPos, pend[i]);
            mainChain.insert(insertPos, pend[i]);
        }
    }

    if (hasOddNumber)
    {
        typename Container::iterator insertPos = std::lower_bound(mainChain.begin(), mainChain.end(), oddNumber);
        mainChain.insert(insertPos, oddNumber);
    }

    data = mainChain;
}

#endif