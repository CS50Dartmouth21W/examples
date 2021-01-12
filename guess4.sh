#!/bin/bash
#
# guess4.sh
# 
# Description: The user tries to guess a number between 1-100 
# This time, we add some defensive checks on the input!
# (Now showing the power of a function specifically for that purpose.)
#
# Input: The user enters a guess
#
# Output: Status on the guess

# Ask the user to guess, and fill global variable $guess with result.
# usage: askguess low high
#   where [low-high] is the range of numbers in which they should guess.
function askguess() {
    read -p "Guess my number (between $1 and $2): " guess
    # Validate their input; it must not be empty, or contain a non-digit.
    # Note we quote $guess because it might be empty or multi-word.
    if [[ "$guess" == "" || "$guess" =~ [^0-9] ]]; then
        echo bad number...
        guess=0
    fi
    # at this point, $guess is guaranteed to be a number.
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
