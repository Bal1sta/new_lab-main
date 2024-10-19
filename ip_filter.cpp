#include <cassert> // Для использования assert
#include <cstdlib> // Для использования стандартных функций C
#include <iostream> // Для ввода-вывода
#include <fstream> // Для работы с файлами
#include <string> // Для работы со строками
#include <vector> // Для использования векторов
#include <algorithm> // Для std::sort
#include <tuple> // Для использования кортежей
#include "ip_filter.h" // Заголовочный файл для функций фильтрации IP

// Функция для разделения строки на части по указанному разделителю
std::vector<std::string> split(const std::string &str, char d) {
    std::vector<std::string> r; // Вектор для хранения частей строки

    // Проверка на пустую строку
    if (str.empty()) {
        return r; // Возвращаем пустой вектор, если строка пуста
    }

    std::string::size_type start = 0; // Начальная позиция для поиска
    std::string::size_type stop = str.find_first_of(d); // Находим первый разделитель

    while (stop != std::string::npos) { // Пока есть разделитель
        // Добавляем подстроку между разделителями в вектор
        r.push_back(str.substr(start, stop - start));
        start = stop + 1; // Переход к следующему символу после разделителя
        stop = str.find_first_of(d, start); // Находим следующий разделитель
    }
    
    // Добавляем последнюю часть строки после последнего разделителя
    r.push_back(str.substr(start));
    
    return r; // Возвращаем вектор с частями строки
}

// Функция для сравнения двух IP-адресов
bool compareIPs(const std::vector<std::string>& a, const std::vector<std::string>& b) {
    for (size_t i = 0; i < 4; ++i) { // Предполагаем, что IP-адрес состоит из 4 частей
        int partA = (i < a.size()) ? std::stoi(a[i]) : 0; // Преобразуем строку в целое число, если часть существует
        int partB = (i < b.size()) ? std::stoi(b[i]) : 0; // Если часть отсутствует, считаем ее равной 0

        if (partA != partB) {
            return partA < partB; // Сравниваем части и возвращаем результат сравнения
        }
    }
    return false; // Если все части равны, возвращаем false
}

// Функция для вывода всех IP-адресов из пула
void printIPAddresses(const std::vector<std::vector<std::string>>& ip_pool) {
    for (const auto& ip : ip_pool) { // Проходим по каждому IP-адресу в пуле
        for (size_t i = 0; i < ip.size(); ++i) { // Проходим по частям IP-адреса
            if (i != 0) {
                std::cout << "."; // Выводим точку перед каждой частью, кроме первой
            }
            std::cout << ip[i]; // Выводим текущую часть IP-адреса
        }
        std::cout << std::endl; // Переход на новую строку после каждого адреса
    }
}

// Функция для печати IP-адресов с первым байтом равным заданному значению
void printIPsWithFirstByte(const std::vector<std::vector<std::string>>& ip_pool, int first_byte) {
    for (const auto& ip : ip_pool) { // Проходим по каждому IP-адресу в пуле
        if (!ip.empty() && std::stoi(ip[0]) == first_byte) { // Проверяем первый байт IP-адреса
            for (size_t i = 0; i < ip.size(); ++i) { // Проходим по частям IP-адреса
                if (i != 0) {
                    std::cout << "."; // Выводим точку перед каждой частью, кроме первой
                }
                std::cout << ip[i]; // Выводим текущую часть IP-адреса
            }
            std::cout << std::endl; // Переход на новую строку после каждого адреса
        }
    }
}

// Функция для печати IP-адресов с первым байтом равным заданному значению и вторым байтом равным заданному значению
void printIPsWithFirstAndSecondByte(const std::vector<std::vector<std::string>>& ip_pool, int first_byte, int second_byte) {
    for (const auto& ip : ip_pool) { // Проходим по каждому IP-адресу в пуле
        if (ip.size() >= 2 && std::stoi(ip[0]) == first_byte && std::stoi(ip[1]) == second_byte) { 
            for (size_t i = 0; i < ip.size(); ++i) { // Проходим по частям IP-адреса
                if (i != 0) {
                    std::cout << "."; // Выводим точку перед каждой частью, кроме первой
                }
                std::cout << ip[i]; // Выводим текущую часть IP-адреса
            }
            std::cout << std::endl; // Переход на новую строку после каждого адреса
        }
    }
}

// Функция для печати IP-адресов, где любой байт равен заданному значению
void printIPsWithAnyByte(const std::vector<std::vector<std::string>>& ip_pool, int byte_value) {
    for (const auto& ip : ip_pool) { // Проходим по каждому IP-адресу в пуле
        for (const auto& part : ip) { // Проходим по частям текущего IP-адреса 
            if (std::stoi(part) == byte_value) { 
                for (size_t i = 0; i < ip.size(); ++i) { 
                    if (i != 0) {
                        std::cout << "."; // Выводим точку перед каждой частью, кроме первой 
                    }
                    std::cout << ip[i]; // Выводим текущую часть IP-адреса 
                }
                std::cout << std::endl; // Переход на новую строку после каждого адреса 
                break; // Выходим из внутреннего цикла, чтобы не дублировать вывод для одного IP 
            }
        }
    }
}

int main() {
    try {
        std::vector<std::vector<std::string>> ip_pool; // Вектор для хранения пула IP-адресов

        // Открываем файл для чтения 
        std::ifstream file("ip_filter.tsv");
        if (!file.is_open()) { 
            throw std::runtime_error("Не удалось открыть файл ip_filter.tsv"); 
        }

        // Чтение IP-адресов из файла 
        for (std::string line; std::getline(file, line);) { 
            std::vector<std::string> v = split(line, '\t'); 
            ip_pool.push_back(split(v.at(0), '.')); 
        }

        file.close(); // Закрываем файл после чтения 

        // Лексикографическая сортировка IP-адресов 
        std::sort(ip_pool.begin(), ip_pool.end(), compareIPs);

        // Выводим отсортированные IP-адреса 
        std::cout << "Полный список адресов после сортировки:\n"; 
        printIPAddresses(ip_pool);

        std::cout << "Вывод айпишек с первым байтом равным 1:\n"; 
        printIPsWithFirstByte(ip_pool, 1); 

        std::cout << "Вывод айпишек с первым байтом равным 46 и вторым - 70:\n"; 
        printIPsWithFirstAndSecondByte(ip_pool, 46, 70); 

        std::cout << "Вывод айпишек с любым байтом равным 46:\n";    
        printIPsWithAnyByte(ip_pool, 46); 

    } catch (const std::exception &e) { 
        std::cerr << e.what() << std::endl; 
    }

    return 0; 
}