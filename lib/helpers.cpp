#include "helpers.hpp"

#include <algorithm>
#include <stdexcept>
#include <iostream>

bool check_equation(const std::string& equation) {
    // std::cout << "Checking " << equation << std::endl;

    const auto equals_index = equation.find('=');
    if (equals_index == std::string::npos) {
        return false;
    }
    const auto& left_term = equation.substr(0, equals_index);
    const auto& right_term = equation.substr(equals_index + 1, equation.size());
    if (left_term.empty() || right_term.empty()) {
        return false;
    } else {
        const auto left_result = evaluate_term(left_term);
        const auto right_result = evaluate_term(right_term);
        return left_result == right_result && left_result != -1;
    }
}

unsigned long evaluate_term(const std::string& term) {
    if (term.empty()) {
        return -1;
    }
    if (term[0] < '0' || term[0] > '9') {
        return -1;
    }
    size_t offset = -1;
    unsigned long accumulator = std::stoul(term, &offset);
    if (offset > 0 && term[0] == '0') {
        return -1;
    }
    unsigned long parser = 0;
    bool plus = false;
    for (; offset < term.length(); offset++) {
        const auto& c = term[offset];
        bool new_plus = false;
        switch (c) {
            case '+': new_plus = true;
            case '-':
            if (parser == (unsigned long) -1) {
                return -1;
            }
            accumulator += plus ? parser : -parser;
            parser = -1;
            plus = new_plus;
            break;
            default:
                if (c < '0' || c > '9') {
                    throw std::runtime_error("Invalid char " + c);
                }
                if (parser == (unsigned long) -1) {
                    parser = (unsigned long) (c - '0');
                    if (!parser) {
                        return -1;
                    }
                } else {
                    parser = parser * 10 + c - '0';
                }
        }
    }
    if (parser == (unsigned long) -1) {
        return -1;
    }
    accumulator += plus ? parser : -parser;
    return accumulator;
}