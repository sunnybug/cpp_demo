#include <iostream>
#include <vector>

// 二分查找算法
// 最坏时间为O(logn),即对数时间
// 返回所在位置
template<class ContainerType, class ItemType>
int binary_search(const ContainerType& rContainer, const ItemType& rItem)
{
    typename ContainerType::size_type low = 0;
    auto high = rContainer.size();

    while(low <= high)
    {
        auto mid = (low + high) / 2;
        auto guess = rContainer[mid];

        if (guess == rItem)
        {
            return mid;
        }

        if (guess > rItem)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return -1;
}

int main()
{
    std::vector<int> lst = {1, 2, 3, 4, 5};
    printf("%d", binary_search(lst, 3));
    return 0;
}