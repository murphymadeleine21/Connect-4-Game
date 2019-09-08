//
//  main.cpp
//  Connect 4
//
//  Created by Madeleine Murphy on 6/15/19.
//  Copyright © 2019 Madeleine Murphy. All rights reserved.
//

#include <iostream>
#include <cassert>
using namespace std;

#include "Board.h"
#include "Player.h"
#include "Game.h"

int main()
{
    HumanPlayer mad("Player 1");
    ComputerPlayer tom("Maddie's Awesome Player");
    Board game1;
    Game yay(game1, &mad, &tom);
    yay.play();
}
