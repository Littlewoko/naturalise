#pragma once
#include <vector>
#include <string>
#include "utils/types.h"

using namespace std;

namespace TestUtil {
    inline bool has_violation(const vector<Violation> &violations,
                            int line,
                            const string &message,
                            ViolationLevel level) {
        for (auto const &v: violations) {
            if (v.level == level 
            && v.line_number == line
            && (v.message.find(message) != string::npos)) {
                return true;
            }
        }

        return false;
    }
}