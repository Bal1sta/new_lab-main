#ifndef IP_FILTER_H
#define IP_FILTER_H

#include <string>
#include <vector>

// Функция для разделения строки на части
std::vector<std::string> split(const std::string &str, char d);

// Функция для сравнения двух IP-адресов
bool compareIPs(const std::vector<std::string>& a, const std::vector<std::string>& b);

// Функция для печати IP-адресов с первым байтом равным заданному значению
void printIPsWithFirstByte(const std::vector<std::vector<std::string>>& ip_pool, int first_byte);

// Функция для печати IP-адресов с первым байтом равным 46 и вторым - 70
void printIPsWithFirstAndSecondByte(const std::vector<std::vector<std::string>>& ip_pool, int first_byte, int second_byte);

// Функция для печати IP-адресов, где любой байт равен заданному значению
void printIPsWithAnyByte(const std::vector<std::vector<std::string>>& ip_pool, int byte_value);

#endif // IP_FILTER_H
