#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class SynonymDictionary {
private:
    unordered_map<string, vector<string>> synonyms;

public:
    void addSynonym(const string& word1, const string& word2) {
        synonyms[word1].push_back(word2);
        synonyms[word2].push_back(word1);
    }

    int countSynonyms(const string& word) {
        if (synonyms.count(word) == 0) {
            return 0;
        }
        return synonyms[word].size();
    }

    string checkSynonyms(const string& word1, const string& word2) {
        if (synonyms.count(word1) && 
            find(synonyms[word1].begin(), synonyms[word1].end(), word2) != synonyms[word1].end()) {
            return "YES";
        } else {
            return "NO";
        }
    }
};

int main() {
    int Q;
    cin >> Q;

    SynonymDictionary dictionary;

    for (int i = 0; i < Q; ++i) {
        string operation;
        cin >> operation;
        
        if (operation == "ADD") {
            string word1, word2;
            cin >> word1 >> word2;
            dictionary.addSynonym(word1, word2);
        } else if (operation == "COUNT") {
            string word;
            cin >> word;
            cout << dictionary.countSynonyms(word) << endl;
        } else if (operation == "CHECK") {
            string word1, word2;
            cin >> word1 >> word2;
            cout << dictionary.checkSynonyms(word1, word2) << endl;
        }
    }

    return 0;
}
