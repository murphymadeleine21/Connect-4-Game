//
//  Game.cpp
//  Connect 4
//
//  Created by Madeleine Murphy on 6/15/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#include "Game.h"

Game::Game(const Board& b, Player* red, Player* black)
: m_board(b), m_RedPlayer(red), m_BlackPlayer(black), m_whoseTurn(m_RedPlayer), m_over(false)
{}
//Construct a Game to be played with the indicated players on a copy of the board b. The Red Player always moves first.

void Game::display() const
{
    for (int i = 0; i < 29; i++)
        cout << "–";
    cout << endl;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (j == 0)
                cout << "| ";
            cout << m_board.checkerInPos(i, j) << " | ";
        }
        
        cout << endl;
    }
    for (int i = 0; i < 29; i++)
        cout << "–";
    cout << endl;
    if (!m_over)
        cout << "CONNECT 4!" << endl;
}
//Display the game's board in a manner of your choosing, provided you show a reasonable representation of the state of the board.

void Game::status(bool& over, bool& hasWinner, Color& winner) const
{
    for (int i = 0; i < ROWS; i++)  //run through every row and see if there's a connection across
    {
        for (int j = 0; j < 4; j++)
        {
            if (m_board.checkerInPos(i, j) == 'O')      //go to next column in that row
                continue;
            if (m_board.checkerInPos(i, j) == 'R')
            {
                if (m_board.checkerInPos(i, j+1) == 'R' && m_board.checkerInPos(i, j+2) == 'R' && m_board.checkerInPos(i, j+3) == 'R')
                {
                    hasWinner = true;
                    winner = RED;
                    over = true;
                    return;
                }
            }
            if (m_board.checkerInPos(i, j) == 'B')
            {
                if (m_board.checkerInPos(i, j+1) == 'B' && m_board.checkerInPos(i, j+2) == 'B'&&
                    m_board.checkerInPos(i, j+3) == 'B')
                {
                    hasWinner = true;
                    winner = BLACK;
                    over = true;
                    return;
                }
            }
        }
    }
    for (int j = 0; j < COLS; j++)  //run through every column and see if there's a connection down
    {
        for (int i = 0; i < 3; i++)
        {
            if (m_board.checkerInPos(i, j) == 'O')      //go to next row down that column
                continue;
            if (m_board.checkerInPos(i, j) == 'R')
            {
                if (m_board.checkerInPos(i+1, j) == 'R' && m_board.checkerInPos(i+2, j) == 'R' && m_board.checkerInPos(i+3, j) == 'R')
                {
                    hasWinner = true;
                    winner = RED;
                    over = true;
                    return;
                }
            }
            if (m_board.checkerInPos(i, j) == 'B')
            {
                if (m_board.checkerInPos(i+1, j) == 'B' && m_board.checkerInPos(i+2, j) == 'B' && m_board.checkerInPos(i+3, j) == 'B')
                {
                    hasWinner = true;
                    winner = BLACK;
                    over = true;
                    return;
                }
            }
        }
    }
    //check diagonals
    //check bottom row diagonals going right first
    //check each row connections right and left diagonal
    for (int row = 5; row > 2; row--)
    {
        for (int j = 0; j < 4; j++)     //check going right
        {
            if (m_board.checkerInPos(row, j) == 'O')  //move over to next column
                continue;
            if (m_board.checkerInPos(row, j) == 'R')
            {
                if (m_board.checkerInPos(row-1, j+1) == 'R' && m_board.checkerInPos(row-2, j+2) == 'R' && m_board.checkerInPos(row-3, j+3) == 'R')    //diagonal connection up from bottom going right
                {
                    hasWinner = true;
                    winner = RED;
                    over = true;
                    return;
                }
            }
            if (m_board.checkerInPos(row, j) == 'B')
            {
                if (m_board.checkerInPos(row-1, j+1) == 'B' && m_board.checkerInPos(row-2, j+2) == 'B' && m_board.checkerInPos(row-3, j+3) == 'B')    //diagonal connection up from bottom going right
                {
                    hasWinner = true;
                    winner = BLACK;
                    over = true;
                    return;
                }
            }
        }
        for (int j = 3; j < COLS; j++)     //check going left from bottom
        {
            if (m_board.checkerInPos(row, j) == 'O')  //move over to next column
                continue;
            if (m_board.checkerInPos(row, j) == 'R')
            {
                if (m_board.checkerInPos(row-1, j-1) == 'R' && m_board.checkerInPos(row-2, j-2) == 'R' && m_board.checkerInPos(row-3, j-3) == 'R')    //diagonal connection up from bottom going left
                {
                    hasWinner = true;
                    winner = RED;
                    over = true;
                    return;
                }
            }
            if (m_board.checkerInPos(row, j) == 'B')
            {
                if (m_board.checkerInPos(row-1, j-1) == 'B' && m_board.checkerInPos(row-2, j-2) == 'B' && m_board.checkerInPos(row-3, j-3) == 'B')    //diagonal connection up from bottom going left
                {
                    hasWinner = true;
                    winner = BLACK;
                    over = true;
                    return;
                }
            }
        }
    }
    
    //if we made it all the way without finding any connections, and there are still checkers in play the game is not over
    if (m_board.checkersToPlay(RED) == 0 && m_board.checkersToPlay(BLACK) == 0)     //if there are no connections and no checkers, we have a tie
    {
        over = true;
        hasWinner = false;
        return;
    }
    over = false;
    
}
//If the game isn't over (i.e., more moves are possible), set over to false and do not change anything else. Otherwise, set over to true and hasWinner to true if the game has a winner.

bool Game::move()
{
    display();
    status(m_over, m_hasWinner, m_winner);
    if (m_over)
    {
        return false;
    }
    
    int slot = m_whoseTurn->chooseMove(m_board, playerColor(m_whoseTurn));
    if (slot == -1)
        return false;
    cout << m_whoseTurn->name() << " chooses slot " << slot << endl;
    cout << endl;
    if (m_board.drop(playerColor(m_whoseTurn), slot) == true)
    {
        status(m_over, m_hasWinner, m_winner);
        if (m_over == true)
        {
            display();
            return false;
        }
    }
    
    if (playerColor(m_whoseTurn) == RED)
        m_whoseTurn = m_BlackPlayer;
    else
        m_whoseTurn = m_RedPlayer;
    return true;
}
//If the game is over, return false. Otherwise, make a complete move for the player whose turn it is (so that it becomes the other player's turn) and return true. "Complete" means that the player drops a checker into a slot.

void Game::play()
{
    if (move())
        play();
    else{
        if (m_hasWinner == false)
            cout << "The game resulted in a tie." << endl;
        else
            cout << "The winner is " << player(m_winner)->name() << "." << endl;
    }
}
//Play the game. Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow what's happening. 


Color Game::playerColor(Player* turn)
{
    if (turn == m_RedPlayer)
        return RED;
    else
        return BLACK;
}

Player* Game::player(Color c)
{
    if (c == RED)
        return m_RedPlayer;
    else
        return m_BlackPlayer;
}
