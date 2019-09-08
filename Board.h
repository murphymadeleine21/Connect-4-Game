//
//  Board.hpp
//  Connect 4
//
//  Created by Madeleine Murphy on 6/15/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#ifndef Board_h
#define Board_h
#include "Color.h"
#include <stdio.h>


class Board
{
public:
    Board();
    //Construct an empty Board 6rowsx7cols, 21 checkers for each player (R for Red, B for Black)
    int checkersToPlay(Color c) const;
    //return the number of checkers that are available to play for the indicated color.
    int checkersCol(int column) const;
    //Return the number of checkers in the indicated column, or −1 if the column number is invalid.
    bool full(int column) const;
    //return if the column is full
    int checkersRow(int row) const;
    //return number of checkers in the indicated row, or -1 if invalid
    int colorCheckersCol(int column, Color c) const;
    //return number of indicated color's checkers in a column, or -1 if invalid
    int colorCheckersRow(int row, Color c) const;
    //return number of indicated color's checkers in a row, or -1 if invalid
    int checkersInPlayC(Color c) const;
    //Return the total number of checkers in play for the indicated color.
    int checkersInPlay() const;
    //return the total number of checkers in play in the game
    int totalCheckers() const;
    //Return the total number of checkers in the game for both players
    
    char checkerInPos(int row, int col) const;
    //return the character at that Grid
    
    bool drop(Color c, int column);
    //If the column indicated by (column) is full or invalid, or if the player has no checkers left to play, this function returns false without changing anything. Otherwise, it will return true after dropping the checker: the checker is placed into the top most empty row space in the column. The indicated color's number of checkers available for play will decrease by 1. The parameter endRow is set to the row the checker was placed in.
      
    
   private:
    char m_grid[6][7];
    int m_redToPlay;
    int m_blackToPlay;
    int m_totalCheckers;
    int m_checkersInPlay;
    int m_redInPlay;
    int m_blackInPlay;
};

#endif /* Board_h */
