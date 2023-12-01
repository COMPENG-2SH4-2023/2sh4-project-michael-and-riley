#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 100000

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// Global declarations:
GameMechs *game;
Player *player;

int main(void)
{

    Initialize();

    // Use the exit flag from the game mechanics class
    while (game->getExitFlagStatus() == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    // Initializing:
    game = new GameMechs(); // Use the default constructor for defualt board size.
    player = new Player(game);
    objPosArrayList *startBody = player->getPlayerPos();
    game->generateFood(startBody);
}

void GetInput(void)
{
    if (MacUILib_hasChar())
    {
        // updates the current input in the game mechanics object when a key is pressed.
        game->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    // Update the player position every loop cycle
    player->updatePlayerDir();
    player->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    bool drawn;
    objPosArrayList *playerBody = player->getPlayerPos();
    objPos tempPos2, tempBody; // Create a temporary object to retrieve the values which are passed by reference
    game->getFoodPos(tempPos2);

    for (int i = 0; i < game->getBoardSizeY(); i++)
    {
        for (int j = 0; j < game->getBoardSizeX(); j++)
        {
            drawn = false;
            for (int k = 0; k < playerBody->getSize(); k++)
            {
                playerBody->getElement(tempBody, k);
                if (tempBody.x == j && tempBody.y == i)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                }
            }
            if (drawn)
                continue;
            // Prints the static border in the draw area
            if (i == 0 || i == (game->getBoardSizeY() - 1))
            {
                MacUILib_printf("#");
            }
            else if (j == 0 || j == (game->getBoardSizeX() - 1))
            {
                MacUILib_printf("#");
            }

            else if (j == tempPos2.x && i == tempPos2.y)
            {
                MacUILib_printf("%c", tempPos2.symbol);
            }
            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("Score: %d\n", game->getScore());
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();

    if (game->getLoseFlagStatus()) // If the player self collided, print game over message
    {
        MacUILib_printf("--- GAME OVER ---\n");
    }
    MacUILib_printf("Exiting game... \nThank you for playing!\n");

    MacUILib_uninit();
}
