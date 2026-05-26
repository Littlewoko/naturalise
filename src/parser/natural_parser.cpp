#include "natural_parser.h"

ValidationResult NaturalParser::validate(const string &source) {
    ValidationResult res;

    if (source.rfind("* >Natural Source Header", 0) == 0) {
        res.has_valid_header = true;
    } else {
        res.error_count++;
    }

    return res;
}