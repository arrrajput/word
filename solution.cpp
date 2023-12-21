#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <chrono>
#include <algorithm>

using namespace std;

bool isCompoundWord(const string &word, const set<string> &wordSet, bool isOriginalWord = true) {
    if (!isOriginalWord && wordSet.find(word) != wordSet.end()) {
        return true;
    }
    for (int i = 1; i < word.length(); ++i) {
        string prefix = word.substr(0, i);
        string suffix = word.substr(i);
        if (wordSet.find(prefix) != wordSet.end() && isCompoundWord(suffix, wordSet, false)) {
            return true;
        }
    }
    return false;
}

int main() {
    set<string> wordSet;
    string longest, secondLongest, word;
    string filename;

    cout << "Enter the file name: ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    while (file >> word) {
        wordSet.insert(word);
    }

    auto startTime = chrono::high_resolution_clock::now();

    for (const auto &w : wordSet) {
        //cout<<w<<endl;
        if (isCompoundWord(w, wordSet)) {
            if (w.length() > longest.length()) {
                secondLongest = longest;
                longest = w;
            } else if (w.length() > secondLongest.length() && w != longest) {
                secondLongest = w;
            }
        }
    }

    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = endTime - startTime;

    cout << "Longest compound word: " << longest << endl;
    cout << "Second longest compound word: " << secondLongest << endl;
    cout << "Processing time: " << elapsed.count() << " seconds" << endl;

    return 0;
}