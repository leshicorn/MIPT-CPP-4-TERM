#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

void Assert(bool b, const string& hint) {
    if (!b) {
        throw runtime_error(hint);
    }
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

class Rational {
public:
    Rational() : numerator_(0), denominator_(1) {}

    Rational(int numerator, int denominator) {
        if (denominator == 0) {
            throw invalid_argument("Denominator cannot be zero");
        }

        int gcd_val = gcd(numerator, denominator);
        numerator_ = numerator / gcd_val;
        denominator_ = denominator / gcd_val;

        if (denominator_ < 0) {
            numerator_ *= -1;
            denominator_ *= -1;
        }
    }

    int Numerator() const {
        return numerator_;
    }

    int Denominator() const {
        return denominator_;
    }

private:
    int numerator_;
    int denominator_;

    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
};

void TestDefaultConstructor() {
    Rational r;
    Assert(r.Numerator() == 0 && r.Denominator() == 1, "Default constructor test");
}

void TestReduceFraction() {
    Rational r(2, 4);
    Assert(r.Numerator() == 1 && r.Denominator() == 2, "Reduce fraction test");
}

void TestNegativeFraction() {
    Rational r(-2, 4);
    Assert(r.Numerator() == -1 && r.Denominator() == 2, "Negative fraction test");
}

void TestBothNegativeFraction() {
    Rational r(-2, -4);
    Assert(r.Numerator() == 1 && r.Denominator() == 2, "Both negative fraction test");
}

void TestZeroNumerator() {
    Rational r(0, 5);
    Assert(r.Numerator() == 0 && r.Denominator() == 1, "Zero numerator test");
}

int main() {
    TestRunner runner;
    runner.RunTest(TestDefaultConstructor, "TestDefaultConstructor");
    runner.RunTest(TestReduceFraction, "TestReduceFraction");
    runner.RunTest(TestNegativeFraction, "TestNegativeFraction");
    runner.RunTest(TestBothNegativeFraction, "TestBothNegativeFraction");
    runner.RunTest(TestZeroNumerator, "TestZeroNumerator");

    // Add more tests as needed...

    return 0;
}
