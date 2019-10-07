//
//  main.cpp
//  a2
//
//  Created by Noah Wolf on 10/5/19.
//  Copyright © 2019 Noah Wolf. All rights reserved.
//
#include <iostream>
#include <time.h>
#include <iomanip>
using namespace std;

//Define constant variables and a variable to hold guesses
const int ROWS = 8;
const int COL = 8;
int guesses = 5;



//Main function... contains each function declaration
int main()
{

    //declares the board 2-D array
    char gameArray[ROWS][COL];
    char play;
    
    int initializeArray(char gameArray[ROWS][COL]);
    int displayArray(char gameArray[ROWS][COL]);
    int fillArray(char gameArray[ROWS][COL]);
    int game(char gameArray[ROWS][COL]);
    int instructions();

    //do...while loop to check if user wants to play again
    do
    {

        initializeArray(gameArray);
        displayArray(gameArray);
        fillArray(gameArray);
        instructions();
        game(gameArray);
    
        cout << "Play Again? Enter 'Y'" << endl;
        cin >> play;

        //Gives user 5 guesses if they want to play again
        if(play == 'Y' || play == 'y')
        {
            guesses = 5;
        }
    
    }while(play == 'Y' || play == 'y');

    return 0;
}



//FUNCTION to place a ? in every spot on the game board
//and reset guesses to 5 to ensure user has correct amount of guesses
int initializeArray(char gameArray[ROWS][COL])
{

    int row, column;
    guesses = 5;

    //For loop to fill the board with question marks
    for (row = 0; row < ROWS; row++)
    {

        for (column = 0; column < COL; column++)
        {
            gameArray[row][column] = '?';
        }

    }

    return 0;
}



//FUNCTION to print the game board to the console
//Utilizes setw() to set the width of the field to provide better spacing
//Adds 1 to column and row because arrays start at 0
int displayArray(char gameArray[ROWS][COL])
{
    int row;
    int column;

    cout << endl;
    cout << "   ";
    
    for (column = 0; column < COL; column++)
    {
        cout << setw(3) << column + 1;
    }

    cout << endl;
    cout << "   -------------------------" << endl;


    for (row = 0; row < ROWS; row++)
    {
        cout << " " << row + 1 << "|";

        for (column = 0; column < COL; column++)
        {
            cout << setw(3) << gameArray[row][column];
        }
        
        cout << endl;
    }


    cout << "   -------------------------" << endl;

    return 0;
}



//FUNCTION that displays game instructions
int instructions()
{

    cout << endl;
    cout << "**" << " ********************* " << "**" << endl;
    cout << "**" << "      Find Gold!       " << "**" << endl;
    cout << "**" << "  You have 5 guesses,  " << "**" << endl;
    cout << "**" << "   5 pieces of gold    " << "**" << endl;
    cout << "**" << "      and 1 bomb       " << "**" << endl;
    cout << "**" << "      Good Luck!       " << "**" << endl;
    cout << "**" << "                       " << "**" << endl;
    cout << "**" << " P.S. If you find gold " << "**" << endl;
    cout << "**" << "   you earn an extra   " << "**" << endl;
    cout << "**" << "        guess!         " << "**" << endl;
    cout << "**" << " ********************* " << "**" << endl;
    cout << endl;
    cout << endl;

    return 0;
}



//FUNCTION that randomly fills the array with gold and a bomb
int fillArray(char gameArray[ROWS][COL])
{

    int bomb = 0;
    int gold = 0;
    int x;
    int y;
    srand(time_t(NULL));//Xcode kept giving me a build fail with srand(time(null))
                        //time_t fixed the build fail, but not sure if it's exactly
                        //what I was supposed to use?

    //do...while loop to place gold in 5 different/random places
    do
    {

        //gets a random row and column
        x = rand() % ROWS;
        y = rand() % COL;

        //checks to make sure gold isn't already at the random coordinates
        if (gameArray[x][y] != 'G')
        {
            gameArray[x][y] = 'G';
                gold++;
        }

    }while (gold < 5);

    
    //do...while loop to place 1 bomb in a random spot
    do
    {

        x = rand() % ROWS;
        y = rand() % COL;

        //checks to verify that gold isn't where the bomb is to be placed
        if (gameArray[x][y] != 'G')
        {
            gameArray[x][y] = 'B';
                bomb++;
        }

    }while (bomb < 1);

    return 0;
}



//FUNCTION to track user input and score the game
//displays final game board without question marks and shows F, G, and B
//for found gold, unfound gold, and the bomb
int game(char gameArray[ROWS][COL])
{
    
    int score = 0;
    int guessR;
    int guessC;

    do
    {

        cout << "Enter x coordinate between 1 and 8: ";
        cin >> guessR;


        //While loop to check for valid user input
        //Uses cin.clear and cin.ignore to clear and reset invalid input from cin
        while (!cin || guessR < 1 || guessR > 8)
        {
            cout << "ERROR!" << endl;
            cout << "Please enter a number between 1 and 8: ";
            cin.clear();
            cin.ignore();
            cin >> guessR;
        }
        
        guessR--;
        
        cout << endl;
        cout << "Enter y coordinate between 1 and 8: ";
        cin >> guessC;

        //Another while loop to check for valid input
        while (!cin || guessC < 1 || guessC > 8)
        {
            cout << "ERROR!" << endl;
            cout << "Please enter a number between 1 and 8: ";
            cin.clear();
            cin.ignore();
            cin >> guessC;
        }

        guessC--;
        cout << endl;


        //Extra credit
        if (gameArray[guessR][guessC] == 'G')
        {

            cout << "You Found GOLD!! ";
            cout << "You earned an extra guess!!" << endl;
            cout << "You now have " << guesses << " guesses left!" << endl;
            cout << endl;
            
            gameArray[guessR][guessC] = 'F';
                score += 1;

            continue;
        }

        //if users' guess hits a bomb game over
        else if (gameArray[guessR][guessC] == 'B')
        {
            cout << endl;
            cout << "BOMB! Game over!" << endl;
            cout << endl;

            break;
        }

        else
        {
            cout << "Too Bad... :(  ";
                guesses--;

            cout << "you have " << guesses << " guesses to go!" << endl;
            cout << endl;
        }

    }while (guesses > 0);


    cout << "You earned " << score << " points!" << endl;
    cout << "Better Luck Next Time" << endl;
    cout << "Here's your board:" << endl;

    
    
    for (guessC = 0; guessC < COL; guessC++)
    {

        for (guessR = 0; guessR < ROWS; guessR++)
        {

            if (gameArray[guessR][guessC] == '?')
            {

                gameArray[guessR][guessC] = ' ';
            }
        }
    }

    
    cout << "   ";
    
    for (guessC = 0; guessC < COL; guessC++)
    {
        cout << setw(3) << guessC + 1;
    }

    cout << endl;
    cout << "   -------------------------" << endl;


    for (guessR = 0; guessR < ROWS; guessR++)
    {
        cout << " " << guessR + 1 << "|";

            for (guessC = 0; guessC < COL; guessC++)
            {
                cout << setw(3) << gameArray[guessR][guessC];
            }
            
            cout << endl;
    }

    cout << "   -------------------------" << endl;

    return 0;
}
