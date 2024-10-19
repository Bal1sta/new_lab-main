#define BOOST_TEST_MODULE PrintIPTests
#include <boost/test/included/unit_test.hpp>
#include <sstream>
#include <vector>
#include <string>

// Функция для печати IP-адресов с первым и вторым байтами
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


// Тесты для функции printIPsWithFirstAndSecondByte
BOOST_AUTO_TEST_CASE(TestPrintIPsWithFirstAndSecondByte) {
    std::ostringstream output;
    auto cout_buf = std::cout.rdbuf(output.rdbuf()); // Сохраняем старый буфер

    // Подготовка данных для тестирования
    std::vector<std::vector<std::string>> ip_pool = {
        {"192", "168", "1", "1"},
        {"192", "168", "1", "2"},
        {"10", "0", "0", "1"},
        {"10", "0", "0", "2"},
        {"172", "16", "0", "1"}
    };

    // Вызов функции с параметрами 192 и 168
    printIPsWithFirstAndSecondByte(ip_pool, 192, 168);
    BOOST_CHECK_EQUAL(output.str(), "192.168.1.1\n192.168.1.2\n");

    output.str(""); // Сброс вывода для следующего теста
    output.clear();

    // Проверка с первым байтом 10 и вторым 0
    printIPsWithFirstAndSecondByte(ip_pool, 10, 0);
    BOOST_CHECK_EQUAL(output.str(), "10.0.0.1\n10.0.0.2\n");

    output.str(""); // Сброс вывода для следующего теста
    output.clear();

    // Проверка с первым байтом 172 и вторым 16
    printIPsWithFirstAndSecondByte(ip_pool, 172, 16);
    BOOST_CHECK_EQUAL(output.str(), "172.16.0.1\n");

    output.str(""); // Сброс вывода для следующего теста
    output.clear();

    // Проверка с параметрами, которые не совпадают ни с одним IP
    printIPsWithFirstAndSecondByte(ip_pool, 8, 8);
    BOOST_CHECK_EQUAL(output.str(), ""); // Ожидаем пустой вывод

    std::cout.rdbuf(cout_buf); // Восстанавливаем старый буфер
}

BOOST_AUTO_TEST_CASE(TestPrintIPsWithFirstAndSecondByte_AdditionalCases) {
    std::ostringstream output;
    auto cout_buf = std::cout.rdbuf(output.rdbuf()); // Сохраняем старый буфер

    // Подготовка данных для тестирования
    std::vector<std::vector<std::string>> ip_pool = {
        {"192", "168", "1", "1"},
        {"192", "168", "1", "2"},
        {"10", "0", "0", "1"},
        {"10", "0", "0", "2"},
        {"172", "16", "0", "1"}
    };

    // Вызов функции с первым байтом 192 и вторым 0 (ожидаем пустой вывод)
    printIPsWithFirstAndSecondByte(ip_pool, 192, 0);
    BOOST_CHECK_EQUAL(output.str(), ""); // Ожидаем пустой вывод

    output.str(""); // Сброс вывода для следующего теста
    output.clear();

    // Вызов функции с пустым пулом IP-адресов
    std::vector<std::vector<std::string>> empty_ip_pool;
    printIPsWithFirstAndSecondByte(empty_ip_pool, 192, 168);
    BOOST_CHECK_EQUAL(output.str(), ""); // Ожидаем пустой вывод

    std::cout.rdbuf(cout_buf); // Восстанавливаем старый буфер

}

BOOST_AUTO_TEST_CASE(TestPrintIPsWithFirstAndSecondByte_ExtraCases) {
    std::ostringstream output;
    auto cout_buf = std::cout.rdbuf(output.rdbuf()); // Сохраняем старый буфер

    // Подготовка данных для тестирования
    std::vector<std::vector<std::string>> ip_pool = {
        {"192", "168", "1", "1"},
        {"192", "168", "1", "2"},
        {"10", "0", "0", "1"},
        {"10", "0", "0"}, // IP с недостаточным количеством байтов
        {"172", "16", "0", "1"}
    };

    // Вызов функции с первым байтом 192 и вторым 168
    printIPsWithFirstAndSecondByte(ip_pool, 192, 168);
    BOOST_CHECK_EQUAL(output.str(), "192.168.1.1\n192.168.1.2\n"); // Ожидаем вывод

    output.str(""); // Сброс вывода для следующего теста
    output.clear();

    // Вызов функции с первым байтом 10 и вторым 1 (ожидаем пустой вывод)
    printIPsWithFirstAndSecondByte(ip_pool, 10, 1);
    BOOST_CHECK_EQUAL(output.str(), ""); // Ожидаем пустой вывод

    output.str(""); // Сброс вывода для следующего теста
    output.clear();

    // Вызов функции с первым байтом 172 и вторым 16
    printIPsWithFirstAndSecondByte(ip_pool, 172, 16);
    BOOST_CHECK_EQUAL(output.str(), "172.16.0.1\n"); // Ожидаем вывод

    std::cout.rdbuf(cout_buf); // Восстанавливаем старый буфер
}
