#pragma once
#include "manager.h"
#include "TitleMenuTool.h"

class Title : public MyApp::Scene
{

public:

	TitleMenuTool titlemenutool{ 3 };


	void screenshot() 
	{
		String sss = U"Stage01";
		String screenshotpath = U"StagesData/" + sss + U"/ScreenShot.png";

		//スクリーンショットをとるStagesData/Stage01/ScreenShot.png
		//ScreenCapture::SaveCurrentFrame(screenshotpath);
	
		CSVData a;
		
		a.load(U"StagesData/NewStagesData.csv");
		a.write(U"ステージ名", U"スクリーンショット（パス）", U"クリア状況", U"クリアタイム");
		a.newLine();

		a.write(U"Stage01", screenshotpath, U"No", 9999);
		a.newLine();
		a.write(U"Stage02", screenshotpath, U"No", 9999);
		a.newLine();
		a.write(U"Stage03", screenshotpath, U"No", 9999);
		a.newLine();
		a.write(U"Stage04", screenshotpath, U"No", 9999);
		a.newLine();

		a.save(U"StagesData/NewStagesData.csv");

		FileSystem::Copy(U"StagesData/NewStagesData.csv", U"StagesData/StagesData.csv", CopyOption::Overwrite_if_Exists);
		
		FileSystem::Remove(U"StagesData/NewStagesData.csv");

	}


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

		if (KeyT.down()) 
		{
			//screenshot();
		}


	}

	void draw()const override
	{
		Window::ClientRect().draw(Palette::Black);
		getData().font(U"TITLE", getData().ini_num).drawAt(Window::Center());

		titlemenutool.draw();


	}


};