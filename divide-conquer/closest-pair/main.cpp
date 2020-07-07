#include <iostream>
#include <cmath>
#include <vector>

//FIXME: THIS ALGO STILL PENDING

struct pair {
   int x, y;
};
struct closest_pair {
    pair a, b;
    double distance = MAXFLOAT;
};

double calc_distance(pair a, pair b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

/* C.n^2 */
closest_pair select_closest_pair(std::vector<pair> &pairs) {
    double distance;
    closest_pair closest_pair;

    for (int i = 0; i < pairs.size(); i++) {
        for (int j = i+1; j < pairs.size(); j++) {
             distance = calc_distance(pairs[i], pairs[j]);

             std::cout << "Distance of (" << pairs[i].x << ',' << pairs[i].y << ") to (";
             std::cout << pairs[j].x << ',' << pairs[j].y << ") is: " << distance << std::endl;

             if (distance < closest_pair.distance) {
                 closest_pair = { pairs[i], pairs[j], distance };
             }
        }
    }
    return closest_pair;
}

std::vector<pair> merge_sort(std::vector<pair> &pairs, int begin, int end, char by_axis = 'x') {
    if (end - begin == 1) {
        std::vector<pair> p(2);
        if (by_axis == 'x') {
            if (pairs[begin].x < pairs[end].x) {
                p[0] = { pairs[begin].x, pairs[begin].y },
                p[1] = { pairs[end].x, pairs[end].y };
            } else {
                p[0] = { pairs[end].x, pairs[end].y },
                p[1] = { pairs[begin].x, pairs[begin].y };
            }
        } else {
            if (pairs[begin].y < pairs[end].y) {
                p[0] = { pairs[begin].x, pairs[begin].y },
                p[1] = { pairs[end].x, pairs[end].y };
            } else {
                p[0] = { pairs[end].x, pairs[end].y },
                p[1] = { pairs[begin].x, pairs[begin].y };
            }
        }
        
        return p;
    }

    int mid = begin + ((end-begin)/2);
    std::vector<pair> left = merge_sort(pairs, begin, mid, by_axis);
    std::vector<pair> right = merge_sort(pairs, mid, end, by_axis);

    int n = end - begin;
    std::vector<pair> combined(n);

    int i = begin, j = mid, k = 0;
    while (i+j < n) {
        if (by_axis == 'x') {
            if ((i < mid && left[i].x < right[i].x) || j < end) {
                combined[k] = left[i];
                i++;
            } else {
                combined[k] = right[j];
                j++;
            }
        } else {
            if ((i < mid && left[i].y < right[i].y) || j < end) {
                combined[k] = left[i];
                i++;
            } else {
                combined[k] = right[j];
                j++;
            }
        }
        k++;
    }
    return combined;
}

closest_pair linear_closest_pair(std::vector<pair> &sorted_pairs) {
    closest_pair cp;
    double distance;
    for (int i = 0; i < sorted_pairs.size() - 1; i++) {
        distance = calc_distance(sorted_pairs[i], sorted_pairs[i+1]);
        if (distance < cp.distance) {
            cp = { sorted_pairs[i], sorted_pairs[i+1], distance };
        }
    }
    return cp;
}

// C.n.log(n)
closest_pair fast_select_closest_pair(std::vector<pair> &pairs_by_x, std::vector<pair> &pairs_by_y, int begin, int end) {
    if (end - begin <= 2) {
        double distance;
        distance = calc_distance(pairs_by_x[begin], pairs_by_x[end]);

    }
    int mid = begin + ((end - begin)/2) - 1;

    closest_pair left = fast_select_closest_pair(pairs_by_x, pairs_by_y, begin, mid);
    closest_pair right = fast_select_closest_pair(pairs_by_x, pairs_by_y, mid, end);

    //std::vector<pair> left_sorted_by_x = merge_sort(pairs_by_x, 0, mid_x, 'x');
    //std::vector<pair> left_sorted_by_y = merge_sort(pairs_by_y, 0, mid_y, 'y');
    //std::vector<pair> right_sorted_by_x = merge_sort(pairs_by_x, mid_x, pairs_by_x.size(), 'x');
    //std::vector<pair> right_sorted_by_y = merge_sort(pairs_by_y, mid+1, end, 'y');

    if (left.distance < right.distance)
        return left;
    return right;
}


/*
 *        |         e
 *        |              f
 *        |
 *        |
 *     c  |        d
 * _______|__b___________
 *        |
 *   a    |
 */
int main() {
    int n = 4;
    std::vector<pair> pairs(n);
    pairs[0] = {-2,-2};  //a
    pairs[1] = { 1, 0};  //b
    pairs[2] = {-1, 1};  //c
    pairs[3] = { 3, 1};  //d

    std::cout << "Printing pairs: " << std::endl;
    for (auto i = 0; i < n; i++) {
        std::cout << pairs[i].x  << ',' << pairs[i].y << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Selecting closest pair O(n^2): " << std::endl;
    const auto &closest = select_closest_pair(pairs);
    std::cout << std::endl << "Closest pair (" << closest.a.x << ',' << closest.a.y << ") ~ (";
    std::cout << closest.b.x << ',' << closest.b.y << ") with distance: " << closest.distance << std::endl;
    std::cout << std::endl;

    std::cout << "Fast closest pair O(n.logn): " << std::endl;
    auto px = merge_sort(pairs, 0, pairs.size(), 'x');
    auto py = merge_sort(pairs, 0, pairs.size(), 'y');
    const auto &fast_closest = fast_select_closest_pair(px, py, 0, pairs.size());
    std::cout << std::endl << "Closest pair (" << fast_closest.a.x << ',' << fast_closest.a.y << ") ~ (";
    std::cout << fast_closest.b.x << ',' << fast_closest.b.y << ") with distance: " << fast_closest.distance << std::endl;
    std::cout << std::endl;

    return 0;
}
