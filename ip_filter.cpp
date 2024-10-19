#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream> // Для работы с файлами
#include <string>
#include <vector>
#include <algorithm> // Для std::sort
#include <tuple> // Для использования кортежей
#include "ip_filter.h"

// Функция для разделения строки на части
std::vector<std::string> split(const std::string &str, char d) {
    std::vector<std::string> r;

    // Проверка на пустую строку
    if (str.empty()) {
        return r; // Возвращаем пустой вектор
    }

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);

    while (stop != std::string::npos) {
        // Добавляем подстроку между разделителями
        r.push_back(str.substr(start, stop - start));
        start = stop + 1; // Переход к следующему символу после разделителя
        stop = str.find_first_of(d, start); // Находим следующий разделитель
    }
    
    // Добавляем последнюю часть строки после последнего разделителя
    r.push_back(str.substr(start));
    
    return r;
}

bool compareIPs(const std::vector<std::string>& a, const std::vector<std::string>& b) {
    for (size_t i = 0; i < 4; ++i) { // Предполагаем, что IP-адрес состоит из 4 частей
        int partA = (i < a.size()) ? std::stoi(a[i]) : 0; // Преобразуем строку в целое число
        int partB = (i < b.size()) ? std::stoi(b[i]) : 0; // Если часть отсутствует, считаем ее равной 0

        if (partA != partB) {
            return partA < partB; // Сравниваем части
        }
    }
    return false; // Если все части равны
}

void printIPAddresses(const std::vector<std::vector<std::string>>& ip_pool) {
    for (const auto& ip : ip_pool) {
        for (size_t i = 0; i < ip.size(); ++i) {
            if (i != 0) {
                std::cout << ".";
            }
            std::cout << ip[i];
        }
        std::cout << std::endl; // Переход на новую строку после каждого адреса
    }
}

// Функция для печати IP-адресов с первым байтом равным заданному значению
void printIPsWithFirstByte(const std::vector<std::vector<std::string>>& ip_pool, int first_byte) {
    for (const auto& ip : ip_pool) {
        if (!ip.empty() && std::stoi(ip[0]) == first_byte) {
            for (size_t i = 0; i < ip.size(); ++i) {
                if (i != 0) {
                    std::cout << ".";
                }
                std::cout << ip[i];
            }
            std::cout << std::endl; // Переход на новую строку после каждого адреса
        }
    }
}

// Функция для печати IP-адресов с первым байтом равным 46 и вторым - 70
void printIPsWithFirstAndSecondByte(const std::vector<std::vector<std::string>>& ip_pool, int first_byte, int second_byte) {
    for (const auto& ip : ip_pool) {
        if (ip.size() >= 2 && std::stoi(ip[0]) == first_byte && std::stoi(ip[1]) == second_byte) {
            for (size_t i = 0; i < ip.size(); ++i) {
                if (i != 0) {
                    std::cout << ".";
                }
                std::cout << ip[i];
            }
            std::cout << std::endl; // Переход на новую строку после каждого адреса
        }
    }
}
// Функция для печати IP-адресов, где любой байт равен заданному значению
void printIPsWithAnyByte(const std::vector<std::vector<std::string>>& ip_pool, int byte_value) {
    for (const auto& ip : ip_pool) {
        for (const auto& part : ip) {
            if (std::stoi(part) == byte_value) {
                for (size_t i = 0; i < ip.size(); ++i) {
                    if (i != 0) {
                        std::cout << ".";
                    }
                    std::cout << ip[i];
                }
                std::cout << std::endl; // Переход на новую строку после каждого адреса
                break; // Выходим из внутреннего цикла, чтобы не дублировать вывод для одного IP
            }
        }
    }
}


int main(){
    try {
        std::vector<std::vector<std::string>> ip_pool;

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

        std::cout << "Вывод айпишек с 1" << "\n";
        // Печать адресов с первым байтом равным 1
        printIPsWithFirstByte(ip_pool, 1);

        std::cout << "Вывод айпишек с 46 и 70 " << "\n";
        // Печать адресов с первым байтом равным 46 и вторым - 70
        printIPsWithFirstAndSecondByte(ip_pool, 46, 70);

        std::cout << "Вывод айпишек с 46 " << "\n";    
        // Печать адресов с любым байтом равным 46
        printIPsWithAnyByte(ip_pool, 46);

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}