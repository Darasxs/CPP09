#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <deque>
# include <sstream>
# include <ctime>
# include <algorithm>
# include <stdexcept>

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

# include "PmergeMe.tpp"

#endif