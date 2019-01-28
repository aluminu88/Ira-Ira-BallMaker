#pragma once
#include "manager.h"


class Result : public MyApp::Scene
{
public:

	Result(const InitData& init)
		: IScene(init)
	{

	}


	void update()override
	{
		if (KeyZ.down())
		{
			changeScene(SceneName::Title);
			getData().ini_num++;
		}
	}

	void draw()const override
	{
		Window::ClientRect().draw(Palette::Blue);
		getData().font(U"RESULT", getData().ini_num).drawAt(Window::Center());
	}


};