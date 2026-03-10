//Сапожников Юрий ИВТ-22
#pragma once

#include "SortAndSearch.Modul.Time.h"  
#include "SortAndSearch.Test.h"
#include <fstream>        
#include <iomanip>        
#include <numeric>        
#include <algorithm>     
#include <functional>  

using namespace std;

double measure_time(function<void(vector<int>&)> f, vector<int>& arr) {
    vector<int> copy = arr;
    auto start = chrono::high_resolution_clock::now();

    if (copy.empty()) return 0.0;

    f(copy);

    auto end = chrono::high_resolution_clock::now();
    return chrono::duration<double>(end - start).count();
}


void generate_sort_database(size_t MAX, size_t MIN) {
    cout << "Генерация базы данных...\n";

    vector<size_t> sizes = { 1000, 5000, 10000};
    const int NUM_TESTS = 20;

    ofstream csv("sort_database.csv");
    csv << "size,bubblesort,shellsort,quicksort,mergesort\n";

    for (size_t n : sizes) {
        double total_bubble = 0, total_shell = 0, total_quick = 0, total_merge = 0;

        cout << "n=" << n << "\r";

        for (int test = 0; test < NUM_TESTS; test++) {
            vector<int> arr(n);
            random_array(arr, MAX, MIN);

            // Bubble
            vector<int> copy = arr;
            auto start = chrono::high_resolution_clock::now();
            bubblesort(copy);
            total_bubble += chrono::duration<double>(chrono::high_resolution_clock::now() - start).count();

            // Shell  
            copy = arr;
            start = chrono::high_resolution_clock::now();
            shellsort(copy);
            total_shell += chrono::duration<double>(chrono::high_resolution_clock::now() - start).count();

            // Quick
            copy = arr;
            start = chrono::high_resolution_clock::now();
            quicksort(copy, 0, n - 1);  
            total_quick += chrono::duration<double>(chrono::high_resolution_clock::now() - start).count();

            // Merge
            copy = arr;
            start = chrono::high_resolution_clock::now();
            mergesort(copy, 0, n);  
            total_merge += chrono::duration<double>(chrono::high_resolution_clock::now() - start).count();
        }

        csv << n << ","
            << total_bubble / NUM_TESTS << ","
            << total_shell / NUM_TESTS << ","
            << total_quick / NUM_TESTS << ","
            << total_merge / NUM_TESTS << "\n";
    }
    csv.close();
}

void generate_search_database() {
    cout << "Генерация базы данных ПОИСКА...\n";

    vector<size_t> sizes = { 1000000, 5000000, 10000000, 25000000, 50000000 };
    const int NUM_TESTS = 50;  
    const int SEARCHES_PER_TEST = 100;  

    ofstream csv("search_database.csv");
    csv << "size,binsearch,interpolation\n";

    for (size_t n : sizes) {
        vector<int> sorted_arr(n);
        // Создаем отсортированный массив
        for (size_t i = 0; i < n; i++) sorted_arr[i] = i + 1;

        double total_bin = 0, total_interp = 0;

        cout << "n=" << n << "\r";

        for (int test = 0; test < NUM_TESTS; test++) {
            for (int k = 0; k < SEARCHES_PER_TEST; k++) {
                int target = rand() % n + 1;  // Случайный элемент из массива

                // Бинарный поиск
                vector<int> copy = sorted_arr;
                auto start = chrono::high_resolution_clock::now();
                binsearch(copy, 0, n, target);
                total_bin += chrono::duration<double>(chrono::high_resolution_clock::now() - start).count();

                // Интерполяционный поиск  
                copy = sorted_arr;
                start = chrono::high_resolution_clock::now();
                interpolationsearch(copy, 0, n, target);
                total_interp += chrono::duration<double>(chrono::high_resolution_clock::now() - start).count();
            }
        }

        csv << n << "," << total_bin / NUM_TESTS << "," << total_interp / NUM_TESTS << "\n";
    }
    csv.close();
    cout << "\n search_database.csv готов!\n";
}



