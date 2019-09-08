//
//  Player.hpp
//  Connect 4
//
//  Created by Madeleine Murphy on 6/15/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include <iostream>
#include <stdio.h>
#include "Color.h"
#include "Board.h"
using namespace std;

class Player
{
public:
    Player(string name);
    //Create a Player with the indicated name.
    string name() const;
    //Return the name of the player.
    virtual bool isInteractive() const;
    //Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
    virtual int chooseMove(const Board& b, Color c) const = 0;
    //Every concrete class derived from this class must implement this function so that if the player were to be playing color c and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.
    virtual ~Player();
    //Since this class is designed as a base class, it should have a virtual destructor.
private:
    string m_name;
};

//Each concrete class derived from Player will implement the chooseMove function in its own way. Of the classes listed here, only HumanPlayer::isInteractive should return true. (When testing, we may supply other kinds of interactive players.) Each of the three classes listed here must have a constructor taking a string representing the name of the player.
class HumanPlayer : public Player
{
public:
    HumanPlayer(string name);
    bool isInteractive() const;
    int chooseMove(const Board& b, Color c) const;
};

class ComputerPlayer : public Player
{
public:
    ComputerPlayer(string name);
    bool isInteractive() const;
    int chooseMove(const Board& b, Color c) const;
};
#endif /* Player_h */
