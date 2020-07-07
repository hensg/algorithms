//
//  grade_school.cpp
//  algorithms
//
//  Created by Henrique Goulart on 10/06/20.
//  Copyright © 2020 Henrique Goulart. All rights reserved.
//

#include "grade_school.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> partial_mult(const string a, const string b, const long n, long &partial_result_max_length) {
    vector<string> partial_results(n);
    string partial_result, partial_sum;
    int tmp = 0, carry = 0;
    
    for (long i = n - 1; i >= 0; i--) {
        for (long j = n - 1; j >= 0; j--) {
            tmp = (a[j]-48) * (b[i]-48);
            partial_sum = to_string(tmp + carry);
            
            if (partial_sum.length() == 2) {
                partial_result.insert(0, 1,partial_sum[1]);
                carry = (int)partial_sum[0] - 48;
            } else {
                partial_result.insert(0, partial_sum);
                carry = 0;
            }
        }
        partial_result.insert(0, to_string(carry));
        partial_results[i] = partial_result.append(n - i - 1, '0');
        if (partial_result_max_length < partial_result.length()){
            partial_result_max_length = partial_result.length();
        }
        partial_result = "";
        carry = 0;
    }
    return partial_results;
}

string final_sum(vector<string> &partial_results, const long partial_result_max_length) {
    string final_result, tmpstr;
    int tmp, carry = 0;

    for (auto &partial_result : partial_results) {
        partial_result.insert(0, partial_result_max_length - partial_result.length(), '0');
    }
    
    for (long i = partial_result_max_length - 1; i >= 0; i--) {
        tmp = 0;
        for (auto &partial_result : partial_results) {
            tmp += ((int)partial_result[i]-48);
        }
        tmp += carry;
        tmpstr = to_string(tmp);
        final_result.insert(0, 1, tmpstr[tmpstr.length() - 1]);
        const string remaining_sum = tmpstr.substr(0, tmpstr.length() - 1);
        carry = !remaining_sum.empty() ? stoi(remaining_sum) : 0;
    }
    return final_result;
}

string grade_school_int_mult(string first_input, string second_input) {
    long n;
    if (first_input.length() >= second_input.length())
        n = first_input.length();
    else
        n = second_input.length();
    
    const string a = first_input.insert(0, n - first_input.length(), '0');
    const string b = second_input.insert(0, n - second_input.length(), '0');
    
    long partial_result_max_length = 0;
    vector<string> partial_results = partial_mult(a, b, n, partial_result_max_length);
    return final_sum(partial_results, partial_result_max_length);
}
