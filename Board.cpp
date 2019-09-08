//
//  Board.cpp
//  Connect 4
//
//  Created by Madeleine Murphy on 6/15/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#include "Board.h"

Board::Board()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
            m_grid[i][j] = 'O';
    }
    m_redToPlay = 21;
    m_blackToPlay = 21;
    m_totalCheckers = 42;
    m_checkersInPlay = 0;
}
//Construct an empty Board 7x6, 21 checkers for each player

int Board::checkersToPlay(Color c) const
{
    if (c == RED)
        return m_redToPlay;
    else
        return m_blackToPlay;
}
//return the number of checkers that are available to play for the indicated color.


int Board::checkersCol(int column) const
{
    if (column < 1 || column > 7)
        return -1;
    int count = 0;
    for (int i = 0; i < ROWS; i++)
    {
        if (m_grid[i][column-1] == 'R' || m_grid[i][column-1] == 'B')
            count++;
    }
    return count;
}
//Return the number of checkers in the indicated column, or −1 if the column number is invalid.

bool Board::full(int column) const
{
    if (checkersCol(column) == 6)
        return true;
    return false;
}

int Board::checkersRow(int row) const
{
    if (row < 1 || row > 6)
        return -1;
    int count = 0;
    for (int i = 0; i < COLS; i++)
    {
        if (m_grid[row][i] == 'R' || m_grid[row][i] == 'B')
            count++;
    }
    return count;
}
//return number of checkers in the indicated row, or -1 if invalid

int Board::colorCheckersCol(int column, Color c) const
{
    if (column < 1 || column > 7)
        return -1;
    int count = 0;
    if (c == RED)
    {
        for (int i = 0; i < ROWS; i++)
        {
            if (m_grid[i][column-1] == 'R')
                count++;
        }
    }
    else
    {
        for (int i = 0; i < ROWS; i++)
        {
            if (m_grid[i][column-1] == 'B')
                count++;
        }
    }
    return count;
}
//return number of indicated color's checkers in a column, or -1 if invalid


int Board::colorCheckersRow(int row, Color c) const
{
    if (row < 1 || row > 6)
        return -1;
    int count = 0;
    if (c == RED)
    {
        for (int i = 0; i < COLS; i++)
        {
            if (m_grid[row-1][i] == 'R')
                count++;
        }
    }
    else
    {
        for (int i = 0; i < ROWS; i++)
        {
            if (m_grid[row-1][i] == 'B')
                count++;
        }
    }
    return count;
}
//return number of indicated color's checkers in a row, or -1 if invalid


int Board::checkersInPlayC(Color c) const
{
    if (c == RED)
        return m_redInPlay;
    else
        return m_blackInPlay;
}
//Return the total number of checkers in play for the indicated color.


int Board::totalCheckers() const
{
    return m_totalCheckers;
}
//Return the total number of checkers in the game for both players

int Board::checkersInPlay() const
{
    return m_checkersInPlay;
}
//return the total number of checkers in play in the game

char Board::checkerInPos(int row, int col) const
{
    return m_grid[row][col];
}
//return the character at that Grid


bool Board::drop(Color c, int column)
{
    if (column < 1 || column > 7)   //invalid
        return false;
    if (full(column))   //full
        return false;
    if (c == RED)           //if the player has no checkers left to play
    {
        if (m_redToPlay == 0)
            return false;
        else
        {
            int row = 0;
            while (row < 6 && m_grid[row][column-1] == 'O')    //find the first row that is occupied, or hit the bottom
                row++;
            row--;      //go to the row above it
            m_grid[row][column-1] = 'R';
            m_redInPlay++;
            m_redToPlay--;
            m_checkersInPlay++;
            
        }
    }
    else if (c == BLACK)
    {
        if (m_blackToPlay == 0)     //if the player has no checkers left to play
            return false;
        else
        {
            int row = 0;
            while (row < 6 && m_grid[row][column-1] == 'O')    //find the first row that is occupied, or hit the bottom
                row++;
            row--;      //go to the row above it
            m_grid[row][column-1] = 'B';
            m_blackInPlay++;
            m_blackToPlay--;
            m_checkersInPlay++;
            
        }
    }
    return true;
}
//If the column indicated by (column) is full or invalid, or if the player has no checkers left to play, this function returns false without changing anything. Otherwise, it will return true after dropping the checker: the checker is placed into the top most empty row space in the column. The indicated color's number of checkers available for play will decrease by 1. The parameter endRow is set to the row the checker was placed in.

