#include <vector>
#include <utility>
#include "test_runner.h"

#define ASSERT_EQUAL(x, y) AssertEqual(x, y, __FILE__ ":" + std::to_string(__LINE__))


using namespace std;

template<typename T>
class Table {
public:
    Table(size_t rows, size_t cols) : data(rows, std::vector<T>(cols)) {}

    const std::vector<T>& operator[](size_t idx) const {
        return data[idx];
    }

    std::vector<T>& operator[](size_t idx) {
        return data[idx];
    }

    void Resize(size_t new_rows, size_t new_cols) {
        data.resize(new_rows);
        for (auto& row : data) {
            row.resize(new_cols);
        }
    }

    std::pair<size_t, size_t> Size() const {
        if (data.empty()) {
            return {0, 0};
        }
        return {data.size(), data[0].size()};
    }

private:
    std::vector<std::vector<T>> data;
};


void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
