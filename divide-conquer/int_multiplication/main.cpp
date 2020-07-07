#include <iostream>
#include <string>
#include "grade_school.hpp"
#include "recursive_mult.hpp"

int main(int argc, const char * argv[]) {
    std::string first_input = "3141592653589793238462643383279502884197169399375105820974944592";
    std::string second_input = "2718281828459045235360287471352662497757247093699959574966967627";

    std::cout << "Multiplication result:\n";
    //std::cout << grade_school_int_mult(first_input, second_input) << '\n';
    //std::cout << recursive_mult(first_input, second_input, first_input.length()) << '\n';
    std::cout << recursive_mult("5678", "1234", 4) << '\n';

    return 0;
}
