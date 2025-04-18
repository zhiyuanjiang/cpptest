#include <iostream>
#include <string>
#include <cstring>
#include <list>
#include <vector>
#include <deque>
#include <type_traits>

/*
stl copy算法的简单实现
error 1
调用仿函数时出了个问题，直接像这般调用，my_copy_dispatch()，这里的问题在于my_copy_dispatch是结构体，
我缺少这样的一个对象，所以需要先创建一个临时对象，实际调用如下：my_copy_dispatch()()

error 2
函数中使用std::true_type形参，但我却妄图传入true参数，实际应该这样使用：std::bool_constant<true>
*/

template<class InputIterator, class OutputIterator, class Diff>
OutputIterator my_copy_d(InputIterator first, InputIterator last, OutputIterator result, Diff*) {
    for(Diff n = last-first; n > 0; --n, ++first, ++result) {
        *result = *first;
    }
    std::cout << "my_copy_d" << std::endl;
    return result;
}

template<class InputIterator, class OutputIterator>
OutputIterator _my_copy(InputIterator first, InputIterator last, OutputIterator result, std::random_access_iterator_tag) {
    std::cout << "_my_copy random_access_iterator_tag" << std::endl;
    return my_copy_d(first, last, result, (typename std::iterator_traits<InputIterator>::difference_type*)0);
}

template<class InputIterator, class OutputIterator>
OutputIterator _my_copy(InputIterator first, InputIterator last, OutputIterator result, std::input_iterator_tag) {
    for(; first != last; ++first, ++result) {
        *result = *first;
    }
    std::cout << "_my_copy input_iterator_tag" << std::endl;
    return result;
}

template<class T>
T* my_copy_t(const T* first, const T* last, T* result, std::true_type) {
    std::memmove(result, first, sizeof(T)*(last-first));
    std::cout << "my_copy_t T* true_type" << std::endl;
    return result+(last-first);
}

template<class T>
T* my_copy_t(const T* first, const T* last, T* result, std::false_type) {
    std::cout << "my_copy_t T* false_type" << std::endl;
    return my_copy_d(first, last, result, (std::ptrdiff_t*)0);
}

template<class InputIterator, class OutputIterator>
struct my_copy_dispatch {
    OutputIterator operator() (InputIterator first, InputIterator last, OutputIterator result) {
        std::cout << "my_copy_dispatch generalize" << std::endl;
        return _my_copy(first, last, result, typename std::iterator_traits<InputIterator>::iterator_category());
    }
};

template<class T>
struct my_copy_dispatch<T*, T*> {
    T* operator() (T* first, T* last, T* result) {
        std::cout << "my_copy_dispatch T*" << std::endl;
        return my_copy_t(first, last, result, std::bool_constant<std::is_trivially_copy_assignable_v<T>>());
    };
};

template<class T>
struct my_copy_dispatch<const T*, T*> {
    T* operator() (const T* first, const T* last, T* result) {
        std::cout << "my_copy_dispatch const T*" << std::endl;
        return my_copy_t(first, last, result, std::is_trivially_copyable_v<T>);
    }
};

char* my_copy(const char* first, const char* last, char* result) {
    std::memmove(result, first, last-first);
    std::cout << "my_copy char*" << std::endl;
    return result+(last-first);
}

wchar_t* my_copy(const wchar_t* first, const wchar_t* last, wchar_t* result) {
    std::memmove(result, first, sizeof(wchar_t)*(last-first));
    std::cout << "my_copy wchar_t*" << std::endl;
    return result+(last-first);
}

template<class InputIterator, class OutputIterator>
OutputIterator my_copy(InputIterator first, InputIterator last, OutputIterator result) {
    std::cout << "my_copy generalize" << std::endl;
    return my_copy_dispatch<InputIterator, OutputIterator>()(first, last, result);
}

class C {
public:
    C() : _data(3) {}
private:
    int _data;
};

int main() {
    // test 1
    std::cout << "test 1" << std::endl; 
    const char ccs[5] = {'a', 'b', 'c', 'd', 'e'};
    char ccd[5];
    my_copy(ccs, ccs+5, ccd);
    // test 2
    std::cout << "test 2" << std::endl;
    const wchar_t cwcs[5] = {'a', 'b', 'c', 'd', 'e'};
    wchar_t cwcd[5];
    my_copy(cwcs, cwcs+5, cwcd);
    // test 3
    std::cout << "test 3" << std::endl;
    int ia[5] = {0, 1, 2, 3, 4};
    my_copy(ia, ia+5, ia);
    // test 4
    std::cout << "test 4" << std::endl;
    std::list<int> ilists(ia, ia+5);
    std::list<int> ilistd(5);
    my_copy(ilists.begin(), ilists.end(), ilistd.begin());
    // test 5
    std::cout << "test 5" << std::endl;
    std::vector<int> ivecs(ia, ia+5);
    std::vector<int> ivecd(5);
    my_copy(ivecs.begin(), ivecs.end(), ivecd.begin());
    // test 6
    std::cout << "test 6" << std::endl;
    C cvs[5];
    C cvd[5];
    my_copy(cvs, cvs+5, cvd);
    // test 7
    std::cout << "test 7" << std::endl;
    std::deque<C> cds(cvs, cvs+5);
    std::deque<C> cdd(5);
    my_copy(cds.begin(), cds.end(), cdd.begin());
    // test 8
    std::cout << "test 8" << std::endl;
    std::string strvs[5];
    std::string strvd[5];
    strvs[0] = "a";
    strvs[1] = "b";
    strvs[2] = "c";
    strvs[3] = "d";
    strvs[4] = "e";
    my_copy(strvs, strvs+5, strvd);
    return 0;
}
