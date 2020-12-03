//A program coded by Jan Roces

#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>
#include <iomanip>
#include <vector>
#include <fstream>
#include <ctime>
#include "mastermind.h"

using namespace std;

string colors[6] = {"RED", "YELLOW", "GREEN", "BLUE", "BLACK", "WHITE"};
bool checkInput(string[]);
void printGameBoard(guess[], int);
void printBlankBoard(mastermind, int, bool);

//CLASS CONSTRUCTORS AND FUNCTIONS
//--------------------------------------------------------------------------------
mastermind::mastermind(int size) : MAX_MOVES(10)
{
    cols = size;
    moves = 0;
    
    for (int i=0; i<cols; i++)
    {
        pegs[i] = "red";
    }
}


mastermind::mastermind(int size, string initial[]): MAX_MOVES(10)
{
    cols = size;
    moves = 0;
    string color;
    int n;

    for (int i=0; i<cols; i++)
    {
        n = initial[i].length();

        for (int j=0; j<n; j++)
        {
            initial[i][j] = toupper(initial[i][j]);
        }

        pegs[i] = initial[i];
    }
}

int mastermind::move(string playerMove[], int& x, int& o)
{
    x = 0;
    o = 0;
    int n;

    for (int i=0; i<cols; i++)
    {
        n = playerMove[i].length();

        for (int j=0; j<n; j++)
        {
            playerMove[i][j] = toupper(playerMove[i][j]);
        }
    }

    for (int i=0; i<4; i++)
    {
        if (pegs[i] == playerMove[i])
        {
            x++;
        }

        else
        {
            for (int j=0; j<4; j++)
            {
                if (i == j)
                    continue;

                else 
                {
                    if (pegs[i] == playerMove[j])
                    {
                        o++;
                        break;
                    }
                }
            }
        }
        
    }

    if ((moves == MAX_MOVES) && (x != 4))
        return -1;
    else if (x == 4)
        return 1;
    else
        return 0;
}

int mastermind::getMoveIndex()
{
    moves++;
    return moves;
}

string mastermind::getPegs(int n)
{
    return pegs[n];
}

//MAIN FUNCTIONS
//--------------------------------------------------------------------------------
bool checkInput(string input[])
{
    int n = 0;
    int m;
    int len;

    for (int i=0; i<4; i++)
    {
        len = input[i].length();

        for (int j=0; j<len; j++)
        {
            input[i][j] = toupper(input[i][j]);
        }
    }

    for (int i=0; i<4; i++)
    {
        for (int j=0; j<6; j++)
        {
            if (input[i] == colors[j])
            {
                n++;
                break;
            }
        }
    }

    if (n == 4)
        return true;

    else
        return false;
}

void printBlankBoard(mastermind game, int n, bool r)
{
    string border = " --------------------------------------------------------------- ";
    int a = 9;
    int b = 55;
    int c = 12;
    int d = 64;
    
    if (n == 10 || r == true)
    {
        cout << border << endl;
        cout << "|" << setw(d) << setfill(' ') << "|" << endl;
        cout << "|    ";
        for (int i=0; i<4; i++)
        {
            cout << setfill(' ') << setw(c) << game.getPegs(i);
        }
        cout << setfill(' ') << setw(c) << "|" << endl;
        cout << "|" << setw(d) << setfill(' ') << "|" << endl;
        n = 10 - n;
    }

    else
    {
        n = 10 - n;
        cout << border << endl;
        cout << "|" << setw(d) << setfill(' ') << "|" << endl;
        cout << "|    ";
        for (int i=0; i<4; i++)
        {
            cout << setfill(' ') << setw(c) << "XXXX";
        }
        cout << setfill(' ') << setw(c) << "|" << endl;
        cout << "|" << setw(d) << setfill(' ') << "|" << endl;
    }

    for (int i=0; i<n; i++)
    {
        cout << border << endl;
        cout << "|" << setw(a) << setfill(' ') << "|" << setw(b) << setfill(' ') << "|" << endl;
        cout << "|" << setw(a) << setfill(' ') << "|" << setw(b) << setfill(' ') << "|" << endl;
        cout << "|" << setw(a) << setfill(' ') << "|" << setw(b) << setfill(' ') << "|" << endl;
    }
}

void printGameBoard(guess game[], int currTurn)
{
    string border = " --------------------------------------------------------------- ";
    int a = 7;
    int b = 12;
    int c = 55;
    
    for (int i=currTurn-1; i>=0; i--)
    {
        cout << border << endl;
        cout << "| Turn " << left << setw(2) << setfill(' ') << game[i].turn << "|";
        cout << right <<setw(c) << setfill(' ') << "|" << endl;
        cout << "| x = " << game[i].x << "  |";

        for (int j=0; j<4; j++)
        {
            cout << right << setw(b) << game[i].guess[j] << setfill(' ');
        }

        cout << setw(a) << setfill(' ') << "|" << endl;
        cout << "| o = " << game[i].o << "  |" << setw(c) << setfill(' ') << "|" << endl;
    }
    cout << border << endl;
    cout << "  x: correct color in correct position" << endl;
    cout << "  o: correct color in wrong position" << endl;
    cout << endl << endl;
}

//MAIN
//--------------------------------------------------------------------------------
int main()
{
    srand(time(0));
    string winningColors[4];
    int r;

    for (int i=0; i<4; i++)
    {
        r = rand() % 6;
        winningColors[i] = colors[r];
    }

    mastermind myGame(4, winningColors);
    guess guessesArr[10];
    string play[4];
    string line;
    
    int determineGame = 0;
    int count = 0;
    int x;
    int o;
    int turn;
    bool check;
    bool reveal = false;
    
    while ((determineGame != 1) && (determineGame != -1))
    {
        turn = myGame.getMoveIndex();
        cout << "Turn: " << turn << endl;
        cout << "Enter 4 colors (choices: red, yellow, green, blue, black, white): " << endl;
        
        for (int i=0; i<4; i++)
        {
            cin >> play[i];
        }

        while (checkInput(play) == false)
        {
            cout << "ERROR in input. Try again." << endl << endl;
            cout << "Turn: " << turn << endl;
            cout << "Enter 4 colors (choices: red, yellow, green, blue, black, white): " << endl;
        
            for (int i=0; i<4; i++)
                cin >> play[i];
        }

        determineGame = myGame.move(play, x, o);

        for (int i=0; i<4; i++)
            guessesArr[turn-1].guess[i] = play[i];

        guessesArr[turn-1].x = x;
        guessesArr[turn-1].o = o;
        guessesArr[turn-1].turn = turn; 

        cout << endl << endl;

        ifstream logo ("logo.txt");
        if (logo.is_open())
        {
            while (getline(logo,line))
                cout << line << endl;
            logo.close();
        }
        printBlankBoard(myGame, turn, reveal);
        printGameBoard(guessesArr, turn);
    }
    
    if (determineGame == 1)
    {
        reveal = true;
        cout << endl << endl;

        ifstream logo ("logo.txt");
        if (logo.is_open())
        {
            while (getline(logo,line))
                cout << line << endl;
            logo.close();
        }
        printBlankBoard(myGame, turn, reveal);
        printGameBoard(guessesArr, turn);

        ifstream win ("win.txt");
        if (win.is_open())
        {
            while (getline(win,line))
                cout << line << endl;
            win.close();
        }
    }
    
    if (determineGame == -1)
    {
        cout << endl << endl;

        ifstream logo ("logo.txt");
        if (logo.is_open())
        {
            while (getline(logo,line))
                cout << line << endl;
            logo.close();
        }
        printBlankBoard(myGame, turn, reveal);
        printGameBoard(guessesArr, turn);
        
        ifstream lose ("lose.txt");
        if (lose.is_open())
        {
            while (getline(lose,line))
                cout << line << endl;
            lose.close();
        }
    }

    return 0;
}
