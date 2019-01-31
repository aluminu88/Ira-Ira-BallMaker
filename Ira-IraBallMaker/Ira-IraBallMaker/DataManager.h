#pragma once
//CSVを読み込んで、データ通りにオブジェクトを配置させる

//管理用CSVを読み込んで、ステージ数、スクリーンショット、説明をSelectUIに表示
//ステージデータCSVを読み込んで、ObjectやBall、Goalを配置
//

#include<Siv3D.hpp>
#include"IObject.h"
#include "Goal.h"
#include "EditGUI.h"
#include "Ball_Kun.h"

class DataManager {

public:

	CSVData csvdata;

	ObjectManager* objectmanagerptr;
	Goal* goalptr;
	EditGUI* editguiptr;

	struct StagesDataList
	{
	public:

		int ID;
		String stagename;
		String screenpath;
		String clearstate;
		int time;

		StagesDataList(int _ID, String _stagename, String _screenpath,String _clearstate,int _time) :
			ID(_ID),
			stagename(_stagename),
			screenpath(_screenpath),
			clearstate(_clearstate),
			time(_time)
		{}

	};

	std::vector<StagesDataList> stagesdatalist;


	DataManager(ObjectManager* _optr,Goal* _gptr):
		objectmanagerptr(_optr),
		goalptr(_gptr)
	{

	}

	void setEditGUptr(EditGUI* _eptr) 
	{
		editguiptr = _eptr;
	}

	

	//GUIのステージ保存時に呼ばれる
	void stagesave(int ID)
	{
		

		//フォルダパスの準備(設定したステージ名を読み取ってファイルパスを作る)

		String directoryname = U"StagesData/" + editguiptr->stagename.text;

		String screenshotpath = U"StagesData/" + editguiptr->stagename.text + U"/ScreenShot.png";

		//スクリーンショットをとるStagesData/Stage01/ScreenShot.png
		ScreenCapture::SaveCurrentFrame(screenshotpath);



		stagesdatalist = {};

		//管理用ファイル "StagesData/StageData.csv

		//割り振られたIDの行に記述するんだと思う→そうはいかないので全部書き直し

		//前の内容をコピー

		//既存ファイルを一時的に開き、要素を格納する
		csvdata.load(U"StagesData/StagesData.csv");
		for (size_t i = 1; i < csvdata.rows() ; i++) 
		{
			stagesdatalist.emplace_back(i, csvdata.get<String>(i, 0), csvdata.get<String>(i, 1), csvdata.get<String>(i, 2), csvdata.get<int>(i, 3));
		}


		if (ID == (int)csvdata.rows()) {
			//新規作成時に上書きできるように保持
			stagesdatalist.emplace_back(csvdata.rows(), U"新規作成", U"None", U"None", 9999);

		}

		//保存したStageDataListの中でデータの置き換え作業
		
		for (auto&& data : stagesdatalist) 
		{
			if(data.ID == ID)data = StagesDataList(ID, editguiptr->stagename.text, screenshotpath,U"No",9999);//編集保存はクリア情報を一新

			
		}

		//stagesdatalist[ID] = StagesDataList(ID, editguiptr->stagename.text, screenshotpath);
		
		//置き換えたら入れ直す

		csvdata.load(U"StagesData/NewStagesData.csv");
		csvdata.write(U"ステージ名", U"スクリーンショット（パス）", U"クリア状況", U"クリアタイム");
		csvdata.newLine();
		
		for (auto&& data : stagesdatalist) 
		{
			csvdata.write(data.stagename, data.screenpath, data.clearstate, data.time);
			csvdata.newLine();
		}
		

		csvdata.save(U"StagesData/NewStagesData.csv");

		//新しく作り直したファイルを本データにコピーさせる
		FileSystem::Copy(U"StagesData/NewStagesData.csv", U"StagesData/StagesData.csv", CopyOption::Overwrite_if_Exists);

		//一時ファイルは削除する
		FileSystem::Remove(U"StagesData/NewStagesData.csv");

		csvdata.clear();

		//クリアデータ

		//csvdata.load(directoryname + U"/ClearData.csv");
		//csvdata.save(directoryname + U"/ClearData.csv");

		//csvdata.load(directoryname + U"/NewClearData.csv");
		//csvdata.write(U"クリア状況", U"クリアタイム");
		//csvdata.newLine();
		//csvdata.write(U"No", U"9999");//新規保存はクリアデータを初期化
		//csvdata.save(directoryname + U"NewClearData.csv");

		//新しく作り直したファイルを本データにコピーさせる
		//FileSystem::Copy(directoryname + U"/NewClearData.csv", directoryname + U"/ClearData.csv", CopyOption::Overwrite_if_Exists);

		//一時ファイルは削除する
		//FileSystem::Remove(directoryname + U"/NewClearData.csv");
		
		//

		//Block保存 "StagesData/Stage01/BlockData.csv"
		

		csvdata.load(directoryname + U"/BlockData.csv");
		csvdata.save(directoryname + U"/BlockData.csv");
		csvdata.clear();

		csvdata.load(directoryname + U"/NewBlockData.csv");
		csvdata.write(U"x座標", U"y座標", U"幅", U"高さ", U"rad", U"radpUus", U"vx", U"vy");//8項目)
		csvdata.newLine();

		//要素の記録
		if (!objectmanagerptr->blocks.empty()) 
		{
			for (auto&& block : objectmanagerptr->blocks) 
			{
				csvdata.write(block->block.pos.x);
				csvdata.write(block->block.pos.y);
				csvdata.write((int)block->block.w);
				csvdata.write((int)block->block.h);
				csvdata.write(block->rad);
				csvdata.write(block->radplus);
				csvdata.write((int)block->vx);
				csvdata.write((int)block->vy);
				csvdata.newLine();
			}
		}
		else csvdata.write(U"None");

		csvdata.save(directoryname + U"/NewBlockData.csv");
		
		//新しく作り直したファイルを本データにコピーさせる
		FileSystem::Copy(directoryname + U"/NewBlockData.csv", directoryname + U"/BlockData.csv", CopyOption::Overwrite_if_Exists);

		//一時ファイルは削除する
		FileSystem::Remove(directoryname + U"/NewBlockData.csv");

		csvdata.clear();
		
		
		//Line
		//csvdata.load(U"LineData.csv");
		
		//Goalとスタート等 "StagesData/Stage01/Utility.csv"
		//csvdata.load(directoryname + U"/UtilityData.csv");
		//csvdata.save(directoryname + U"/UtilityData.csv");
		//csvdata.clear();

		csvdata.load(directoryname + U"/NewUtilityData.csv");

		

		csvdata.write(U"Start.x",U"Start.y",U"Goal.x",U"Goal,y");
		csvdata.newLine();
		
		//要素の記録
		csvdata.write(goalptr->startpos.x, goalptr->startpos.y, goalptr->goalrect.pos.x, goalptr->goalrect.pos.y);
		csvdata.newLine();
		//

		csvdata.save(directoryname + U"/UtilityData.csv");

		//新しく作り直したファイルを本データにコピーさせる
		FileSystem::Copy(directoryname + U"/NewUtilityData.csv", directoryname + U"/UtilityData.csv", CopyOption::Overwrite_if_Exists);

		//一時ファイルは削除する
		FileSystem::Remove(directoryname+ U"/NewUtilityData.csv");
		
		csvdata.clear();

		editguiptr->saving = false;

		//クローズではなく、.save()がその役目をしているらしい
		
	}

	void stageread(String stagename,Ball_kun& ballkun,int option) 
	{
		if (stagename == U"新規作成") return;
	
		//ゴールやスタート地点

		csvdata.load(U"StagesData/" + stagename + U"/UtilityData.csv");

		goalptr->startpos = Vec2(csvdata.get<double>(1, 0), csvdata.get<double>(1, 1));
		goalptr->goalrect.pos = Vec2(csvdata.get<double>(1,2),csvdata.get<double>(1,3));

		//Block

		csvdata.load(U"StagesData/" + stagename + U"/BlockData.csv");

		//Blockの初期化
		objectmanagerptr->blocks = {};
		
		//
		if (csvdata.get<String>(1, 1) != U"None") {

			for (size_t i = 1; i < csvdata.rows(); i++)
			{
				objectmanagerptr->blockadd(std::make_shared<Block>(RectF(Vec2(csvdata.get<double>(i, 0), csvdata.get<double>(i, 1)), csvdata.get<int>(i, 2), csvdata.get<int>(i, 3)), csvdata.get<double>(i, 4), csvdata.get<double>(i, 5), csvdata.get<int>(i, 6), csvdata.get<int>(i, 7), &ballkun, option));
			}

		}


	}

	bool cleardata(int ID,String filepath,int time) 
	{
		stagesdatalist = {};
		bool newrecord = false;

		//管理用ファイル "StagesData/StageData.csv

		//割り振られたIDの行に記述するんだと思う→そうはいかないので全部書き直し

		//前の内容をコピー

		//既存ファイルを一時的に開き、要素を格納する
		csvdata.load(U"StagesData/StagesData.csv");
		for (size_t i = 1; i < csvdata.rows(); i++)
		{
			stagesdatalist.emplace_back(i, csvdata.get<String>(i, 0), csvdata.get<String>(i, 1), csvdata.get<String>(i, 2), csvdata.get<int>(i, 3));
		}



		//保存したStageDataListの中で対応するIDにデータの置き換え作業

		for (auto&& data : stagesdatalist)
		{
			if (data.ID == ID)
			{
				if (data.time > time) {
					data = StagesDataList(ID, filepath, U"StagesData/" + filepath + U"/ScreenShot.png", U"Yes", time);
					newrecord = true;
				}
			}
		}

		//stagesdatalist[ID] = StagesDataList(ID, editguiptr->stagename.text, screenshotpath);

		//置き換えたら入れ直す

		csvdata.load(U"StagesData/NewStagesData.csv");
		csvdata.write(U"ステージ名", U"スクリーンショット（パス）", U"クリア状況", U"クリアタイム");
		csvdata.newLine();

		for (auto&& data : stagesdatalist)
		{
			csvdata.write(data.stagename, data.screenpath, data.clearstate, data.time);
			csvdata.newLine();
		}


		csvdata.save(U"StagesData/NewStagesData.csv");

		//新しく作り直したファイルを本データにコピーさせる
		FileSystem::Copy(U"StagesData/NewStagesData.csv", U"StagesData/StagesData.csv", CopyOption::Overwrite_if_Exists);

		//一時ファイルは削除する
		FileSystem::Remove(U"StagesData/NewStagesData.csv");

		csvdata.clear();

		return newrecord;
		
	}


};