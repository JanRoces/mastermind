This program is based on the 1970 board game: Mastermind and coded by Jan Roces
Its intent is to show usage of data structures, filestreams, searching algorithms, and for fun.
All files contained within the mastermind folder are needed to run this program.
An .exe file is provided to run this program on the terminal, or compile 'mastermind.cpp' with a C++ compiler.

How to play:
1. At program execution, a 'code' of 4 colors is randomly generated from a list of 6 different colors.
    a. Colors may be repeated
    b. There are never blank or missing colors of the combination.
    c. Color code never changes throughout its current run time.

2. The game is to guess what the 4 color combination is.
    a. You are only allowed to choose from the given colors, it will throw an error otherwise.
    b. You are only allowed 10 turns to guess the color combination correctly.
    c. Exceeding 10 turns without correctly guessing the combination will result in a lose.
    d. Correctly guessing the color combination will reveal the color code and will result in a win.

3. After the initial guess, the game board will appear.
    a. The left column tracks turns, x, and o.
    b. x is the number of correctly chosen colors in the correctly placed position.
    c. o is the number of correctly chosen colors in the wrongly placed position.
    d. It is possible that you can guess a color combination that is completly wrong and x and o values will be zero.

