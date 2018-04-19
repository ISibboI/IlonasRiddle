#include "helpers.hpp"

#include <stdexcept>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3) {
        throw std::runtime_error("Usage: " + std::string(argv[0]) + " <term> <expected_result>");
    }
    const std::string term(argv[1]);
    const unsigned long expected = std::stoul(std::string(argv[2]));
    const unsigned long actual = evaluate_term(term);
    std::cout << "Term: " << term << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    std::cout << "Actual: " << actual << std::endl;

    return expected != actual;
}