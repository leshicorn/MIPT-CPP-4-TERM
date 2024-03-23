#include "sum_reverse_sort.h"
#include <algorithm>
#include <iostream>
#include <vector>

int Sum(int x, int y) {
    return x + y;
}

string Reverse(string s) {
    reverse(s.begin(), s.end());
    return s;
}

void Sort(vector<int>& nums) {
    sort(nums.begin(), nums.end());
}

int main() {
    // Тест функции Sum
    int result_sum = Sum(5, 3);
    std::cout << "Sum(5, 3) = " << result_sum << std::endl;

    // Тест функции Reverse
    std::string str = "hello";
    std::string reversed_str = Reverse(str);
    std::cout << "Reverse(\"hello\") = " << reversed_str << std::endl;

    // Тест функции Sort
    std::vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6};
    std::cout << "Before sorting: ";
    for (int num : nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    Sort(nums);

    std::cout << "After sorting: ";
    for (int num : nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}