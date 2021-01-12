#!/bin/bash
#
# guess1.sh
# 
# Description: The user tries to guess a number between 1-100 
# We change the expression to use [[ and -gt for arithmetical comparison.
#
# This is not a good program. There is no check on what the
# user enters; it might be outside the range.
# Heck - it might not even be a number and might be empty!
# Some defensive programming would check the input.
# 
# Input: The user enters a guess
#
# Output: Status on the guess

echo "I'm thinking of a number between 1-100."
# The correct answer.
answer=31

read -p "Guess my number: " guess

while [[ $guess -ne $answer ]]; do
    echo "Wrong! try again"
    read -p "Guess my number: " guess
done

echo Correct!
exit 0
