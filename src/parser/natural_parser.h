#pragma once
#include <string>

using namespace std;

struct ValidationResult {
    bool has_valid_header = false;
    int error_count = 0;
};

class NaturalParser {
    public:
        ValidationResult validate(const string &source);
};