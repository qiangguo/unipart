#!/usr/bin/env python3

import re
fname = "test.txt"
buff = {}
with open(fname) as f:
    content = f.readlines()

content = [re.sub(r'[^\w\s]', ' ', v.strip()) for v in content]
content = " ".join(content)
content = sorted([v for v in content.split(" ") if v != ''])

while content:
    head = content[0]
    content = content[1:]
    if head in buff.keys():
        buff[head] += 1
    else:
        buff[head] = 1
        
results = [(buff[key], key) for key in buff.keys()]
results = sorted(results, reverse=True)
for Num, Word in results:
    print(Word, "- occurs ->", Num)
