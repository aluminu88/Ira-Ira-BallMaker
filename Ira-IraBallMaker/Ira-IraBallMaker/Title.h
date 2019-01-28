#pragma once
#include "manager.h"
#include "TitleMenuTool.h"

class Title : public MyApp::Scene
{

public:

	TitleMenuTool titlemenutool{ 3 };


	Title(const InitData& init)
		: IScene(init)
	{
		

		getData().ini_num = 0;
		//getData().ini_num = 0;

		titlemenutool.titlesentence = U"いらいらボールメーカー";
		titlemenutool.items.push_back( U"ステージで遊ぶ");
		titlemenutool.items.push_back( U"ステージを作る");
		titlemenutool.items.push_back( U"ステージを送る");

	}



	void update()override
	{

		titlemenutool.update();

		if (MouseL.up())
			
		{
			getData().mode = titlemenutool.num;
			//getData().mode = 0;//Game
			//getData().mode = 1;//Making
			changeScene(SceneName::Select);
			
		}
	}

	void draw()const override
	{
		Window::ClientRect().draw(Palette::Black);
		getData().font(U"TITLE", getData().ini_num).drawAt(Window::Center());

		titlemenutool.draw();


	}


};