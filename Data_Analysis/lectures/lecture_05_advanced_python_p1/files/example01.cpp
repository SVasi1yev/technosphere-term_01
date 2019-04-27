#include <iostream>
#include <vector>

void vectorAppender1(std::vector<int> a, int b) {
    // passing argument by value
    a.push_back(b);
}

void vectorAppender2(std::vector<int>& a, int b) {
    // passing argument by reference
    a.push_back(b);
}

int main() {
    std::vector<int> v;

    vectorAppender1(v, 1);
    vectorAppender2(v, 2);

    for (const auto& e : v)
        std::cout << e << ' ';
    std::cout << std::endl;

    return 0;
}
