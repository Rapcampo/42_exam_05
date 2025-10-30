#!/bin/bash

#set -x
test_file="tests.txt"

echo "\n\n\n \e[1;32mINVALID MAPS!\e[0m"

while IFS= read -r command; do
    echo "Executing map: $command"
    echo -e "\n\e[1;33m\tMAP TILE\n\e[0m"
    cat $command
    echo -e "\n\e[1;31m\tAFTER BSQ\n\e[0m"
    valgrind -q --leak-check=full --show-leak-kinds=all ./bsq $command
done < "$test_file"
