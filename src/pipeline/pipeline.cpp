#include "pipeline.h"

using namespace std;

vector<Violation> RulePipeline::run(vector<Chunk> &chunks) {
    vector<Violation> res;
    for (auto &chunk: chunks) {
        for (auto &rule: m_rules) {
            if (rule->should_run(chunk.type)) {
                rule->validate(chunk, res);
            }
        }
    }

    return res;
}