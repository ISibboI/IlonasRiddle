#include "helpers.hpp"

#include <vector>
#include <utility>
#include <iostream>
#include <string>

void evaluate_permutations(const size_t offset, std::vector<char>& characters) {
    if (characters.size() == offset + 1) {
        if (check_equation(std::string(characters.begin(), characters.end()))) {
            std::string p(characters.begin(), characters.end());
            p += "\n";
            std::cout << p;
        }
        return;
    }

    for (size_t i = offset; i < characters.size(); i++) {
        std::swap(characters[offset], characters[i]);
        evaluate_permutations(offset + 1, characters);
        std::swap(characters[offset], characters[i]);
    }
}

int main() {
    std::vector<char> characters{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '-', '='};
    // std::vector<char> characters{'1', '1', '+', '=', '2'};

    for (size_t i = 0; i < characters.size(); i++) {
        std::swap(characters[0], characters[i]);
#pragma omp parallel for firstprivate(characters)
        for (size_t j = 1; j < characters.size(); j++) {
            std::swap(characters[1], characters[j]);
            evaluate_permutations(2, characters);
            std::swap(characters[1], characters[j]);
        }
        std::swap(characters[0], characters[i]);
    }

    return 0;
}