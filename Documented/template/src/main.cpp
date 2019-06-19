#include <iostream>

template<unsigned long long int n>
struct fibonacci {
  static constexpr unsigned long long int value = fibonacci<n-1>::value + fibonacci<n-2>::value;
};

template<>
struct fibonacci<0> {
  static constexpr unsigned long long int value = 0;
};

template<>
struct fibonacci<1> {
  static constexpr unsigned long long int value = 1;
};


int main(int argc, const char * argv[]) {
	std::cout << "f(50) is " << fibonacci<50>::value << std::endl;
	
	return 0;
}
