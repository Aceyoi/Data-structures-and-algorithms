//Сапожников Юрий ИВТ-22

#include "zipf_law.h"
#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    string filename = "books.txt"; // Имя файла с текстом
    string output_filename = "word_freq.txt"; // Имя файла для вывода данных

    // Чтение текста и подсчет частоты слов
    unordered_map<string, int> word_count = read_file_and_count_words(filename);

    // Сортировка слов по частоте
    vector<pair<string, int>> word_freq = sort_by_frequency(word_count);

    // Запись данных в файл для построения графика
    write_data_to_file(word_freq, output_filename);

    cout << "Файл с названием " << output_filename << " сохранен " << endl; // Выводим сообщение о завершении

    // python main_1.py

    return 0;
}
