#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include <sstream>
#include <stdexcept>
#include <iostream>
#include <string>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "{";
    bool first = true;
    for (const auto& elem : vec) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << elem;
    }
    return os << "}";
}

void Assert(bool b, const std::string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template<typename TestFunc>
    void RunTest(TestFunc func, const std::string& test_name) {
        try {
            func();
            std::cerr << test_name << " OK" << std::endl;
        } catch (const std::runtime_error& e) {
            ++fail_count;
            std::cerr << test_name << " fail: " << e.what() << std::endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            std::cerr << fail_count << " tests failed. Terminate" << std::endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

#define ASSERT_EQUAL(x, y) AssertEqual(x, y, __FILE__ + ":" + std::to_string(__LINE__))
#define ASSERT(x) Assert(x, "")
#define RUN_TEST(tr, func) tr.RunTest(func, #func)

#endif // TEST_RUNNER_H
