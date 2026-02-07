
#include <iostream>
#include "UnrealityEngine.h"

#include "XenonLevel.h"


int main()
{
	int value;
	int windowWidth, windowHeight;

	windowWidth = 1920;
	windowHeight = 1080;


	UnrealityEngine Engine;

	Engine.Initialize("Xenon Clone", windowWidth, windowHeight);

	XenonLevel* level = new XenonLevel(Engine.GetRenderer(), windowWidth, windowHeight);

	Engine.SetCurrentLevel(level);

	Engine.StartGame();

}
