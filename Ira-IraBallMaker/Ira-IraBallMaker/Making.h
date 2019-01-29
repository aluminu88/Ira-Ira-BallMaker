#pragma once
#include "manager.h"
#include "EditGUI.h"


class Making : public MyApp::Scene
{
public:

	//CSVData csver;

	bool pause = false;

	//ボール
	Ball_kun ballkun{ {250,250} };
	
	//ゴール
	Goal goal{ &ballkun , Vec2(400,400) };

	//空のオブジェクトマネージャーを宣言
	ObjectManager objectmanager = {} ;

	//EditGUIがボールとオブジェクトをもつ
	EditGUI editgui{ &ballkun,&objectmanager ,&goal };


	DataManager datamanager{ &objectmanager, &goal };


	Making(const InitData& init)
		: IScene(init)
	{
		Window::Resize(1200, 700);

		//stagedataに合わせてデータの読み取り
		//ObjectManagerの配列にObjectを代入

		datamanager.setEditGUptr(&editgui);

		datamanager.stageread(getData().filepath, ballkun);


		//テスト用
		//objectmanager.add(std::make_shared<Block>(RectF(30, 30, 40, 100), 0, 0, 0, 0, &ballkun));
		//objectmanager.add(std::make_shared<Block>(RectF(130, 30, 40, 100), Math::Pi / 4, 0, 0, 0, &ballkun));
		//objectmanager.add(std::make_shared<Block>(RectF(30, 130, 40, 100), 0, Math::Pi / 4, 0, 0, &ballkun));
		//objectmanager.add(std::make_shared<Block>(RectF(30, 30, 40, 100), 0, 0, 10, 0, &ballkun));
		//objectmanager.add(std::make_shared<Block>(RectF(100, 100, 40, 100), 0, 0, 0, 5, &ballkun));
		//objectmanager.add(std::make_shared<Block>(RectF(150, 150, 40, 100), 0, 0, 5, 5, &ballkun));


		//ballkunの位置をデータ通りに修正

		//goalの位置をデータ通りに修正


	}


	void update()override
	{

		//エディタはポーズ中でも使用可能
		editgui.update();
		if (editgui.saving) 
		{
			datamanager.stagesave(getData().stagenum);
		}

		//戻る
		if (Key0.down())changeScene(SceneName::Select);

	
		//ポーズ(解く)
		if (pause) {
			if (KeyP.down())pause = false;
			if (MouseR.down())changeScene(SceneName::Select);//戻る
			return;
		}

		//ポーズする
		if (!pause && KeyP.down())pause = true;


		//ボールの位置（顔）更新
		ballkun.update();


		//編集画面から出たら復帰する
		if (!Rect(0, 0, 800, 600).intersects(ballkun.ballbody))ballkun.reset();

		//ゴールやオブジェクトと触れたからと言って特に何もしない
		
		goal.update();
		objectmanager.update();

		if (KeyZ.down())
		{
			changeScene(SceneName::Title);
		}





	}

	void draw()const override
	{

		Window::ClientRect().draw(Palette::Black);

		
		//ゴールはオブジェクトに隠れ、ボールが最前線
		editgui.drawstart();

		goal.draw();
		objectmanager.draw();
		ballkun.draw();


		/*前線群*/

		//編集画面の枠組み
		Rect(800, 0, 400, 700).draw(Palette::Gray);
		Rect(0, 600, 1200, 100).draw(Palette::Gray);

		//出力部
		if (pause) getData().font(U"ポーズ\n戻る：右クリック").drawAt(0, 600, Palette::Black);

		//GUI(最前線)
		editgui.draw();

	}


};