#include "helpers.hpp"

#include <algorithm>
#include <stdexcept>

bool check_equation(const std::string& equation) {
    const auto equals_index = equation.find('=');
    if (equals_index == std::string::npos) {
        return false;
    }
    const auto& left_term = equation.substr(0, equals_index);
    const auto& right_term = equation.substr(equals_index + 1, equation.size());
    if (left_term.empty() || right_term.empty()) {
        return false;
    } else {
        return evaluate_term(left_term) == evaluate_term(right_term);
    }
}

unsigned long evaluate_term(const std::string& term) {
    size_t offset = -1;
    unsigned long accumulator = std::stoul(term, &offset);
    unsigned long parser = -1;
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
            plus = new_plus;
            break;
            default:
                if (c < '0' || c > '9') {
                    throw std::runtime_error("Invalid char " + c);
                }
                if (parser == (unsigned long) -1) {
                    parser = (unsigned long) (c - '0');
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