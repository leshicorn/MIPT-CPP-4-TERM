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

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        first_names[year] = first_name;
    }

    void ChangeLastName(int year, const string& last_name) {
        last_names[year] = last_name;
    }

    string GetFullName(int year) const {
        string first_name = GetName(year, first_names);
        string last_name = GetName(year, last_names);

        if (first_name.empty() && last_name.empty()) {
            return "Incognito";
        } else if (first_name.empty()) {
            return last_name + " with unknown first name";
        } else if (last_name.empty()) {
            return first_name + " with unknown last name";
        } else {
            return first_name + " " + last_name;
        }
    }

private:
    map<int, string> first_names;
    map<int, string> last_names;

    string GetName(int year, const map<int, string>& names) const {
        string name;
        for (const auto& item : names) {
            if (item.first <= year) {
                name = item.second;
            } else {
                break;
            }
        }
        return name;
    }
};

void TestIncognito() {
    Person person;
    AssertEqual(person.GetFullName(1900), "Incognito", "No name changes, expected 'Incognito'");
    AssertEqual(person.GetFullName(2000), "Incognito", "No name changes, expected 'Incognito'");
}

void TestFirstNameOnly() {
    Person person;
    person.ChangeFirstName(1980, "John");
    AssertEqual(person.GetFullName(1970), "Incognito", "No name changes before John");
    AssertEqual(person.GetFullName(1990), "John with unknown last name", "First name changed to John");
    AssertEqual(person.GetFullName(2000), "John with unknown last name", "First name still John");
}

void TestLastNameOnly() {
    Person person;
    person.ChangeLastName(1970, "Doe");
    AssertEqual(person.GetFullName(1960), "Incognito", "No name changes before Doe");
    AssertEqual(person.GetFullName(1980), "Doe with unknown first name", "Last name changed to Doe");
    AssertEqual(person.GetFullName(1990), "Doe with unknown first name", "Last name still Doe");
}

void TestFullName() {
    Person person;
    person.ChangeFirstName(1980, "John");
    person.ChangeLastName(1985, "Doe");
    AssertEqual(person.GetFullName(1970), "Incognito", "No name changes before John Doe");
    AssertEqual(person.GetFullName(1980), "John with unknown last name", "First name changed to John");
    AssertEqual(person.GetFullName(1985), "John Doe", "Last name changed to Doe");
    AssertEqual(person.GetFullName(1990), "John Doe", "Both first and last names exist");
}

int main() {
    TestRunner runner;
    runner.RunTest(TestIncognito, "TestIncognito");
    runner.RunTest(TestFirstNameOnly, "TestFirstNameOnly");
    runner.RunTest(TestLastNameOnly, "TestLastNameOnly");
    runner.RunTest(TestFullName, "TestFullName");
    return 0;
}
