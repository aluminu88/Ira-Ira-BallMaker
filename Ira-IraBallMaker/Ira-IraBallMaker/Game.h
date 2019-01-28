#pragma once

/**/




#include "manager.h"


class Game : public MyApp::Scene
{
public:

	//CSVData csver;

	bool win=false;
	bool lose = false;
	bool pause = false;

	Ball_kun ballkun{ {250,250} };

	//空のオブジェクトマネージャーを宣言
	ObjectManager objectmanager = {};

	Game(const InitData& init)
		: IScene(init)
	{
		Window::Resize(800, 600);
		
		//stagedataに合わせてデータの読み取り
		



		//テスト用(ブロックの配置)
		objectmanager.add(std::make_shared<Block>(RectF(30, 30, 40, 100), 0, 0, 0, 0,&ballkun));
		objectmanager.add(std::make_shared<Block>(RectF(130, 30, 40, 100), Math::Pi / 4, 0, 0, 0, &ballkun));
		objectmanager.add(std::make_shared<Block>(RectF(30, 130, 40, 100), 0, Math::Pi / 4, 0, 0, &ballkun));
		objectmanager.add(std::make_shared<Block>(RectF(30, 30, 40, 100), 0, 0, 10, 0, &ballkun));
		objectmanager.add(std::make_shared<Block>(RectF(100, 100, 40, 100), 0, 0, 0, 5, &ballkun));
		//objectmanager.add(std::make_shared<Block>(RectF(150, 150, 40, 100), 0, 0, 5, 5, &ballkun));


		//ballkunの位置をデータ通りに修正


		//ゴールの位置をデータ通りに修正
		


	}


	void update()override
	{

		//戻る
		if (Key0.down())changeScene(SceneName::Select);

		//if(win) ballkun.


		//成功/失敗用ポーズ
		if (win || lose) {

			if (win)ballkun.facechange("WIN");
			if(lose)ballkun.facechange("LOSE");

			if (MouseL.down())changeScene(SceneName::Game);//もう一回
			if (MouseR.down())changeScene(SceneName::Select);//戻る
			return;
		}		

		

		//ポーズ(成功/失敗ポーズの後におく。)
		if (pause) {
			if (KeyP.down())pause = false;
			if (MouseR.down())changeScene(SceneName::Select);//戻る
			return;
		}

		//ポーズならば解ける
		if (!pause && KeyP.down() && lose == false && win == false)pause = true;



		ballkun.update();
		//編集画面から出たらまけ

		lose = objectmanager.update();

		if (!Rect(0,0,800, 600).intersects(ballkun.ballbody))lose = true;

		if (KeyZ.down())
		{
			changeScene(SceneName::Result);
		}
	}

	void draw()const override
	{
		
		Window::ClientRect().draw(Palette::Black);

		if(pause) getData().font(U"ポーズ\n\nやり直す:左クリック\n戻る：右クリック").drawAt(Window::Center());
		else if(win)  getData().font(U"ステージクリア！！\n\nもう一回:左クリック\n戻る:右クリック").drawAt(Window::Center());
		else if (lose) {
			if(!Rect(0,0,800,600).intersects(ballkun.ballbody)) getData().font(U"コースアウト…\n\nもう一回:左クリック\n戻る:右クリック").drawAt(Window::Center());
			else getData().font(U"クリア失敗…\n\nもう一回:左クリック\n戻る:右クリック").drawAt(Window::Center());
		}
		objectmanager.draw();
		ballkun.draw();
	}


};