#! /usr/bin/env python3

import os
import sys
from contextlib import nullcontext

target = 'program'

if __name__ == '__main__':
    with open(sys.argv[1]) as fin:
        input_file = fin.read()

    if os.path.exists(sys.argv[3] + '.h'):
        write_header = False
        open_func = nullcontext
    else:
        write_header = True
        def open_func(): return open(sys.argv[3] + '.h', 'w')

    with open(sys.argv[2], "w") as yy_out, open_func() as header_out:
        header, rules, footer = input_file.split("%%")

        now_rule_name = ''

        print(header, file=yy_out)
        print("%%", file=yy_out)

        if write_header:
            print("#include \"ast.h\"\n#include \"lexer.h\"\n", file=header_out)

        lino = 0
        for line in rules.split('\n'):
            line = line.strip()
            if len(line) == 0:
                print(file=yy_out)
                continue
            if line.find(':') != -1:
                now_rule_name, now_rule = map(str.strip, line.split(':'))
                lino = 0
            elif line.find('|') != -1:
                now_rule = line[line.find('|') + 1:].strip()
            else:
                print(line, file=sys.stderr)

            if now_rule.find("%") != -1:
                now_rule = now_rule[:now_rule.find("%")]
            now_patterns = now_rule.split()
            """
            print("%s {puts(\"%s\"); yyprocess(\"%s\", $$, %s); %s}" % (
                line,
                "%s: %s" % (now_rule_name, ' '.join(now_patterns)),
                now_rule_name,
                '{' + ', '.join(["$%d" % x for x in range(1,
                                                          1 + len(now_patterns))]) + '}',
                '' if now_rule_name != target else 'result = $$; YYACCEPT;'
            ), file=yy_out)"""
            print("%s {/*puts(\"%s\");*/ yyprocess_%s_%d(\"%s\", $$, %s); %s}" % (
                line,
                "%s: %s" % (now_rule_name, ' '.join(now_patterns)),
                now_rule_name,
                lino,
                now_rule_name,
                '{' + ', '.join(["$%d" % x for x in range(1,
                                                          1 + len(now_patterns))]) + '}',
                '' if now_rule_name != target else 'result = $$; YYACCEPT;'
            ), file=yy_out)
            if write_header:
                print("//%s: %s" %
                      (now_rule_name, ' '.join(now_patterns)), file=header_out)
                print(
                    "void yyprocess_%s_%d(std::string name, YYSTYPE &self, std::vector<YYSTYPE> children) {\n}\n\n" % (
                        now_rule_name,
                        lino
                    ),
                    file=header_out)
            lino += 1

        print("%%", file=yy_out)
        print(footer, file=yy_out)
