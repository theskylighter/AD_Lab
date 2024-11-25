vector<int> arrOfMed;
        for (int i = low; i <= high; i += 5)
        {
            vector<int> group;
            for (int j = i; j < i + 5 && j <= high; ++j)
            {
            group.push_back(arr[j]);
            }
            arrOfMed.push_back(findMedian(group));
        }
        return selectMedianOfMedian(arrOfMed, 0, arrOfMed.size() - 1);