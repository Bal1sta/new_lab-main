cmake_minimum_required(VERSION 3.10)

project(IFilterProject VERSION 0.1.0)

# Найти Boost
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

# Создание библиотеки и исполняемого файла
add_library(ip_filter ip_filter.cpp)
add_executable(test_ip_filter test_ip_filter.cpp)

# Установка стандартов C++
set_target_properties(ip_filter test_ip_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# Установка директорий для заголовочных файлов
target_include_directories(ip_filter PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(test_ip_filter PRIVATE ${Boost_INCLUDE_DIRS})

# Связывание библиотек
target_link_libraries(test_ip_filter PRIVATE ${Boost_LIBRARIES} ip_filter)

# Включение тестирования
enable_testing()
add_test(NAME test_ip_filter COMMAND test_ip_filter)

# Копирование ресурсов (если необходимо)
set(RESOURCE_FILES 
    resources/ic.icns 
    ip_filter.tsv  # Добавляем файл ip_filter.tsv
)

foreach(RESOURCE ${RESOURCE_FILES})
    configure_file(${RESOURCE} ${CMAKE_BINARY_DIR}/${RESOURCE} COPYONLY)
endforeach()

# Включение CPack для создания пакетов
include(CPack)

# Настройки для CPack
set(CPACK_PACKAGE_NAME "ip_filter")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION "A description of your package.")
set(CPACK_PACKAGE_LICENSE "MIT")
set(CPACK_GENERATOR "DEB")

# Установка файлов в пакет (если необходимо)
install(TARGETS ip_filter DESTINATION bin)
install(TARGETS test_ip_filter DESTINATION bin)  

# Установка ресурсов в пакет (если необходимо)
install(FILES ${RESOURCE_FILES} DESTINATION resources)

message("Configured PROJECT_VERSION: ${PROJECT_VERSION}")
