#include <iostream>
#include "Engine/Engine.h"
#include "Level/SokobanLevel.h"
#include "Game/Game.h"

using namespace Wanted;


int main()
{
    const int width = 3;
    const int height = 3;
    CHAR_INFO charArray[3 * 3] = {};
    charArray[2 * width + 1].Char.AsciiChar = 'P';
    charArray[2 * width + 1].Attributes = FOREGROUND_GREEN;

    charArray[0 * width + 1].Char.AsciiChar = '#';
    charArray[0 * width + 1].Attributes = FOREGROUND_RED;

	//Wanted::Engine engine;
	//engine.SetNewLevel(new SokobanLevel());
	//engine.Run();
    
    //Game game;
    //game.Run();
    
    COORD position = {};
    COORD screenSize;
    screenSize.X = width;
    screenSize.Y = height;

    SMALL_RECT writeRegion{
	0,0,static_cast<short>(width),static_cast<short>(height)
    };
    WriteConsoleOutputA(
	GetStdHandle(STD_OUTPUT_HANDLE),
	charArray,
	screenSize,
	position,
	&writeRegion
    );

    

    std::cin.get();
} 