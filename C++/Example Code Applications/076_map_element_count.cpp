#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int ArrayChallenge(int arr[], std::size_t arrLength)
{
    std::vector<int> ivec;
    for (size_t i = 0; i < arrLength; ++i)
        ivec.push_back(arr[i]);

    std::map<int, int> imap;

    for (const auto &val : ivec)
        ++imap[val];

    int ret_val;
    int ret_cnt{};

    for (size_t i = 0; i < arrLength; ++i)
    {
        int count = imap.at(arr[i]);

        if (count > ret_cnt)
        {
            ret_cnt = count;
            ret_val = arr[i];
        }
    }

    return ret_cnt > 1 ? ret_val : -1;
}

int main()
{
    int arr[] = {1, 2, 3, 3, 3, 2, 2, 2, 3, 4, 2, 5, 2};
    std::cout << ArrayChallenge(arr, sizeof arr / sizeof *arr);
}
