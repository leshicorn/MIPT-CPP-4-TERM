#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

using std::endl;
using std::string;
using std::cerr;
using std::exception;
using std::ostringstream;
using std::runtime_error;
using std::vector;

#define RUN_TEST(tr, func) \
  tr.RunTest(func , #func)

#define ASSERT_EQUAL(x, y) { \
    ostringstream os; \
    os << __FILE__ << " : " << __LINE__ ; \
    AssertEqual(x, y, os.str()); \
}

#define ASSERT(x) ASSERT_EQUAL(x, true)

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

std::ostream& operator<<(std::ostream& os, const std::vector<int> vec) {
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i != vec.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<string> vec) {
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i != vec.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T, typename U>
void AssertEqual(const T& t, const U& u, const string& hint) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << "!=" << u << "Hint: " << hint;
        throw runtime_error(os.str());
    }
}