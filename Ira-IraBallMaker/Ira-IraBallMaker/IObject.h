#pragma once


/*障害物としての最も基本的なもの*/

/*
IObjectは最低限の共通機能を用意する
- ボールの位置の把握
- 仮想update,仮想draw
- 衝突情報
- 選択、掴み判定（編集用)
Block
Line
*/


#include<Siv3D.hpp>
#include "Ball_Kun.h"
#include<memory>

//障害物の基底クラス

class IObject {

private :

	bool hit = false;
	
	
	
	Font font{ 10 };//デバック用

	int ID;

protected:

	bool selected = false;
	bool d_selected = false;
	bool deleted = false;


public :

	enum class SelectState
	{
		none,
		select,
		d_select

	};

	SelectState state = SelectState::none;

	bool grabbed = false;

	bool gethit()const { return hit; }
	bool getdelete() { return deleted; }
	bool getselect()const { return selected; }
	bool getd_select()const { return d_selected; }

	int getID()const { return ID; }

	void hitting() { hit = true; }
	void hitreset() { hit = false; }
	void kill() { deleted = true; }

	void select() { 
		selected = true;
	}

	void d_select() { d_selected = true; }

	void setID(int _ID) { ID = _ID; }

	Ball_kun* Ball;

	IObject(Ball_kun* _Ball) :
		Ball(_Ball)
	{
	};

	virtual void update() = 0;
	virtual void draw()const = 0;

};

class Block : public IObject
{
public:

	//本体は四角形
	RectF block, sub_block;
	Vec2 pos;

	//新たに必要な情報:回転角、角速度、x速度、y速度

	double rad, radplus, vx, vy;
	

	Block(RectF _rect, double _rad, double _radplus, double _vx, double _vy, Ball_kun* _Ball) :
		block(_rect),
		rad(_rad),
		radplus(_radplus),
		vx(_vx),
		vy(_vy),
		IObject(_Ball)
	{
		setID(101);
		pos = block.pos;
		sub_block = block;
		
	}

	void update()override 
	{
	
		


	//ボールとの衝突判定

		//真衝突判定
			if (Ball->ballbody.intersects(block.rotated(rad)))
			{
				hitting();
			}
		

	//本体の処理

		//回転
		rad += radplus;
		if (rad > 6.28) {

			while (rad > 12.56) {

				rad = rad - 6.28;

			}
		}

		if (!grabbed)block.pos += {vx, vy};

		//横ループ//右移動//ちょっと行き過ぎる?
		if (vx > 0) {
			
			if (!(800 >= (block.tl().x))) {
				block.pos.x = 0;
			}

			if (800 >= (block.tr().x)) {

				sub_block.pos.x = 0 - sub_block.w - vx;

				if (Ball->ballbody.intersects(block.rotated(rad))) {//blockが含まれているときのあたり判定

					hitting();
				}
				


			}

			if (!(800 >= (block.tr().x))) {//blockが含まれなくなったとき

				sub_block.pos += {vx, 0};//sub_blockを動かしてループしているように見せる


				if (Ball->ballbody.intersects(sub_block.rotated(rad))) {//この間sub_blockのあたり判定を持たせる
					hitting();
				}
				
			}

		}
		//

		//横ループ//左移動//ちょっと行き過ぎる?
		if (vx < 0) {

			if (!(0 <= (block.tr().x))) {
				block.pos.x = 800 - block.w;
			}

			if (0 < (block.tl().x)) {

				sub_block.pos.x = 800 - vx;

				if (Ball->ballbody.intersects(block.rotated(rad))) {

					hitting();

				}
				

			}

			if (!(0 < (block.tl().x))) {

				sub_block.pos += {vx, 0};


				if (Ball->ballbody.intersects(sub_block.rotated(rad))) {
					hitting();
				}
				

			}


		}
		//

		//縦ループ//上移動//ちょっと行き過ぎる?
		if (vy < 0) {

			if (!(0 <= (block.bl().y))) {//Rectが触れている→y下0位内に触れている→y下が０以上
				block.pos.y = 600 - block.h;
			}

			if (0 < (block.tl().y)) {//Rectが含まれている→y上が画面内→y上が0より大

				sub_block.pos.y = 600 - vy;//下にセット
				if (Ball->ballbody.intersects(block.rotated(rad))) {

					hitting();
				}
				

			}

			if (!(0 < (block.tl().y))) {//Rectが含まれていない→y上が画面外→y上が0より大でない

				sub_block.pos += {vx, vy};


				if (Ball->ballbody.intersects(sub_block.rotated(rad))) {
					hitting();
				}
				

			}


		}
		//

		//縦ループ//下移動//ちょっと行き過ぎる?
		if (vy > 0) {

			if (!(600 >= (block.tl().y))) {//Rectが触れていない→y上が600位内でない→y上が600以下でない
				block.pos.y = 0;
			}

			if (600 > (block.bl().y)) {//Rectが含まれている→y下が画面内→y下が600より小

				sub_block.pos.y = 0 - block.h - vy;//上にセット
				if (Ball->ballbody.intersects(block.rotated(rad))) {

					hitting();
				}
				

			}

			if (!(600 > (block.bl().y))) {//Rectが含まれていない→y下が画面外→y下が600より小でない

				sub_block.pos += {vx, vy};


				if (Ball->ballbody.intersects(sub_block.rotated(rad))) {
					hitting();
				}
				

			}


		}
		//
		
		


		//編集中のみできる処理
		if (getID() > 100) 
		{


			//図形を選択する
			if ((block.rotated(rad).leftClicked() || sub_block.rotated(rad).leftClicked()) && !(Rect(800, 0, 400, 700).intersects(Cursor::Pos()) || Rect(0, 600, 1200, 100).intersects(Cursor::Pos())))
			{
				//if (getselect())d_select();
				//select();
				if (state == SelectState::none)
				{
					state = SelectState::select;
				}
				else if (state == SelectState::select) 
				{
					state = SelectState::d_select;
				}
				else if (state == SelectState::d_select) 
				{
					state = SelectState::none;
				}


			}
			else if (MouseL.down() && !(Rect(800, 0, 400, 700).intersects(Cursor::Pos()) || Rect(0, 600, 1200, 100).intersects(Cursor::Pos()))) state = SelectState::none;

			//Rect(800, 0, 400, 700).draw(Palette::Gray);
			//Rect(0, 600, 1200, 100).draw(Palette::Gray);


			//図形を掴む
			if (block.leftClicked() && !Ball->ballbody.intersects(Cursor::PosF()) && state == SelectState::d_select)
			{
				grabbed = true;
			}
			else if (MouseL.up()) 
			{
				grabbed = false;
			}
			else if (grabbed) 
			{
				block.pos += Cursor::DeltaF();
				sub_block = block;
			}

			//図形のhitを初期化する
			if (gethit()) 
			{
				if (!(Ball->ballbody.intersects(block.rotated(rad)))&& !(Ball->ballbody.intersects(sub_block.rotated(rad)) && sub_block.intersects(Rect(0, 0, 800, 600))))
				{
					hitreset();
				}
			}

			//削除状態にする
			if (state == SelectState::d_select) 
			{
				if (MouseR.down()|| KeyD.down()) kill();
				
				if (MouseL.up() && !Rect(Window::Size()).intersects(block)) kill();
			}


		}

		
	}

	void draw()const {

		//衝突状況によって描画する色を変更

		if (gethit())
		{
			block.rotated(rad).draw(Palette::Red);//衝突→赤
			//sub_block.rotated(rad).draw(Palette::Red);
		}
		else {
			block.rotated(rad).draw(Palette::White);
			//sub_block.rotated(rad).draw(Palette::White);//非衝突→白
		}

		//ループ移動のための描画

		if ((!(800 > (block.tr().x)) && vx > 0) || (!(0 < (block.tl().x)) && vx < 0) || (!(0 < block.tl().y) && vy < 0) || (!(600 > block.bl().y) && vy > 0)) {//含まれてないときのみ

			if (state == SelectState::select)sub_block.rotated(rad).drawFrame(2, 0, Palette::Aqua);
			if (state == SelectState::d_select)sub_block.rotated(rad).drawFrame(2, 0, Palette::Orange);

			if (gethit()) {

				sub_block.rotated(rad).draw(Palette::Red);

			}
			else sub_block.rotated(rad).draw(Palette::White);

		}

		//if ((800 >= (block.tl.x) && vx > 0) || (0 <= (block.tr().x) && vx < 0)) {
		if (gethit()) {

			block.rotated(rad).draw(Palette::Red);

		}
		else block.rotated(rad).draw(Palette::White);



		//編集中のみの処理
		if (getID() > 100)
		{
			//選択されている
			if (state == SelectState::select)
			{
				block.rotated(rad).drawFrame(2, 0, Palette::Aqua);
				
				
			}
			else if (state == SelectState::d_select) {
				block.rotated(rad).drawFrame(2, 0, Palette::Orange);
				
			}

		}

	}




};

//class Goal :public IObject
//{
//public :
//
//	RectF goalrect = RectF(70, 70);
//	Vec2 pos;
//
//
//	Goal(Ball_kun* _ball) :IObject(_ball)
//	{};
//
//	bool goaled = false;
//
//	void update()override
//	{
//		//ボールとの衝突判定(完全に包んだ時にゴールとする)
//		if (goalrect.contains(Ball->ballbody)) 
//		{
//			goaled = true;
//		}
//		
//	}
//
//	void draw()const
//	{
//
//	}
//
//};



class ObjectManager {

public :
	std::vector<std::shared_ptr<IObject>> objects;

	std::shared_ptr<Block> selectedBlock ;

	std::vector<std::shared_ptr<Block>> blocks;



	//EditGUI* editgutptr;

	//ObjectManager(EditGUI* _editgutptr) :editgutptr(_editgutptr) {};

	ObjectManager();

	void add(const std::shared_ptr<Block>& ptr);
	
	void blockadd(const std::shared_ptr<Block>& ptr);

	
	bool selectflag= false;
	
	bool update();
	void draw()const;

};