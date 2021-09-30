#pragma once
#include "MarioGame.h"


//Full screen or not
#define FULLSCREENMODE FALSE

//Screen resolution
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//frame rate 
#define FRAME_RATE 60



//The entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

    const char* port = "Mario";
    size_t size = strlen(port) + 1;
    wchar_t* portName = new wchar_t[size];

    size_t outSize;
    mbstowcs_s(&outSize, portName, size, port, size - 1);
	MarioGame game(hInstance, portName, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREENMODE, FRAME_RATE);
	game.RunGame();
	game.Release();
}