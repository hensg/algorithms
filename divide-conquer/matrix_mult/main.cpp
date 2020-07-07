#include <iostream>
#include <vector>

std::vector<std::vector<int>> matrix_multi_loop(
        std::vector<std::vector<int>>& matrix_a,
        std::vector<std::vector<int>>& matrix_b) {

    int max_ia = matrix_a.size(), max_ja = matrix_a[0].size();
    int max_ib = matrix_b.size(), max_jb = matrix_b[0].size();

    std::vector<std::vector<int>> res;
    for (int i = 0; i < max_ia; i++) {
        std::vector<int> line(max_jb);
        res.push_back(line);
    }

    int sum = 0;
    for (int i = 0; i < max_ia; i++) {
        for (int jb = 0; jb < max_jb; jb++) {
            for (int ja = 0; ja < max_ja; ja++) {
                sum += matrix_a[i][ja] * matrix_b[ja][jb];
            }
            res[i][jb] = sum;
            sum = 0;
        }
    }
    return res;
}

std::vector<std::vector<int>> matrix_multi_divide_conquer(
        std::vector<std::vector<int>>& matrix_a,
        std::vector<std::vector<int>>& matrix_b) {

    throw std::runtime_error("Not implemented yet");
}


int main() {

    std::vector<std::vector<int>>
            matrix_a{
            {1, 2},
            {3, 4}
            //2x2
    },
            matrix_b{
            {7,  8},
            {9,  10}
            //2x2
    };

    std::vector<std::vector<int>> res = matrix_multi_loop(matrix_a, matrix_b);
    std::vector<std::vector<int>> res_recursive = matrix_multi_divide_conquer(matrix_a, matrix_b);

    std::cout << "Matrix result: " << std::endl;
    std::cout << res[0][0] << " " << res[0][1] << std::endl;
    std::cout << res[1][0] << " " << res[1][1] << std::endl;

    std::cout << "Matrix result (recursive): " << std::endl;
    std::cout << res_recursive[0][0] << " " << res_recursive[0][1] << std::endl;
    std::cout << res_recursive[1][0] << " " << res_recursive[1][1] << std::endl;

    return 0;
}