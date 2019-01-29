
# include <Siv3D.hpp> // OpenSiv3D v0.3.1
#include "manager.h"
#include "Title.h"
#include "Select.h"
#include "Game.h"
#include "Making.h"
#include "Result.h"

void Main()
{
	const Font font(30);

	MyApp scenemanager;

	scenemanager.add<Title>(SceneName::Title);
	scenemanager.add<Select>(SceneName::Select);
	scenemanager.add<Game>(SceneName::Game);
	scenemanager.add<Making>(SceneName::Making);
	scenemanager.add<Result>(SceneName::Result);

	Window::Resize(800, 600);


	


	while (System::Update())
	{
		if (!scenemanager.update())
		{
			break;
		}
	}
}
