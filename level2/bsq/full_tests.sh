#!/bin/bash

#set -x
test_file="tests.txt"

echo "\n\n\n \e[1;32mINVALID MAPS!\e[0m"

while IFS= read -r command; do
    echo "Executing map: $command"
    cat $command
    echo
    valgrind -q --leak-check=full --show-leak-kinds=all ./bsq $command
done < "$test_file"
