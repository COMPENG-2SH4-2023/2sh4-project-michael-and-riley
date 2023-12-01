#include "Player.h"

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    // more actions to be included

    playerPosList = new objPosArrayList();

    // Sets the initial player position to the center of the board.
    objPos tempPos(mainGameMechsRef->getBoardSizeX() / 2, (mainGameMechsRef->getBoardSizeY()) / 2, '*');
    playerPosList->insertHead(tempPos);
}

Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList *Player::getPlayerPos()
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
    case 27: // Escape key to force exit
        mainGameMechsRef->setExitTrue();
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

    // Check if collided with a food object
    if (checkFoodConsumption(currHead))
    {
        increasePlayerSize(currHead);
    }
    else
    {
        playerPosList->insertHead(currHead);
        playerPosList->removeTail(); // remove tail if no collision is detected
    }

    // Check for self collisions
    if (checkSelfCollision(currHead))
    {
        // If a collsion is detected, set the exit and lose flags to true and exit.
        mainGameMechsRef->setExitTrue();
        mainGameMechsRef->setLoseFlag();
    }
}

bool Player::checkFoodConsumption(objPos &curHeadPos)
{
    // Detects collision with food object
    objPos foodPos;
    mainGameMechsRef->getFoodPos(foodPos);

    if (curHeadPos.isPosEqual(&foodPos))
    {
        return true;
    }
    return false;
}

void Player::increasePlayerSize(objPos &curHeadPos)
{
    playerPosList->insertHead(curHeadPos);
    mainGameMechsRef->generateFood(playerPosList);
}

bool Player::checkSelfCollision(objPos &curHeadPos)
{
    objPos tempBodyPos;
    for (int i = 1; i < playerPosList->getSize() - 1; i++) // Start the loop after the head position
    {
        playerPosList->getElement(tempBodyPos, i); // Get each body position
        if (curHeadPos.isPosEqual(&tempBodyPos))
        {
            return true;
        }
    }
    return false;
}
