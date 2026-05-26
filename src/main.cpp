#include <iostream>
#include <vector>
#include "chunker/chunker.h"
#include "pipeline/pipeline.h"
#include "rules/comment_rule.h"
#include "rules/line_rule.h"
#include "parser/natural_parser.h"

using namespace std;

int main() {
    CommentRule comment_rule;
    LineRule line_rule;
    vector<BaseRule *> active_rules = { &comment_rule, &line_rule };

    Chunker chunker;
    RulePipeline pipeline(active_rules);

    // TODO: allow passing of files (need to pipe file in for now)
    auto chunks = chunker.chunk(cin);

    auto violations = pipeline.run(chunks);

    if (violations.empty()) {
        cout << "You're a natural!" << endl;
        return 0;
    }

    for (const auto &v: violations) {
        cout << "[" << v.level << "]" << " line: " << v.line_number << " | message: " << v.message << endl;
    }

    // violations indicate error! (maybe look at this in case all are warn)
    return 1;
}