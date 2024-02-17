/**
    \file
    \brief 
        OTUS C++ Professional Домашнее задание №4
    \details
        Реализовать функцию печати условного IP-адреса.
        Условность его заключается в том, что количество элементов не обязательно должно быть равно 4-ём или 8-ми, а также каждый элемент не обязательно должен быть числом из диапазона 0..255. От идеи IP-адреса остаётся фактически только вывод элементов через `.` (символ точки).
        Функцию нужно реализовать для различных входных параметров путём использования механизма SFINAE. Всего нужно выполнить 3 обязательных и один опциональный вариант функции.
*/

#include <iostream>
#include <type_traits>
#include <vector>
#include <list>

/**
    \brief
        Задание №1
    \details
        Адрес может быть представлен в виде произвольного целочисленного типа. 
        Выводить побайтово в беззнаковом виде, начиная со старшего байта, 
        с символом `.` (символ точки) в качестве разделителя. 
        Выводятся все байты числа.
        \code
            // проверка, является ли тип интегральным = целочисленным
            std::enable_if_t<std::is_integral_v<T>, void>
        \endcode
    \param value целое число, которое должно быть представлено в виде IP-адреса     
*/
template <typename T>
std::enable_if_t<std::is_integral_v<T>, void>
print_ip(T value)
{
    size_t sz = sizeof(T);
    for (size_t i = 0; i < sz; ++i)
    {
        if (i) std::cout << ".";
        std::cout << (int)((value >> (8 * (sz - i - 1))) & 0xFF);
    }
    std::cout << std::endl;
}

/**
    \brief
        Задание №2
    \details
        Адрес может быть представлен в виде строки. 
        Выводится как есть, вне зависимости от содержимого.
        \code
            //  проверка, является ли тип строкой
            std::enable_if_t<std::is_same_v<T, std::string>, void>  
        \endcode
    \param value строка, которую нужно вывести
*/
template <typename T>
std::enable_if_t<std::is_same_v<T, std::string>, void>
print_ip(T value)
{
    std::cout << value << std::endl;
}

/**
    \brief
        Задание №3 
    \details
        Адрес может быть представлен в виде контейнеров `std::list`, `std::vector`. 
        Выводится полное содержимое контейнера поэлементно и разделяется `.` (символом точка). 
        Элементы выводятся как есть.
        \code
            //  проверка на соответствие типа - vector или list
            std::enable_if_t<std::is_same<T, std::vector<typename T::value_type, typename T::allocator_type>>::value ||
                             std::is_same<T, std::list<typename T::value_type, typename T::allocator_type>>::value, void>
        \endcode        
    \param container контейнер, содержимое которого нужно вывести    
*/
template <typename T>
std::enable_if_t<std::is_same<T, std::vector<typename T::value_type, typename T::allocator_type>>::value ||
                 std::is_same<T, std::list<typename T::value_type, typename T::allocator_type>>::value, void>
print_ip(T container)
{
    auto it = container.begin();
    while (it != container.end())
        std::cout << *it << ((++it != container.end()) ?  "." : "\n");
}            

/**
    \brief
        Главная функция
    \details
        Выполнение контрольных примеров.
*/
int main() 
{
    print_ip( int8_t{-1} ); // 255
    print_ip( int16_t{0} ); // 0.0
    print_ip( int32_t{2130706433} ); // 127.0.0.1
    print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
    //
    print_ip( std::string{"Hello, World!"} ); // Hello, World!
    //
    print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
    print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
}