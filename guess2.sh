#!/bin/bash
#
# guess2.sh
# 
# Description: The user tries to guess a number between 1-100 
# This time, we guide the user toward an answer.
# It still needs some defensive checks on the input!
# 
# Input: The user enters a guess
#
# Output: Status on the guess

echo "I'm thinking of a number between 1-100."
# The correct answer.
answer=31

read -p "Guess my number: " guess

while [[ $guess -ne $answer ]]; do
    # The -gt treats the comparison as numeric rather than alpha.
    if [[ $guess -gt $answer ]]; then
        echo too high!
    else
        echo too low!
    fi

    read -p "Guess my number: " guess
done

echo Correct!
exit 0
