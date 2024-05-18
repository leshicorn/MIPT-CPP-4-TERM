#include "profile.h"
#include "test_runner.h"

#include <map>
#include <set>
#include <string>
#include <sstream>
#include <future>
#include <functional>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

struct Stats {
  map<string, int> word_frequencies;

  void operator+=(const Stats& other) {
    for (const auto& [word, frequency] : other.word_frequencies) {
      word_frequencies[word] += frequency;
    }
  }
};

vector<string> SplitIntoWords(const string& line) {
  istringstream words_input(line);
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

Stats ExploreKeyWordsSingleThread(const set<string>& key_words, istream& input) {
  Stats result;
  for (string line; getline(input, line);) {
    vector<string> words = SplitIntoWords(line);
    for (const auto& word : words) {
      if (key_words.count(word)) {
        result.word_frequencies[word]++;
      }
    }
  }
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
  const size_t num_threads = thread::hardware_concurrency();
  vector<future<Stats>> futures;
  vector<Stats> stats_per_thread(num_threads);

  for (size_t i = 0; i < num_threads; ++i) {
    futures.push_back(async([&key_words, &input, i, num_threads]() {
      Stats result;
      for (string line; getline(input, line);) {
        if (hash<string>{}(line) % num_threads != i) {
          continue;
        }
        vector<string> words = SplitIntoWords(line);
        for (const auto& word : words) {
          if (key_words.count(word)) {
            result.word_frequencies[word]++;
          }
        }
      }
      return result;
    }));
  }

  Stats result;
  for (auto& future : futures) {
    result += future.get();
  }
  return result;
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequencies, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}
