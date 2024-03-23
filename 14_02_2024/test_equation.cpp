#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
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

int GetDistinctRealRootCount(double a, double b, double c) {
  // Вы можете вставлять сюда различные реализации функции,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный
}
void TestNoRoots() {
  AssertEqual(GetDistinctRealRootCount(1, 0, 1), 0, "No real roots, discriminant < 0");
  AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0, "No real roots, a = b = 0");
}

void TestOneRoot() {
  AssertEqual(GetDistinctRealRootCount(1, -2, 1), 1, "One real root, discriminant = 0");
  AssertEqual(GetDistinctRealRootCount(1, 4, 4), 1, "One real root, a = 1, b = 4, c = 4");
}

void TestTwoRoots() {
  AssertEqual(GetDistinctRealRootCount(1, 0, -4), 2, "Two distinct real roots");
  AssertEqual(GetDistinctRealRootCount(1, -5, 6), 2, "Two distinct real roots, a = 1, b = -5, c = 6");
}

void TestAllCoefficientsZero() {
  AssertEqual(GetDistinctRealRootCount(0, 0, 0), 0, "All coefficients are zero");
}

void TestLinearEquation() {
  AssertEqual(GetDistinctRealRootCount(0, 2, 3), 1, "Linear equation, one real root");
  AssertEqual(GetDistinctRealRootCount(0, 0, 5), 0, "Linear equation, no real roots");
}

void TestQuadraticEquation() {
  AssertEqual(GetDistinctRealRootCount(2, 4, 2), 1, "Quadratic equation, one real root");
  AssertEqual(GetDistinctRealRootCount(3, -6, 3), 1, "Quadratic equation, one real root");
}

void TestComplexRoots() {
  AssertEqual(GetDistinctRealRootCount(1, 2, 2), 0, "Complex roots, discriminant < 0");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestNoRoots, "TestNoRoots");
  runner.RunTest(TestOneRoot, "TestOneRoot");
  runner.RunTest(TestTwoRoots, "TestTwoRoots");
  runner.RunTest(TestAllCoefficientsZero, "TestAllCoefficientsZero");
  runner.RunTest(TestLinearEquation, "TestLinearEquation");
  runner.RunTest(TestQuadraticEquation, "TestQuadraticEquation");
  runner.RunTest(TestComplexRoots, "TestComplexRoots");
  return 0;
}
