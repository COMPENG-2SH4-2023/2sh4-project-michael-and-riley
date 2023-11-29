#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

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

    while (exitFlag == false)
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

    exitFlag = false;

    // Initializing:
    game = new GameMechs(); // Use the default constructor for defualt board size.
    player = new Player(game);
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

    objPos tempPos; // Create a temporary object to retrieve the values which are passed by reference
    player->getPlayerPos(tempPos);

    for (int i = 0; i < game->getBoardSizeY(); i++)
    {
        for (int j = 0; j < game->getBoardSizeX(); j++)
        {
            // Prints the static border in the draw area
            if (i == 0 || i == (game->getBoardSizeY() - 1))
            {
                MacUILib_printf("#");
            }
            else if (j == 0 || j == (game->getBoardSizeX() - 1))
            {
                MacUILib_printf("#");
            }
            else if (j == tempPos.x && i == tempPos.y) // Prints the character symbol at the current player position
            {
                MacUILib_printf("%c", tempPos.symbol);
            }
            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();

    MacUILib_uninit();
}
