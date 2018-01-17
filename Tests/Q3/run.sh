cat test.txt | tr '[:space:]' '[\n*]' | tr -d '[:punct:]' |  grep -v "^\s*$" | sort | uniq -c | sort -bnr

