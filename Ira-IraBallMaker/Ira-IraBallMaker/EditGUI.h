#pragma once
#include<Siv3D.hpp>
#include "Iobject.h"

class EditGUI{ 

public :
	
	mutable TextEditState stagename{ U"ステージ名" };

	mutable double s0 = 0.3, s1 = 0.4, s2 = 0.5, s3 = 0.6, s4 = 0.7, s5 = 0.8;

	mutable double block_w = 0.0, block_h = 0.0, block_r=0.0,block_rp=0.0,block_vx=0.0,block_vy=0.0;

	mutable bool c_vx = true, c_vy = false, c2 = true, c3 = false;

	Font datafont{ 20 }, itemfont{15};

	RectF  stampRect;

	RectF BlockGUIBox = RectF(800, 250, 400, 450);

	RectF BlockGUIheader = RectF(800, 250, 400, 30);

	bool BlockGUIgrabbed = false;

	ObjectManager* objectmanagerptr;
	Ball_kun* ballkunptr;

	//禁断の呪法

	EditGUI(Ball_kun* _ballkunptr,ObjectManager* _objectmanagerptr) :
		objectmanagerptr(_objectmanagerptr),
		ballkunptr(_ballkunptr)
	{}
	
	//カーソル自動追従,持ち運ぶ、見えなくする

	const Array<String> blockaddoptions =
	{
		U"Cursor", U"Bring",U"Invisible"
	};

	const Array<String> editoptions =
	{
		U"Edit", U"Add"
	};

	const Array<String> objectoptions =
	{

		U"None",U"Block",U"Line"
	};
	
	mutable size_t blockaddIndex=0, editoraddIndex=0,objectIndex=0;




	void set_BlockGUI() 
	{

	}

	void edithighlight() 
	{
		
	}

	void update() 
	{
		
		//


		//Block用の項目

		if (BlockGUIheader.leftClicked()) {
			BlockGUIgrabbed = true;
		}
		else if (MouseL.up()) {
			BlockGUIgrabbed = false;
		}
		else if (BlockGUIgrabbed) {
			BlockGUIBox.pos += Cursor::DeltaF();
			BlockGUIheader.pos = BlockGUIBox.pos;
		}

		stampRect = RectF(Cursor::Pos(),block_w, block_h);

		

		//Block編集機能

		if (objectoptions[objectIndex] == U"Block") 
		{

			//左クリックで選択？


			//マウス右クリックで追加
			if (editoptions[editoraddIndex] == U"Add")
			{

				if (MouseR.down() && stampRect.w > 0 && stampRect.w > 0)
				{
					objectmanagerptr->add(std::make_shared<Block>(RectF(stampRect), block_r, block_rp, block_vx, block_vy, ballkunptr));
				}
			}
			//選択した図形の情報をハイライト、編集可能
			else if (editoptions[editoraddIndex] == U"Edit")
			{
				std::shared_ptr<Block> a;
				if (!objectmanagerptr->selectedObject == NULL) {
					
					//Blockとして扱うために代入
					a = objectmanagerptr->selectedObject;

					block_w = a->block.w;
					block_h = a->block.h;
					block_r = a->rad;
					block_rp = a->radplus;
					block_vx = a->vx;
					block_vy = a->vy;

					

				}

			}

		}

	}

	

	void BlockGUIsystem()const 
	{

		if ((int)block_vx == 0)c_vy = true;
		else c_vy= false;
		if ((int)block_vy == 0)c_vx = true;
		else c_vx = false;


		if (blockaddoptions[blockaddIndex] == U"Cursor")
		{
			//RectF(Vec2(Cursor::Pos()), block_w, block_h).rotated(block_r).draw(Palette::Aqua);
			stampRect.draw(Palette::Aqua);

		}
		else if (blockaddoptions[blockaddIndex] == U"Bring")
		{

		}

		//スライダー
		itemfont(U"width:").draw(BlockGUIBox.pos + Vec2(2, 40), Palette::Black);
		if (SimpleGUI::Button(U"-", BlockGUIBox.pos + Vec2(65, 40), 20))
		{
			block_w--;
		}
		SimpleGUI::Slider(block_w, 0, 500, BlockGUIBox.pos + Vec2(90, 40), 200);//幅
		if (SimpleGUI::Button(U"+", BlockGUIBox.pos + Vec2(295, 40), 20))
		{
			block_w++;
		}
		datafont((int)block_w).draw(BlockGUIBox.pos + Vec2(320, 40), Palette::Black);
		if (SimpleGUI::Button(U"0", BlockGUIBox.pos + Vec2(365, 40), 20))
		{
			block_w = 0;
		}


		itemfont(U"height:").draw(BlockGUIBox.pos + Vec2(2, 80), Palette::Black);
		if (SimpleGUI::Button(U"-", BlockGUIBox.pos + Vec2(65, 80), 20))
		{
			block_h--;
		}
		SimpleGUI::Slider(block_h, 0, 500, BlockGUIBox.pos + Vec2(90, 80), 200);//高さ
		if (SimpleGUI::Button(U"+", BlockGUIBox.pos + Vec2(295, 80), 20))
		{
			block_h++;
		}
		datafont((int)block_h).draw(BlockGUIBox.pos + Vec2(320, 80), Palette::Black);
		if (SimpleGUI::Button(U"0", BlockGUIBox.pos + Vec2(365, 80), 20))
		{
			block_h = 0;
		}


		itemfont(U"rad:").draw(BlockGUIBox.pos + Vec2(2, 120), Palette::Black);
		if (SimpleGUI::Button(U"-", BlockGUIBox.pos + Vec2(65, 120), 20))
		{
			block_r--;
		}
		SimpleGUI::Slider(block_r, -360, 360, BlockGUIBox.pos + Vec2(90, 120), 200);//角度
		if (SimpleGUI::Button(U"+", BlockGUIBox.pos + Vec2(295, 120), 20))
		{
			block_r++;
		}
		datafont((int)block_r).draw(BlockGUIBox.pos + Vec2(320, 120), Palette::Black);
		if (SimpleGUI::Button(U"0", BlockGUIBox.pos + Vec2(365, 120), 20))
		{
			block_r = 0;
		}

		itemfont(U"radplus:").draw(BlockGUIBox.pos + Vec2(2, 160), Palette::Black);
		if (SimpleGUI::Button(U"-", BlockGUIBox.pos + Vec2(65, 160), 20))
		{
			block_rp--;
		}
		SimpleGUI::Slider(block_rp, -360_deg, 360_deg, BlockGUIBox.pos + Vec2(90, 160), 200);//角速度
		if (SimpleGUI::Button(U"+", BlockGUIBox.pos + Vec2(295, 160), 20))
		{
			block_rp++;
		}
		datafont((int)block_rp).draw(BlockGUIBox.pos + Vec2(320, 160), Palette::Black);
		if (SimpleGUI::Button(U"0", BlockGUIBox.pos + Vec2(365, 160), 20))
		{
			block_rp = 0;
		}


		itemfont(U"vx:").draw(BlockGUIBox.pos + Vec2(2, 200), Palette::Black);
		if (SimpleGUI::Button(U"-", BlockGUIBox.pos + Vec2(65, 200), 20,c_vx))
		{
			block_vx--;
		}
		SimpleGUI::Slider(block_vx, -10, 10, BlockGUIBox.pos + Vec2(90, 200), 200, c_vx);//x速度
		if (SimpleGUI::Button(U"+", BlockGUIBox.pos + Vec2(295, 200), 20))
		{
			block_vx++;
		}
		datafont((int)block_vx).draw(BlockGUIBox.pos + Vec2(320, 200), Palette::Black);
		if (SimpleGUI::Button(U"0", BlockGUIBox.pos + Vec2(365, 200), 20, c_vx))
		{
			block_vx = 0;
		}

		itemfont(U"vy:").draw(BlockGUIBox.pos + Vec2(2, 240), Palette::Black);
		if (SimpleGUI::Button(U"-", BlockGUIBox.pos + Vec2(65, 240), 20,c_vy))
		{
			block_vy--;
		}
		SimpleGUI::Slider(block_vy, -10, 10, BlockGUIBox.pos + Vec2(90, 240), 200, c_vy);//x速度
		if (SimpleGUI::Button(U"+", BlockGUIBox.pos + Vec2(295, 240), 20,c_vy))
		{
			block_vy++;
		}
		datafont((int)block_vy).draw(BlockGUIBox.pos + Vec2(320, 240), Palette::Black);
		if (SimpleGUI::Button(U"0", BlockGUIBox.pos + Vec2(365, 240), 20,c_vy))
		{
			block_vy = 0;
		}

		itemfont(U"addoption:").draw(BlockGUIBox.pos + Vec2(2, 285),Palette::Black);
		SimpleGUI::RadioButtons(blockaddIndex, blockaddoptions, BlockGUIBox.pos + Vec2(0, 310));

	};

	void CommonGUIsystem()const
	{
		itemfont(U"StageName:").draw(802, 15, Palette::Black);
		//ステージ名入力用
		SimpleGUI::TextBox(stagename, Vec2(890, 10), 200, 10);



		//保存ボタン
		if (SimpleGUI::Button(U"保存", Vec2(1110, 10), 50))
		{
			//ファイル指定
			//スクリーンショットをとる(GUIを見えなくする？)
			//ステージ名とオブジェクトデータ,スクショの保存
		}

		itemfont(U"Edit or Add:").draw(802, 60, Palette::Black);
		SimpleGUI::RadioButtons(editoraddIndex, editoptions, Vec2(800, 90), 80);

		itemfont(U"Object:").draw(902, 60, Palette::Black);
		SimpleGUI::RadioButtons(objectIndex, objectoptions, Vec2(900, 90), 100);

	}


	void draw()const 
	{

		//共通

		CommonGUIsystem();


		//GUIの描画
		BlockGUIBox.draw(Palette::Silver);
		BlockGUIheader.draw(Palette::White);
		datafont(U"BlockGUI").drawAt(BlockGUIheader.center(),Palette::Black);


		



		//マウス座標の表示
		datafont(Cursor::Pos()).draw(800,200);

		BlockGUIsystem();



		
	}


};