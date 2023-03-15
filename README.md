# Install JUCE framework

https://juce.com/download/

```
git clone https://github.com/juce-framework/JUCE.git
```

## Start JUCE

https://github.com/juce-framework/JUCE/blob/master/README.md

## JUCE documentation

https://juce.com/learn/tutorials/

# Guess My Number with JUCE

I have recreated this simple game using JUCE framework.

# Description

It's a simple game in which the computer chooses a number between a specified range of numbers, and the user tries to guess the number through a series of guesses. The goal of the game is to guess the number in the fewest number of guesses possible.

# The game has three difficulty levels

1. Easy level:
- The computer chooses a number within a range, such as between 1 and 10.
2. Normal level:
- The computer chooses a number within a range, such as between 1 and 100.
3. Hard level:
- The computer chooses a number within a range, such as between 1 and 1000.

# The game

1. The computer chooses a number at a chosen level.
2. The user makes a guess as to what number the computer has chosen.
3. The computer responds to the guess by saying "greater", "less", or "win".
4. Steps 2 and 3 are repeated until the user correctly guesses the number.
5. The program keeps track of the number of tries that the user has made.

# To-do

- Rewrite the Menu Chooser to display the difficulty level buttons after clicking the play button.
- Add game option for "who guess the number". The player can pick a number and the computer must guess what it is.
