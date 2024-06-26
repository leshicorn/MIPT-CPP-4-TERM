#include "test_runner.h"
#include <vector>
using namespace std;

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
    int64_t sum = 0;
    for (const auto& row : matrix) {
        for (int element : row) {
            sum += element;
        }
    }
    return sum;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
}
