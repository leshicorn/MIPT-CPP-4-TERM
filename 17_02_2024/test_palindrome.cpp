#include <iostream>
#include <string>
#include <cassert>

using namespace std;

bool IsPalindrom(const string& str) {
    for (size_t i = 0; i < str.size() / 2; ++i) {
        if (str[i] != str[str.size() - i - 1]) {
            return false;
        }
    }
    return true;
}

void TestEmptyString() {
    const string str = "";
    assert(IsPalindrom(str));
}

void TestSingleCharacter() {
    const string str = "a";
    assert(IsPalindrom(str));
}

void TestPalindrome() {
    const string str = "level";
    assert(IsPalindrom(str));
}

void TestNonPalindrome() {
    const string str = "hello";
    assert(!IsPalindrom(str));
}

void TestPalindromeWithSpaces() {
    const string str = "was it a car or a cat i saw";
    assert(IsPalindrom(str));
}

void TestNonPalindromeWithSpaces() {
    const string str = "not a palindrome";
    assert(!IsPalindrom(str));
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

int main() {
    TestRunner runner;
    runner.RunTest(TestEmptyString, "TestEmptyString");
    runner.RunTest(TestSingleCharacter, "TestSingleCharacter");
    runner.RunTest(TestPalindrome, "TestPalindrome");
    runner.RunTest(TestNonPalindrome, "TestNonPalindrome");
    runner.RunTest(TestPalindromeWithSpaces, "TestPalindromeWithSpaces");
    runner.RunTest(TestNonPalindromeWithSpaces, "TestNonPalindromeWithSpaces");

    return 0;
}
