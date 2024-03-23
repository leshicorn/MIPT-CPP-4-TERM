#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Logger {
    public: explicit Logger(ostream & output_stream): os(output_stream) {}

    void SetLogLine(bool value) {
        log_line = value;
    }
    void SetLogFile(bool value) {
        log_file = value;
    }

    void Log(const string & message);

    private: ostream & os;
    bool log_line = false;
    bool log_file = false;
};

int main() {

    return 0;
}