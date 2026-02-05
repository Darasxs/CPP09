#ifndef PMERGEME_CPP
# define PMERGEME_CPP

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
        void vectorSort();
        void dequeSort();

    public:
        PmergeMe(void);
        PmergeMe(int argc, char **argv);
        PmergeMe(PmergeMe const &copy);
        PmergeMe &operator=(PmergeMe const &copy);
        ~PmergeMe(void);

        void sort(void);
};

#endif