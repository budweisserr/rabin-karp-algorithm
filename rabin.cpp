#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <locale>
#include <math.h>
#include "windows.h"

const int letter = 94;
std::vector<int> g_position;

unsigned long int hashFunc(std::string data) {
    unsigned long int hashCode = 0;
    for (int i = 0; i != data.length(); i++) {
        hashCode += data[i] * pow(letter, i);
    }
    return hashCode;
}

int RabinKarp(std::string data, std::string inputData) {
    int counter = 0, space = 0, i = 0;
    bool equal = false;
    unsigned long int inputHash = hashFunc(inputData);
    std::vector<char> word;
    for (; data[i] != '\0';) {
        while (data[i] != ' ') {
            word.push_back(data[i]);
            if (data[i] == '.' || data[i] == '\n' || data[i] == ',' || data[i] == '!' || data[i] == '?' || data[i] == ';' || data[i] == ':') word.pop_back();
            i++;
            if (data[i] == '\0') {
                space++;
                break;
            }
        }
        if (data[i] == ' ') {
            space++;
            i++;
        }
        if (word.size() != inputData.length()) {
            word.clear();
            continue;
        }
        else {
            std::string strWord(word.begin(), word.end());
            unsigned long int wordHash = hashFunc(strWord);
            if (wordHash == inputHash) {
                for (int j = 0; j != inputData.length(); j++) {
                    if (inputData[j] == strWord[j]) {
                        equal = true;
                    }
                    else {
                        equal = false;
                    }
                }
                if (equal) {
                    counter++;
                    g_position.push_back(space);
                }
            }
            word.clear();
        }
    }
    return counter;
}

void find(std::vector<int> row, int element, int start) {
    if (row.size() == 0) return;
    int last = row.size() - 1;
    int old = row[last];
    row[last] = element;
    int i = start;
    while (row[i] != element) i++;
    row[last] = old;
    if (row[i] == element && i != row.size() - 1) {
        find(row, element, i + 1);
    }
    if (row[i] == element) {
        g_position.push_back(i);
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choise;
    std::cout << "Введіть номер завдання: ";
    std::cin >> choise;
    switch (choise) {
    case 1: {
        int size;
        std::cout << "Введіть розмір матриці: ";
        std::cin >> size;
        std::vector<std::vector<int>> arr;
        std::cout << "Матриця випадкових чисел: " << std::endl;
        for (int i = 0; i != size; i++) {
            std::vector<int> temp;
            for (int j = 0; j != size; j++) {
                temp.push_back((int)rand() % 201 - 100);
                std::cout << temp[j] << '\t';
            }
            arr.push_back(temp);
            std::cout << std::endl;
        }
        int element;
        unsigned long time = 0;
        std::cout << "Введіть шуканий елемент: ";
        std::cin >> element;
        for (int i = 0; i != size; i++) {
            std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
            find(arr[i], element, 0);
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            if (g_position.size() == 0) {
                continue;
            }
            else {
                for (int j = g_position.size() - 1; j >= 0; j--) {
                    std::cout << "Число " << element << " знаходиться у " << i+1 << " рядку та " << g_position[j]+1 << " стовбці." << std::endl;
                }
                g_position.clear();
            }
        }
        std::cout << "Час роботи алгоритму: " << time << " наносекунд" << std::endl;
        break;
    }
    case 2: {
        std::string str("Our online self-study, live classes and one-to-one courses with personal. Our online self-study, live classes and one-to-one courses with personal.");
        std::cout << "Текст:" << std::endl << str;
        std::string input;
        std::cout << std::endl << "Введіть шукане слово: ";
        std::cin >> input;
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        int result = RabinKarp(str, input);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Кількість слова " << input << " - " << result << std::endl;
        std::cout << "Номер слова у тексті: ";
        for (int i = 0; i != g_position.size(); i++) {
            std::cout << g_position[i] << ' ';
        }
        std::cout << std::endl;
        std::cout << "Час роботи алгоритму: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " наносекунд" << std::endl;
        g_position.clear();
        break;
    }
    }
    
}


