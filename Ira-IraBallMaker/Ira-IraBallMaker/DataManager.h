#pragma once
//CSVを読み込んで、データ通りにオブジェクトを配置させる

//管理用CSVを読み込んで、ステージ数、スクリーンショット、説明をSelectUIに表示
//ステージデータCSVを読み込んで、ObjectやBall、Goalを配置
//

#include<Siv3D.hpp>
#include"IObject.h"
#include "Goal.h"
#include "EditGUI.h"

class DataManager {

public:

	CSVData csvdata;

	ObjectManager* objectmanagerptr;
	Goal* goalptr;
	EditGUI* editguiptr;


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
	void stagesave()
	{
		//ファイル名関係をいじる

		//スクリーンショットをとるStagesData/Stage01/ScreenShot.png
		String screenshotpath = U"StagesData/" + editguiptr->stagename.text + U"/ScreenShot.png";

		ScreenCapture::SaveCurrentFrame(screenshotpath);



		//管理用ファイル "StagesData/StageData.csv
		csvdata.load(U"StagesData/StagesData.csv");
		csvdata.write(U"ステージ名（パス）",U"スクリーンショット（パス）",U"クリア状況",U"クリアタイム");
		csvdata.newLine();
		csvdata.write(editguiptr->stagename,screenshotpath);
		

		editguiptr->saving = false;

		//新データ用一時ファイル


		//Block保存 "StagesData/Stage01/BlockData.csv"
		csvdata.load(U"StagesData/Stage01/BlockData.csv");
		csvdata.write(U"x座標", L"y座標", L"幅", L"高さ", L"rad", L"radplus", L"vx", L"vy");//8項目)
		csvdata.newLine();

		//要素の記録
		if (!objectmanagerptr->blocks.empty()) 
		{
			for (auto&& block : objectmanagerptr->blocks) 
			{
				csvdata.write(block->block.pos.x);
				csvdata.write(block->block.pos.y);
				csvdata.write(block->block.h);
				csvdata.write(block->block.w);
				csvdata.write(block->rad);
				csvdata.write(block->radplus);
				csvdata.write(block->vx);
				csvdata.write(block->vy);
				csvdata.newLine();
			}
		}
		else csvdata.write(U"None");

		//Line
		//csvdata.load(U"LineData.csv");
		
		//Goalとスタート等 "StagesData/Stage01/Utility.csv"

		csvdata.load(U"StagesData/Stage01/Utility.csv");
		csvdata.write(U"Start.x",U"Start.y",U"Goal.x",U"Goal,y");
		csvdata.newLine();
		
		//要素の記録
		csvdata.write(goalptr->startpos.x, goalptr->startpos.y, goalptr->goalrect.pos.x, goalptr->goalrect.pos.y);
		csvdata.newLine();
		//


		//クローズしなくていいの？

		//新しいファイルを作成して移す
		//
		//FileSystem::Copy(U"NewSavedata.csv", U"savedata_copy.csv", CopyOption::Overwrite_if_Exists);;
		
	}

	


};