#include <iostream>
#include <string>
#include <type_traits>

/*
*   std::aligned_storage
*   template<std::size_t Len, std::size_t Align>
*   struct aligned_storage;
*/

template<typename T, size_t N>
class StaticVector {
public:
    StaticVector() { 
      std::cout << alignof(T) << "/" << sizeof(T)<< std::endl;
      for (int idx = 0; idx < N; ++idx) { 
        std::cout << &data[idx] << std::endl;
      }
    }

    ~StaticVector() {
      for(size_t pos = 0; pos < m_size; ++pos) {
        reinterpret_cast<T*>(data+pos)->~T();
      }
    }

    template<typename ...Args> 
    void emplace_back(Args&&... args) {
      if(m_size >= N) {
        throw std::bad_alloc{};
      }
      new(data+m_size) T(std::forward<Args>(args)...);
      ++m_size;
    }

    const T& operator[](size_t pos) const {
      return *reinterpret_cast<const T*>(data+pos);
    }

private:
  // std::aligned_storage<sizeof(T), alignof(T)>::type data[N]; // C++11
  std::aligned_storage_t<sizeof(T), alignof(T)> data[N];        // c++14
  size_t m_size = 0;
};

int main() {

    StaticVector<std::string, 2> v1;
    v1.emplace_back(5, '*');
    std::cout << v1[0] << '\n';
    
    return 0;
}