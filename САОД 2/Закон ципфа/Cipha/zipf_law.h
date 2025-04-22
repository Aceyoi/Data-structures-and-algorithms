//Сапожников Юрий ИВТ-22

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

// Функция для приведения строки к нижнему регистру
string to_lower(const string& str) {
    locale loc; // Используем локаль для корректного приведения к нижнему регистру
    string result;
    for (unsigned char c : str) {
        result += tolower(c, loc); // Приводим каждый символ к нижнему регистру
    }
    return result;
}

// Функция для удаления пунктуации из строки
string remove_punctuation(const string& str) {
    string result;
    for (char ch : str) {
        if (!ispunct(ch)) { // Проверяем, является ли символ пунктуацией
            result += ch; // Если нет, добавляем его в результат
        }
    }
    return result;
}

// Функция для чтения текста из файла и подсчета частоты слов
unordered_map<string, int> read_file_and_count_words(const string& filename) {
    ifstream file(filename); // Открываем файл для чтения
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl; // Выводим сообщение об ошибке, если файл не открыт
        return {};
    }

    unordered_map<string, int> word_count; // Создаем словарь для подсчета частоты слов
    string line, word;
    while (getline(file, line)) { // Читаем файл построчно
        istringstream iss(line); // Создаем потоковый объект для строки
        while (iss >> word) { // Читаем каждое слово в строке
            word = remove_punctuation(word); // Удаляем пунктуацию
            word = to_lower(word); // Приводим слово к нижнему регистру
            if (!word.empty()) { // Проверяем, что слово не пустое
                word_count[word]++; // Увеличиваем счетчик слова
            }
        }
    }
    file.close(); // Закрываем файл
    return word_count;
}

// Функция для сортировки слов по частоте
vector<pair<string, int>> sort_by_frequency(const unordered_map<string, int>& word_count) {
    vector<pair<string, int>> word_freq(word_count.begin(), word_count.end()); // Создаем вектор из словаря
    sort(word_freq.begin(), word_freq.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second; // Сортируем по убыванию частоты
        });
    return word_freq;
}

// Функция для записи данных в файл для построения графика
void write_data_to_file(const vector<pair<string, int>>& word_freq, const ::string& output_filename) {
    ofstream output_file(output_filename); // Открываем файл для записи
    if (!output_file.is_open()) {
        cerr << "Unable to open file: " << output_filename << endl; // Выводим сообщение об ошибке, если файл не открыт
        return;
    }

    for (size_t i = 0; i < word_freq.size(); ++i) { // Записываем данные в файл
        output_file << i + 1 << " " << word_freq[i].second << endl; // Ранг и частота слова
    }
    output_file.close(); // Закрываем файл
}
