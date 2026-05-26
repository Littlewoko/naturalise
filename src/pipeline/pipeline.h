#pragma once
#include <vector>
#include "rules/base_rule.h"
#include "utils/types.h"

using namespace std;

class RulePipeline {
private:
    vector<BaseRule *> m_rules;
public:
    explicit RulePipeline(vector<BaseRule *> rules) : m_rules(std::move(rules)) {}
    vector<Violation> run(vector<Chunk> &chunks);
};