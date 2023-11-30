#include "Player.h"

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    // more actions to be included
    objPos tempPos;
    // Sets the initial player position to the center of the board.
    tempPos.setObjPos((mainGameMechsRef->getBoardSizeX()) / 2, (mainGameMechsRef->getBoardSizeY()) / 2, '@');
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);
    //alternative? playerPosList.insertHead(setObjPos((mainGameMechsRef->getBoardSizeX()) / 2, (mainGameMechsRef->getBoardSizeY()) / 2, '@'););
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
}

Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    
    // PPA3 input processing logic
    switch (mainGameMechsRef->getInput())
    {
    case 'w':
        if (myDir != UP && myDir != DOWN)
        {
            myDir = UP;
        }
        break;
    case 'a':
        if (myDir != LEFT && myDir != RIGHT)
        {
            myDir = LEFT;
        }
        break;
    case 's':
        if (myDir != UP && myDir != DOWN)
        {
            myDir = DOWN;
        }
        break;
    case 'd':
        if (myDir != LEFT && myDir != RIGHT)
        {
            myDir = RIGHT;
        }
        break;
    default:
        break;
    }
    mainGameMechsRef->clearInput();
}

void Player::movePlayer()
{
    objPos currHead;
    playerPosList->getHeadElement(currHead);
    // PPA3 Finite State Machine logic
    switch (myDir)
    {
    case LEFT:
        currHead.x--;
        break;
    case RIGHT:
        currHead.x++;
        break;
    case UP:
        currHead.y--;
        break;
    case DOWN:
        currHead.y++;
        break;
    case STOP:
    default:
        break;
    }

    // Border Wraparound
    if (currHead.x <= 0)
    {
        currHead.x = (mainGameMechsRef->getBoardSizeX() - 2);
    }
    else if (currHead.x >= (mainGameMechsRef->getBoardSizeX() - 1))
    {
        currHead.x = currHead.x % (mainGameMechsRef->getBoardSizeX() - 2);
    }
    else if (currHead.y <= 0)
    {
        currHead.y = (mainGameMechsRef->getBoardSizeY() - 2);
    }
    else if (currHead.y >= (mainGameMechsRef->getBoardSizeY() - 1))
    {
        currHead.y = currHead.y % (mainGameMechsRef->getBoardSizeY() - 2);
    }
    
    playerPosList->insertHead(currHead);  //insert current head

    playerPosList->removeTail();    //remove tail   
}
