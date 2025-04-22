//���������� ���� ���-22

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <locale>
#include <codecvt>
#include <string>

using namespace std;

// ������� ��� ���������� ������ � ������� ��������
string to_lower(const string& str) {
    locale loc; // ���������� ������ ��� ����������� ���������� � ������� ��������
    string result;
    for (unsigned char c : str) {
        result += tolower(c, loc); // �������� ������ ������ � ������� ��������
    }
    return result;
}

// ������� ��� �������� ���������� �� ������
string remove_punctuation(const string& str) {
    string result;
    for (char ch : str) {
        if (!ispunct(ch)) { // ���������, �������� �� ������ �����������
            result += ch; // ���� ���, ��������� ��� � ���������
        }
    }
    return result;
}

// ������� ��� ������ ������ �� ����� � �������� ������� ����
unordered_map<string, int> read_file_and_count_words(const string& filename) {
    ifstream file(filename); // ��������� ���� ��� ������
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl; // ������� ��������� �� ������, ���� ���� �� ������
        return {};
    }

    unordered_map<string, int> word_count; // ������� ������� ��� �������� ������� ����
    string line, word;
    while (getline(file, line)) { // ������ ���� ���������
        istringstream iss(line); // ������� ��������� ������ ��� ������
        while (iss >> word) { // ������ ������ ����� � ������
            word = remove_punctuation(word); // ������� ����������
            word = to_lower(word); // �������� ����� � ������� ��������
            if (!word.empty()) { // ���������, ��� ����� �� ������
                word_count[word]++; // ����������� ������� �����
            }
        }
    }
    file.close(); // ��������� ����
    return word_count;
}

// ������� ��� ���������� ���� �� �������
vector<pair<string, int>> sort_by_frequency(const unordered_map<string, int>& word_count) {
    vector<pair<string, int>> word_freq(word_count.begin(), word_count.end()); // ������� ������ �� �������
    sort(word_freq.begin(), word_freq.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second; // ��������� �� �������� �������
        });
    return word_freq;
}

// ������� ��� ������ ������ � ���� ��� ���������� �������
void write_data_to_file(const vector<pair<string, int>>& word_freq, const ::string& output_filename) {
    ofstream output_file(output_filename); // ��������� ���� ��� ������
    if (!output_file.is_open()) {
        cerr << "Unable to open file: " << output_filename << endl; // ������� ��������� �� ������, ���� ���� �� ������
        return;
    }

    for (size_t i = 0; i < word_freq.size(); ++i) { // ���������� ������ � ����
        output_file << i + 1 << " " << word_freq[i].second << endl; // ���� � ������� �����
    }
    output_file.close(); // ��������� ����
}
