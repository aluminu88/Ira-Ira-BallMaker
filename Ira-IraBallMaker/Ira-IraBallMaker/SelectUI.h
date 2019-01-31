/*選択画面用のUI機能*/

/*
管理用CSVから、ステージ名、サムネイル画像を読み取る
各項目にIDを振る
用意したRectに必要な情報を表示す（貼り付け）る。

Rect(ノード)は固定、データを遷移させて項目を操作しているように見せる
選択された項目のIDを共有データに格納、Game/Makingへつなぐ

*/

#pragma once
#include <Siv3D.hpp>
#include <vector>
#include <algorithm>



class SelectUI {

private:


	//文字表示用
	Font font20{ 20 };
	Font font40{ 40 };

	//ステージ名称を表示するノード
	Rect r1{ 25,15,300,80 }, r2{ 50,120,300,80 }, r3{ 50,400,300,80 }, r4{ 25,505,300,80 };
	Rect R{ 30,225,400,150 };

	Rect nodes[5] = { r1,r2,R,r3,r4 };


	//ステージサムネイル画像
	Rect preview_node{ 450,30,320,240 };
	Rect preview2_node{ 450,30,250,250 };

	//OKボタン
	Rect OK_node{ 400,500,340,90 };

	//難易度等を表示する
	Rect detail_node{ 470, 310, 300, 50 };


	//メニューを動かすためのボタン
	Triangle up_button{ 200,5,230,45,170,45 }, down_button{ 200,595,170,555,230,555 };


	//貼り付ける情報を受け取る場所



	//各項目を格納する構造体
	struct SelectNodeData 
	{
	public :

		int ID;
		String stagename;
		Texture thumbnail;
		String clearstate;
		int cleartime;

		SelectNodeData(int _ID, String _stagename, Texture _thumbnail,String _clearstate,int _cleartime):
			ID(_ID),
			stagename(_stagename),
			thumbnail(_thumbnail),
			clearstate(_clearstate),
			cleartime(_cleartime)
		{}	

		SelectNodeData(int _ID, String _stagename, Texture _thumbnail) :
			ID(_ID),
			stagename(_stagename),
			thumbnail(_thumbnail)
		{}

	};



	Texture DummyTexture{ U"screenshot/Dummy.png" };

	//各項目を格納している配列
	std::vector<SelectNodeData> stagenodedata;

	CSVData readcsv;
	

	//情報のセットのための関数

	enum class selectmode {
		Maiking,
		Game,
		Sending
	};
	
	selectmode mode;

	void set_selectUI()
	{
		//管理用CSVを呼んでファイル数だけ(for)回し、画像、名前を取り出しつつIDを振る(Makingなら最後に新規作成項目を付ける)

		readcsv.load(U"StagesData/StagesData.csv");


		for (int i = 1; i < (int)readcsv.rows(); i++) //0行目以外の要素数だけ回す
		{
			//項目一つずつにIDを振りながら、スクリーンショットをテクスチャ変換しつつノードのデータとして格納する
			stagenodedata.emplace_back(i, readcsv.get<String>(i, 0), Texture{ readcsv.get<String>(i,1) },readcsv.get<String>(i,2),readcsv.get<int>(i,3));

		}

		if (mode == selectmode::Maiking)stagenodedata.emplace_back(5, U"新規作成", DummyTexture,U"No", 9999);



		//テスト用
		/*stagenodedata.emplace_back(1, U"テスト1", DummyTexture);
		stagenodedata.emplace_back(2, U"テスト2", DummyTexture);
		stagenodedata.emplace_back(3, U"テスト3", DummyTexture);
		stagenodedata.emplace_back(4, U"テスト4", DummyTexture);
		stagenodedata.emplace_back(5, U"テスト5", DummyTexture);
		stagenodedata.emplace_back(6, U"テスト6", DummyTexture);
		stagenodedata.emplace_back(7, U"テスト7", DummyTexture);
		stagenodedata.emplace_back(8, U"テスト8", DummyTexture);
		stagenodedata.emplace_back(9, U"テスト9", DummyTexture);
		stagenodedata.emplace_back(10, U"テスト10", DummyTexture);*/





	}



public:

	//シーン遷移用の関数をもらい受ける
	std::function<void(int,String)> changescene;




	//コンストラクタ
	SelectUI(int _mode)
	{
		if (_mode == 0)mode = selectmode::Game;
		else if (_mode == 1)mode = selectmode::Maiking;
		else if (_mode == 2)mode = selectmode::Sending;
		//生成時に初期化
		set_selectUI();
	}

	void draw()const
	{

		//ステージノードの表示
		for (Rect node : nodes) {

			node.draw();
		}

		//テキストの貼り付け
		auto iter = stagenodedata.begin();
		font40(iter->stagename).drawAt(nodes[2].center(), Palette::Black);
		font20((iter + 1)->stagename).drawAt(nodes[3].center(), Palette::Black);
		font20((iter + 2)->stagename).drawAt(nodes[4].center(), Palette::Black);
		iter = stagenodedata.end();
		font20((iter - 2)->stagename).drawAt(nodes[0].center(), Palette::Black);
		font20((iter - 1)->stagename).drawAt(nodes[1].center(), Palette::Black);

		//サムネイルノードの表示・貼り付け

		preview_node(stagenodedata.begin()->thumbnail(0, 0, 800, 600)).draw().drawFrame(1, Palette::Aqua);

		//
		String detailtext;

		//詳細ノードの表示
		if (stagenodedata.begin()->clearstate == U"Yes") detailtext = U"Cleard!!";
		else detailtext = U"NO Clear";
		

		detail_node.draw();

		if(stagenodedata.begin()->cleartime != 9999)font20(detailtext, U"　　　Time:", stagenodedata.begin()->cleartime, U"秒").drawAt(detail_node.center(),Palette::Black);
		else font20(detailtext, U"　　　Time:", U"---秒").drawAt(detail_node.center(), Palette::Black);


		//OKノードの表示

		if (OK_node.mouseOver()) {

			if (OK_node.leftClicked()) {
				OK_node.draw(Palette::Mistyrose);
			}
			else {
				OK_node.draw(Palette::Red).drawFrame(0, 3, Palette::Mistyrose);
				font40(U"OK").drawAt(OK_node.center());
			}

		}
		else { OK_node.draw(Palette::Red); font40(U"OK").drawAt(OK_node.center()); }


		//


		//ボタンノードの表示


		if (up_button.mouseOver()) {

			if (up_button.leftClicked()) {
				up_button.draw(Palette::Lightgreen);
			}
			else { up_button.draw(Palette::Green).drawFrame(0, 3, Palette::Lightgreen); }

		}
		else { up_button.draw(Palette::Green); }


		if (down_button.mouseOver()) {

			if (down_button.leftClicked()) {
				down_button.draw(Palette::Lightgreen);
			}
			else { down_button.draw(Palette::Green).drawFrame(0, 3, Palette::Lightgreen); }

		}
		else { down_button.draw(Palette::Green); }

		//


	}


	void update()
	{

		//ボタンに対する処理

		if (KeyUp.down() || up_button.leftClicked()) {

			auto iter = stagenodedata.end() - 1;			
			for (size_t i = 1; i < stagenodedata.size(); i++) {
				std::swap(*iter, *(iter - 1));
				iter--;
			}


		}


		if (KeyDown.down() || down_button.leftClicked()) {

			auto iter = stagenodedata.begin();
			for (size_t i = 1; i < stagenodedata.size(); i++) {
				std::swap(*iter, *(iter + 1));
				iter++;

			}
		}


		//


		if (OK_node.leftClicked()) {

			//受け取った遷移関数に選択されたIDを乗せる
			changescene(stagenodedata.begin()->ID, stagenodedata.begin()->stagename);//stagenodedata.begin()->stagename

		}




	}





};