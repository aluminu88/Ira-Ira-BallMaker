#pragma once
#include<Siv3D.hpp>
#include "Iobject.h"
#include"Goal.h"


class EditGUI{ 

public :

	ObjectManager* objectmanagerptr;
	Ball_kun* ballkunptr;
	Goal* goalptr;

	//DataManager datamanager {objectmanagerptr,goalptr};



	/*管理用*/

	mutable TextEditState stagename{ U"ステージ名" };

	Font datafont{ 20 }, itemfont{15};

	//

	mutable bool saving = false;

	/*Goal用*/

	bool goalgrabbed = false;

	/*ボールのスタート地点*/
	Circle startcircle = Circle{Vec2(250,250),30.0};

	/*Block用*/

	//GUI用変数
	mutable double block_w = 0.0, block_h = 0.0, block_r=0.0,block_rp=0.0,block_vx=0.0,block_vy=0.0;
	mutable bool c_vx = true, c_vy = false,c_additon = false,c_editoradd = true;

	//GUI用ウィンドウ
	RectF BlockGUIBox = RectF(2000, 250, 400, 450);//{800,250}が定位置

	RectF BlockGUIheader = RectF(2000, 250, 400, 30);

	bool BlockGUIgrabbed = false;

	//図形追加用
	RectF  stampRect;
	std::shared_ptr<Block> checkBlock = 0;
	

	/*コンストラクタ*/

	EditGUI(Ball_kun* _ballkunptr,ObjectManager* _objectmanagerptr,Goal* _goalptr) :
		objectmanagerptr(_objectmanagerptr),
		ballkunptr(_ballkunptr),
		goalptr(_goalptr)
	{}
	

	/*ラジオボタン用*/

	//カーソル自動追従,持ち運ぶ、見えなくする

	const Array<String> blockaddoptions =
	{
		U"Cursor", U"Bring",U"Invisible"
	};

	mutable size_t blockaddIndex = 0;


	//図形を編集するか、図形を追加するか

	const Array<String> editoptions =
	{
		U"Edit", U"Add"
	};

	mutable size_t  editoraddIndex = 0;


	//展開するGUIウィンドウの種類

	const Array<String> objectoptions =
	{
		U"None",U"Block",U"Line"
	};
	
	mutable size_t objectIndex = 0;
	


	void update() 
	{
		
		/*None用の項目*/

		//Goal

		if (objectoptions[objectIndex] == U"None") {
			c_editoradd = false;
			BlockGUIBox.x = 2000;//表示しない

			//goalを持ち運べる
			if (goalptr->goalrect.leftClicked()) {
				goalgrabbed = true;
			}
			else if (MouseL.up()) {
				goalgrabbed = false;
			}
			else if (goalgrabbed) {
				goalptr->goalrect.pos += Cursor::DeltaF();
			}

			//画面内に完全に入っていない場合位置をリセットする
			if(!Rect(0,0,800,600).contains(goalptr->goalrect)) goalptr->goalrect.setPos(400, 400);

			//マウス右クリックでスタート地点を設定
			if (Rect(0, 0, 800, 600).intersects(Cursor::Pos()) && MouseR.down()) 
			{
				startcircle.setPos(Cursor::Pos());
				goalptr->startpos = Cursor::Pos();
			}

			

		}else c_editoradd = true;

		


		/*Block用の項目*/

		BlockGUIheader.pos = BlockGUIBox.pos;

		stampRect = RectF(Cursor::Pos(), block_w, block_h);

		//Block編集機能

		if (objectoptions[objectIndex] == U"Block")
		{

			//動かしたいならコメントアウトをとる

			/*if (BlockGUIheader.leftClicked()) {
				BlockGUIgrabbed = true;
			}
			else if (MouseL.up()) {
				BlockGUIgrabbed = false;
			}
			else if (BlockGUIgrabbed) {
				BlockGUIBox.pos += Cursor::DeltaF();
				BlockGUIheader.pos = BlockGUIBox.pos;
			}*/


			//BlockGUIを表示
			BlockGUIBox.x = 800;

			//Add機能
			if (editoptions[editoraddIndex] == U"Add")
			{
				c_additon = true;

				if (MouseR.down() && stampRect.w > 0 && stampRect.w > 0)
				{
					objectmanagerptr->add(std::make_shared<Block>(RectF(stampRect), block_r, block_rp, block_vx, block_vy, ballkunptr));
				}
			}
			//Edit機能
			else if (editoptions[editoraddIndex] == U"Edit")
			{
				//強制的にInvisibleし、addoptionを非アクティブ
				blockaddIndex = 2;
				c_additon = false;

				//選択した図形の値をハイライトし、以降GUIから変更が可能

				if (!objectmanagerptr->selectedBlock == NULL) {



					if (objectmanagerptr->selectedBlock != checkBlock) {//異なる=変更を検知
						//初回だけ入れ替えるだけにしたい

						block_w = objectmanagerptr->selectedBlock->block.w;
						block_h = objectmanagerptr->selectedBlock->block.h;
						block_r = objectmanagerptr->selectedBlock->rad;
						block_rp = objectmanagerptr->selectedBlock->radplus;
						block_vx = objectmanagerptr->selectedBlock->vx;
						block_vy = objectmanagerptr->selectedBlock->vy;
						//objectmanagerptr->selectedBlock->sub_block = objectmanagerptr->selectedBlock->block;

						checkBlock = objectmanagerptr->selectedBlock;


					}
					else {
						//常時反映可能
						objectmanagerptr->selectedBlock->block.w = (int)block_w;
						objectmanagerptr->selectedBlock->block.h = (int)block_h;
						objectmanagerptr->selectedBlock->rad = (int)block_r;
						objectmanagerptr->selectedBlock->radplus = (int)block_rp;
						objectmanagerptr->selectedBlock->vx = (int)block_vx;
						objectmanagerptr->selectedBlock->vy = (int)block_vy;

						objectmanagerptr->selectedBlock->sub_block.w = (int)block_w;
						objectmanagerptr->selectedBlock->sub_block.h = (int)block_h;


					}

				}

			}

		}

		//

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
		SimpleGUI::RadioButtons(blockaddIndex, blockaddoptions, BlockGUIBox.pos + Vec2(0, 310), unspecified,c_additon);

	};

	void CommonGUIsystem()const
	{
		itemfont(U"StageName:").draw(802, 15, Palette::Black);
		//ステージ名入力用
		SimpleGUI::TextBox(stagename, Vec2(890, 10), 200, 10);



		//保存ボタン
		if (SimpleGUI::Button(U"保存", Vec2(1110, 10), 50))
		{
			

			saving = true;
			//ファイル指定
			//スクリーンショットをとる(GUIを見えなくする？)
			//ステージ名とオブジェクトデータ,スクショの保存
		}

		itemfont(U"Edit or Add:").draw(802, 60, Palette::Black);
		SimpleGUI::RadioButtons(editoraddIndex, editoptions, Vec2(800, 90), 80,c_editoradd);

		itemfont(U"Object:").draw(902, 60, Palette::Black);
		SimpleGUI::RadioButtons(objectIndex, objectoptions, Vec2(900, 90), 100);

	}

	void drawstart()const 
	{
		//描画順を考慮して分離
		startcircle.draw(Palette::Whitesmoke);
	}


	void draw()const 
	{

		//共通



		//GUIウィンドウの描画
		BlockGUIBox.draw(Palette::Silver);
		BlockGUIheader.draw(Palette::White);
		datafont(U"BlockGUI").drawAt(BlockGUIheader.center(),Palette::Black);


		//マウス座標の表示
		datafont(Cursor::Pos()).draw(800,200);

		//GUI

		CommonGUIsystem();
		BlockGUIsystem();


		//操作方法の説明

		//基本的な説明
		String explain =
			U"ここではいらいらボールのゲームを作成できます。クリックでボールを運んでシミュレートできます。\nObjectオプションを選択して編集するオブジェクトの種類を変えられます。\n";

		if (objectoptions[objectIndex] == U"None") 
		{
			explain += U"None項目\n緑色のゴールを左クリックで動かして運べます\n右クリックするとボールのスタート地点を設定できます。";

		}
		else if(objectoptions[objectIndex] == U"Block")
		{
			explain += U"Block項目\nブロックの追加や編集ができます。ブロックを左クリックを1回した（水色枠）後にもう一度左クリック（オレンジ枠）で運ぶことができます\n";
			explain += U"各項目は，height=高さ，width=幅，rad=回転，radplus=角速度（指定するとその速度で回転)，vx=横移動速度，vy=縦移動速度(指定するとその速度で移動)です。";
			explain += U"vxとvyは同時に設定することはできません。\n";

		}

		if (editoptions[editoraddIndex] == U"Add") 
		{
			explain += U"Addモード\nAddモードでは右クリックで図形の追加ができます。GUIで設定した要素のオブジェクトが生成されます。既にあるブロックを選択すると要素をコピーできるのでオススメです。\n";
		}
		else if (editoptions[editoraddIndex] == U"Edit")
		{
			explain += U"Editモード\nEditモードでは既にあるオブジェクトの要素をGUIから変更できます。また、二回選択したオブジェクトを右クリックで削除できます。\n";
		}

		itemfont(explain).draw(10,610);





		
	}


};