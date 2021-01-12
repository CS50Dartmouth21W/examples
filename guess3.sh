#!/bin/bash
#
# guess3.sh
# 
# Description: The user tries to guess a number between 1-100 
# This time, we move the repeated code into a function.
# It still needs some defensive checks on the input!
# 
# Input: The user enters a guess
#
# Output: Status on the guess

# Ask the user to guess, and fill global variable $guess with result.
# usage: askguess low high
#   where [low-high] is the range of numbers in which they should guess.
function askguess() {
    read -p "Guess my number (between $1 and $2): " guess
}

echo "I'm thinking of a number between 1-100."
# The correct answer.
answer=31

# ask them once
askguess 1 100

while [[ $guess -ne $answer ]]; do
    # The -gt treats the comparison as numeric rather than alpha.
    if [[ $guess -gt $answer ]]; then
        echo too high!
    else
        echo too low!
    fi

    # ask them again
    askguess 1 100
done

echo Correct!
exit 0
