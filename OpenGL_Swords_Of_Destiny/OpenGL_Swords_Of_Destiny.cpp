#include "pch.h"
#include "Engine/Engine.hpp"

#include "FontMeshCreator/MetaFile.hpp"

int main()
{
	// Check if there is memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	/*Engine engine;

	engine.Run();*/
	MetaFile mf("../Fonts/vivaldi.fnt");

	return 0;
}