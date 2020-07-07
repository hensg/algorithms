#include "recursive_mult.hpp"
#include <string>
#include <iostream>
#include <cmath>

unsigned long recursive_mult(std::string x, std::string y, unsigned long n) {
    if (n == 1)
        return ((int)x[0]-48) * ((int)y[0]-48);

    unsigned long half_n = n / 2;
    std::cout << "n: " << n << ", half_n: " << half_n << "\n";

    std::string a = x.substr(0, half_n);
    std::string b = x.substr(half_n, x.length());
    std::string c = y.substr(0, half_n);
    std::string d = y.substr(half_n, x.length());

    std::cout << "a: " << a << ", ";
    std::cout << "b: " << b << ", ";
    std::cout << "c: " << c << ", ";
    std::cout << "d: " << d << '\n';

    unsigned long ac = recursive_mult(a, c, half_n);
    unsigned long ad = recursive_mult(a, d, half_n);
    unsigned long bc = recursive_mult(b, c, half_n);
    unsigned long bd = recursive_mult(b, d, half_n);

    std::cout << "ac: " << ac << ", ";
    std::cout << "ad: " << ad << ", ";
    std::cout << "bc: " << bc << ", ";
    std::cout << "bd: " << bd << '\n';
    std::cout << "----------------\n";

    return pow(10, n) * ac + pow(10, half_n) * (ad + bc) + bd;
}
