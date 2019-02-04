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
	bool newrecord = false;

	//クリアタイム記録用タイマー
	Stopwatch timer;

	Font timefont{ 10 };

	//操作するボール
	Ball_kun ballkun{ {250,250} };

	//ゴール
	Goal goal{ &ballkun,Vec2(400,400) };


	//空のオブジェクトマネージャーを宣言(データ読み込みの過程で代入)
	ObjectManager objectmanager = {};


	//データ読み出し用
	DataManager datamanader {&objectmanager, &goal };

	Game(const InitData& init)
		: IScene(init)
	{
		Window::Resize(800, 600);
		
		//stagedataに合わせてデータの読み取り
		
		datamanader.stagereadV2(getData().filepath,ballkun,getData().mode);

		newrecord = false;
		
		//ゴールの位置をデータ通りに修正
		//Blockをデータ通りに配置


		//テスト用(ブロックの配置)
		//objectmanager.add(std::make_shared<Block>(RectF(30, 30, 40, 100), 0, 0, 0, 0,&ballkun));
		//objectmanager.add(std::make_shared<Block>(RectF(130, 30, 40, 100), Math::Pi / 4, 0, 0, 0, &ballkun));
		//objectmanager.add(std::make_shared<Block>(RectF(30, 130, 40, 100), 0, Math::Pi / 4, 0, 0, &ballkun));
		//objectmanager.add(std::make_shared<Block>(RectF(30, 30, 40, 100), 0, 0, 10, 0, &ballkun));
		//objectmanager.add(std::make_shared<Block>(RectF(100, 100, 40, 100), 0, 0, 0, 5, &ballkun));
		//objectmanager.add(std::make_shared<Block>(RectF(150, 150, 40, 100), 0, 0, 5, 5, &ballkun));
		
		//ballkunの位置をデータ通りに修正
		ballkun.pos = goal.startpos;
		ballkun.ballbody.setPos(goal.startpos);
		

		//タイマー開始

		if (timer.isRunning())timer.restart();
		else timer.start();
	}


	void update()override
	{

		//戻る
		if (Key0.down())changeScene(SceneName::Select);

		//if(win) ballkun.
		

		//成功/失敗用ポーズ
		if (win || lose) {

			//タイマー停止
			timer.pause();

			if (win) {
				ballkun.facechange("WIN");
				if(datamanader.cleardata(getData().stagenum,getData().filepath,timer.s()))newrecord = true;
				//タイマーのタイムを入れたりする
			}
			if(lose)ballkun.facechange("LOSE");

			if (MouseL.down())changeScene(SceneName::Game);//もう一回
			if (MouseR.down())changeScene(SceneName::Select);//戻る
			return;
		}		

		

		//ポーズ(解く)
		if (pause) {

			if (KeyP.down())
			{
				timer.start();
				pause = false;
			}
			if (MouseR.down())changeScene(SceneName::Select);//戻る
			return;
		}

		//ポーズする
		if (!pause && KeyP.down() && lose == false && win == false)
		{
			timer.pause();
			pause = true;
		}


		//ボールの位置（顔）更新
		ballkun.update();

		//ゴールに着いたら勝ち
		win = goal.update();
		
		//オブジェクトとぶつかったら負け
		lose = objectmanager.update();

		//編集画面から出たら負け
		if (!Rect(0,0,800, 600).intersects(ballkun.ballbody))lose = true;

		if (KeyZ.down())
		{
			changeScene(SceneName::Title);
		}
	}

	void draw()const override
	{
		
		Window::ClientRect().draw(Palette::Black);

		//ゴールはオブジェクトに隠れ、ボールが最前線

		goal.draw();
		objectmanager.draw();
		ballkun.draw();


		//最前線群

		//テキスト出力部
		if(pause) getData().font(U"ポーズ\n\nやり直す:左クリック\n戻る：右クリック").drawAt(Window::Center(), Palette::Aqua);
		else if (win) {
			if(newrecord)getData().font(U"ステージクリア！！\n新記録！！\n", timer.s(), U" 秒　　　\nもう一回:左クリック\n戻る:右クリック").drawAt(Window::Center(), Palette::Aqua);
			else getData().font(U"ステージクリア！！\n　　　", timer.s(), U" 秒　　　\nもう一回:左クリック\n戻る:右クリック").drawAt(Window::Center(), Palette::Aqua);
		}
		else if (lose) {
			if(!Rect(0,0,800,600).intersects(ballkun.ballbody)) getData().font(U"コースアウト…\n\nもう一回:左クリック\n戻る:右クリック").drawAt(Window::Center(),Palette::Aqua);
			else getData().font(U"クリア失敗…\n\nもう一回:左クリック\n戻る:右クリック").drawAt(Window::Center(), Palette::Aqua);
		}

		//タイマー
		timefont(timer.s()).draw();
		
	}


};