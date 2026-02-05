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
    [](const std::pair<value_type, value_type> &lhs,
       const std::pair<value_type, value_type> &rhs)
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
}
