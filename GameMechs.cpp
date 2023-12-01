#include "GameMechs.h"
// Libraries for random object generation
#include <stdlib.h>
#include <time.h>

GameMechs::GameMechs()
{
    input = '\0';
    exitFlag = 0;
    loseFlag = 0;
    score = 0;
    boardSizeX = 30;
    boardSizeY = 15;
    srand(time(NULL)); // For the random object generation
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = '\0';
    exitFlag = 0;
    loseFlag = 0;
    score = 0;
    boardSizeX = boardX;
    boardSizeY = boardY;
    srand(time(NULL)); // For the random object generation
}

// do you need a destructor?

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

void GameMechs::setExitTrue()
{
    exitFlag = 1;
}

void GameMechs::setLoseFlag()
{
    loseFlag = 1;
}

char GameMechs::getInput()
{
    return input;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = '\0';
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore()
{
    score += 1;
}

void GameMechs::generateFood(objPosArrayList *blockOff)
{
    int i = 0, j, randomX, randomY;
    int conflict = 1;

    while (conflict)
    {
        // Generate a new random set of coordinates
        objPos tempBlockCheck;
        conflict = 0;
        randomX = (rand() % (boardSizeX - 2)) + 1;
        randomY = (rand() % (boardSizeY - 2)) + 1;

        // Ensure the coordinate does not overlap with the player position
        for (int k = 0; k < blockOff->getSize(); k++)
        {
            blockOff->getElement(tempBlockCheck, k);
            if (tempBlockCheck.x == randomX && tempBlockCheck.y == randomY)
            {
                conflict = 1;
            }
        }
        if (conflict == 0)
        {
            foodPos.setObjPos(randomX, randomY, '*');
        }
    }
    score = blockOff->getSize() - 1; // Uses the size of array list to keep track of the score
}

void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos = foodPos;
}