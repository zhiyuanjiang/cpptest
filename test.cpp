#include <iostream>
#include <tuple>
#include <type_traits>

namespace detail
{
    template<int I, typename T, typename... Args>
    struct find_index
    {
        static int call(std::tuple<Args...> const& t, T&& val)
        {
            return (std::get<I - 1>(t) == val) ? I - 1 :
                find_index<I - 1, T, Args...>::call(t, std::forward<T>(val));
        }
    };

    template<typename T, typename... Args>
    struct find_index<0, T, Args...>
    {
        static int call(std::tuple<Args...> const& t, T&& val)
        {
            return (std::get<0>(t) == val) ? 0 : -1;
        }
    };
}

template<typename T, typename... Args>
int find_index(std::tuple<Args...> const& t, T&& val)
{
    return detail::find_index<sizeof...(Args) - 1, T, Args...>::
           call(t, std::forward<T>(val));
}

int main()
{
    std::tuple<int, int, int, int> a(2, 3, 1, 4);
    std::cout << find_index(a, 1) << std::endl; // Prints 2
    std::cout << find_index(a, 2) << std::endl; // Prints 0
    std::cout << find_index(a, 5) << std::endl; // Prints -1 (not found)

    return 0;
}