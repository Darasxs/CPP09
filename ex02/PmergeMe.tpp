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
}
