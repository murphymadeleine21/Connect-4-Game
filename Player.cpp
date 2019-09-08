//
//  Player.cpp
//  Connect 4
//
//  Created by Madeleine Murphy on 6/15/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//


#include "Player.h"
#include <string>
using namespace std;

/////PLAYER IMPLEMENTATIONS/////

Player::Player(string name)
: m_name(name)
{}
//Create a Player with the indicated name.

string Player::name() const
{
    return m_name;
}
//Return the name of the player.

bool Player::isInteractive() const
{
    return false;
}
//Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.

Player::~Player()
{}
//Since this class is designed as a base class, it should have a virtual destructor.

//////////////////////////////////////

/////HUMAN PLAYER IMPLEMENTATIONS/////
HumanPlayer::HumanPlayer(string name) : Player(name)
{}

bool HumanPlayer::isInteractive() const
{
    return true;
}


int HumanPlayer::chooseMove(const Board& b, Color c) const
{
    if (b.checkersToPlay(c) == 0)       //if that color has no checkers left to play
        return -1;
    
    cout << "Pick a Slot, " << this->name() << ": ";
    int move;
    cin >> move;
   
    if (move <=0 || move > COLS || b.full(move))       //using recursion
    {
        if (b.full(move))
            cout << "That slot is full!" << endl;
        else
        {
            cout << "The slot number must be from 1 to 7." << endl;
        }
        return chooseMove(b, c);
    }
    
    else return move;
}

//////////////////////////////////////
/// Computer Player Implementation ////

ComputerPlayer::ComputerPlayer(string name) : Player(name)
{}

bool ComputerPlayer::isInteractive() const
{
    return false;
}

int ComputerPlayer::chooseMove(const Board& b, Color c) const
{
    if (b.checkersToPlay(c) == 0)
        return -1;
    if (b.checkersRow(5) == 0)  //if there is nothing in the bottom row
        return 3;               //picks slot 3
    
    if (c == RED)
    {
        for (int i = 0; i < ROWS; i++)  //run through every row and see if there's a connection across
        {
            for (int j = 0; j < 4; j++)
            {
                if (b.checkerInPos(i, j) == 'O')      //go to next column in that row
                    continue;
                if (b.checkerInPos(i, j) == 'R')
                {
                    if (b.checkerInPos(i, j+1) == 'R' && b.checkerInPos(i, j+2) == 'R' && b.checkerInPos(i, j+3) == 'O')
                    {
                        return j+4; //aim for a winning move
                    }
                }
                if (b.checkerInPos(i, j) == 'B')
                {
                    if (b.checkerInPos(i, j+1) == 'B' && b.checkerInPos(i, j+2) == 'B'&&
                        b.checkerInPos(i, j+3) == 'O')
                    {
                        return j+4;     //try to block their winning move
                    }
                }
            }
        }
        for (int j = 0; j < COLS; j++)  //run through every column and see if there's a connection down
        {
            for (int i = 5; i > 2; i--)
            {
                if (b.checkerInPos(i, j) == 'O')      //nothing in that column, or we've gone thru it all
                    break;
                if (b.checkerInPos(i, j) == 'R')
                {
                    if (b.checkerInPos(i-1, j) == 'R' && b.checkerInPos(i-2, j) == 'R' && b.checkerInPos(i-3, j) == 'O')
                    {
                        return i-2;         //aim for a winning move
                    }
                }
                if (b.checkerInPos(i, j) == 'B')
                {
                    if (b.checkerInPos(i-1, j) == 'B' && b.checkerInPos(i-2, j) == 'B' && b.checkerInPos(i-3, j) == 'O')
                    {
                        return i-2;         //try to block their winning move
                    }
                }
            }
        }
        //check diagonal connections
        for (int row = 5; row > 2; row--)
        {
            for (int j = 0; j < 4; j++)     //check going right
            {
                if (b.checkerInPos(row, j) == 'O')  //move over to next column
                    continue;
                if (b.checkerInPos(row, j) == 'R')
                {
                    if (b.checkerInPos(row-1, j+1) == 'R' && b.checkerInPos(row-2, j+2) == 'R' && b.checkerInPos(row-3, j+3) == 'O')    //diagonal connection up from bottom going right
                    {
                        return j+4;     //aim for a winning move
                    }
                    if (b.checkerInPos(row-1, j+1) == 'R' && b.checkersCol(j+2) == 6 - row + 1)
                        return j + 3;      //try to connect 3
                }
                if (b.checkerInPos(row, j) == 'B')
                {
                    if (b.checkerInPos(row-1, j+1) == 'B' && b.checkerInPos(row-2, j+2) == 'B' && b.checkerInPos(row-3, j+3) == 'O' && b.checkersCol(j+3) == 6-row+2)    //diagonal connection up from bottom going right
                    {
                        return j+4;     //block their winning move
                    }
                }
                if (b.checkerInPos(row, j) == 'R' && b.checkerInPos(row-1, j+1) == 'R' && b.checkersCol(j+2) == 6 - row + 1)
                    return j + 3;      //try to connect 3
            }
            for (int j = 3; j < COLS; j++)     //check going left from bottom
            {
                if (b.checkerInPos(row, j) == 'O')  //move over to next column
                    continue;
                if (b.checkerInPos(row, j) == 'R')
                {
                    if (b.checkerInPos(row-1, j-1) == 'R' && b.checkerInPos(row-2, j-2) == 'R' && b.checkerInPos(row-3, j-3) == 'O')    //diagonal connection up from bottom going left
                    {
                        return j-2;     //aim for winning move
                    }
                }
                if (b.checkerInPos(row, j) == 'B')
                {
                    if (b.checkerInPos(row-1, j-1) == 'B' && b.checkerInPos(row-2, j-2) == 'B' && b.checkerInPos(row-3, j-3) == 'O' && b.checkersCol(j-3) == 6-row+2)    //diagonal connection up from bottom going left
                    {
                        return j-2;     //block their winning move
                    }
                }
                if (b.checkerInPos(row, j) == 'R' && b.checkerInPos(row-1, j-1) == 'R' && b.checkersCol(j-2) == 6 - row + 1)
                    return j - 1;      //try to connect 3
            }
        }
        //make a somewhat random move otherwise
        for (int i = 5; i > 0; i--)     //if we can connect two
        {
            for (int j = 0; j < COLS; j++)
            {
                if (b.checkerInPos(i, j) == 'R' && b.checkerInPos(i-1, j) == 'O')
                    return j+1;
                if (b.checkerInPos(i, j) == 'R' && j != 6 && b.checkerInPos(i, j+1) == 'O')
                    return j+2;
            }
        }
        //otherwise just choose the first open spot
        for (int i = 5; i > 0; i--)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (b.checkerInPos(i, j) == 'O')
                    return j+1;
            }
        }
    }
    else
    {
        for (int i = 0; i < ROWS; i++)  //run through every row and see if there's a connection across
        {
            for (int j = 0; j < 4; j++)
            {
                if (b.checkerInPos(i, j) == 'O')      //go to next column in that row
                    continue;
                if (b.checkerInPos(i, j) == 'B')
                {
                    if (b.checkerInPos(i, j+1) == 'B' && b.checkerInPos(i, j+2) == 'B' && b.checkerInPos(i, j+3) == 'O')
                    {
                        return j+4; //aim for a winning move
                    }
                }
                if (b.checkerInPos(i, j) == 'R')
                {
                    if (b.checkerInPos(i, j+1) == 'R' && b.checkerInPos(i, j+2) == 'R'&&
                        b.checkerInPos(i, j+3) == 'O')
                    {
                        return j+4;     //try to block their winning move
                    }
                }
            }
        }
        for (int j = 0; j < COLS; j++)  //run through every column and see if there's a connection down
        {
            for (int i = 5; i > 2; i--)
            {
                if (b.checkerInPos(i, j) == 'O')      //nothing in that column, or we've gone thru it all
                    break;
                if (b.checkerInPos(i, j) == 'B')
                {
                    if (b.checkerInPos(i-1, j) == 'B' && b.checkerInPos(i-2, j) == 'B' && b.checkerInPos(i-3, j) == 'O')
                    {
                        return j+1;         //aim for a winning move
                    }
                }
                if (b.checkerInPos(i, j) == 'R')
                {
                    if (b.checkerInPos(i-1, j) == 'R' && b.checkerInPos(i-2, j) == 'R' && b.checkerInPos(i-3, j) == 'O')
                    {
                        return j+1;         //try to block their winning move
                    }
                }
            }
        }
        //check diagonal connections
        for (int row = 5; row > 2; row--)
        {
            for (int j = 0; j < 4; j++)     //check going right
            {
                if (b.checkerInPos(row, j) == 'O')  //move over to next column
                    continue;
                if (b.checkerInPos(row, j) == 'B')
                {
                    if (b.checkerInPos(row-1, j+1) == 'B' && b.checkerInPos(row-2, j+2) == 'B' && b.checkerInPos(row-3, j+3) == 'O')    //diagonal connection up from bottom going right
                    {
                        return j+4;     //aim for a winning move
                    }
                }
                if (b.checkerInPos(row, j) == 'R')
                {
                    if (b.checkerInPos(row-1, j+1) == 'R' && b.checkerInPos(row-2, j+2) == 'R' && b.checkerInPos(row-3, j+3) == 'O' && b.checkersCol(j+3) == 6-row+2)    //diagonal connection up from bottom going right
                    {
                        return j+4;     //block their winning move
                    }
                }
                if (b.checkerInPos(row, j) == 'B' && b.checkerInPos(row-1, j+1) == 'B' && b.checkersCol(j+2) == 6 - row + 1)
                    return j + 3;      //try to connect 3
            }
            for (int j = 3; j < COLS; j++)     //check going left from bottom
            {
                if (b.checkerInPos(row, j) == 'O')  //move over to next column
                    continue;
                if (b.checkerInPos(row, j) == 'B')
                {
                    if (b.checkerInPos(row-1, j-1) == 'B' && b.checkerInPos(row-2, j-2) == 'B' && b.checkerInPos(row-3, j-3) == 'O')    //diagonal connection up from bottom going left
                    {
                        return j-2;     //aim for winning move
                    }
                }
                if (b.checkerInPos(row, j) == 'R')
                {
                    if (b.checkerInPos(row-1, j-1) == 'R' && b.checkerInPos(row-2, j-2) == 'R' && b.checkerInPos(row-3, j-3) == 'O' && b.checkersCol(j-3) == 6-row+2)    //diagonal connection up from bottom going left
                    {
                        return j-2;     //block their winning move
                    }
                }
                if (b.checkerInPos(row, j) == 'B' && b.checkerInPos(row-1, j-1) == 'B' && b.checkersCol(j-2) == 6 - row + 1)
                    return j - 1;      //try to connect 3
            }
        }
        //make a somewhat random move otherwise
        for (int i = 5; i > 0; i--)     //if we can connect two
        {
            for (int j = 0; j < COLS; j++)
            {
                if (b.checkerInPos(i, j) == 'B' && b.checkerInPos(i-1, j) == 'O')
                    return j+1;
                if (b.checkerInPos(i, j) == 'B' && j != 6 && b.checkerInPos(i, j+1) == 'O')
                    return j+2;
            }
        }
        //otherwise just choose the first open spot
        for (int i = 5; i > 0; i--)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (b.checkerInPos(i, j) == 'O')
                    return j+1;
            }
        }
    }
    return -1;      //a move could not be made
}
