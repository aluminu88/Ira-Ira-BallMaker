#pragma once


/*��Q���Ƃ��Ă̍ł���{�I�Ȃ���*/

/*
IObject�͍Œ���̋��ʋ@�\��p�ӂ���
- �{�[���̈ʒu�̔c��
- ���zupdate,���zdraw
- �Փˏ��
- �I���A�͂ݔ���i�ҏW�p)
Block
Line
*/


#include<Siv3D.hpp>
#include "Ball_Kun.h"
#include<memory>

//��Q���̊��N���X

class IObject {

private :

	bool hit = false;
	
	
	
	Font font{ 10 };//�f�o�b�N�p

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

	//�{�͎̂l�p�`
	RectF block, sub_block;
	Vec2 pos;

	//�V���ɕK�v�ȏ��:��]�p�A�p���x�Ax���x�Ay���x

	double rad, radplus, vx, vy;
	
	
	Block(RectF _rect, double _rad, double _radplus, double _vx, double _vy, Ball_kun* _Ball) :
		block(_rect),
		rad(_rad),
		radplus(_radplus),
		vx(_vx),
		vy(_vy),
		IObject(_Ball)
	{
		setID(1);
		pos = block.pos;
		sub_block = block;
		
	}

	Block(RectF _rect, double _rad, double _radplus, double _vx, double _vy, Ball_kun* _Ball,int _option) :
		block(_rect),
		rad(_rad),
		radplus(_radplus),
		vx(_vx),
		vy(_vy),
		IObject(_Ball)
	{
		setID(_option);//mode=0:Game,1:Making
		pos = block.pos;
		sub_block = block;

	}

	void update()override 
	{
	
		


	//�{�[���Ƃ̏Փ˔���

		//�^�Փ˔���
			if (Ball->ballbody.intersects(block.rotated(rad)))
			{
				hitting();
			}
		

	//�{�̂̏���

		//��]
		

		rad += radplus;
		if (rad > 6.28) {

			while (rad > 12.56) {

				rad = rad - 6.28;

			}
		}

		if (!grabbed)block.pos += {vx, vy};

		//�����[�v//�E�ړ�//������ƍs���߂���?
		if (vx > 0) {
			
			if (!(800 >= (block.tl().x))) {
				block.pos.x = 0;
			}

			if (800 >= (block.tr().x)) {

				sub_block.pos.x = 0 - sub_block.w - vx;

				if (Ball->ballbody.intersects(block.rotated(rad))) {//block���܂܂�Ă���Ƃ��̂����蔻��

					hitting();
				}
				


			}

			if (!(800 >= (block.tr().x))) {//block���܂܂�Ȃ��Ȃ����Ƃ�

				sub_block.pos += {vx, 0};//sub_block�𓮂����ă��[�v���Ă���悤�Ɍ�����


				if (Ball->ballbody.intersects(sub_block.rotated(rad))) {//���̊�sub_block�̂����蔻�����������
					hitting();
				}
				
			}

		}
		//

		//�����[�v//���ړ�//������ƍs���߂���?
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

		//�c���[�v//��ړ�//������ƍs���߂���?
		if (vy < 0) {

			if (!(0 <= (block.bl().y))) {//Rect���G��Ă��遨y��0�ʓ��ɐG��Ă��遨y�����O�ȏ�
				block.pos.y = 600 - block.h;
			}

			if (0 < (block.tl().y)) {//Rect���܂܂�Ă��遨y�オ��ʓ���y�オ0����

				sub_block.pos.y = 600 - vy;//���ɃZ�b�g
				if (Ball->ballbody.intersects(block.rotated(rad))) {

					hitting();
				}
				

			}

			if (!(0 < (block.tl().y))) {//Rect���܂܂�Ă��Ȃ���y�オ��ʊO��y�オ0����łȂ�

				sub_block.pos += {vx, vy};


				if (Ball->ballbody.intersects(sub_block.rotated(rad))) {
					hitting();
				}
				

			}


		}
		//

		//�c���[�v//���ړ�//������ƍs���߂���?
		if (vy > 0) {

			if (!(600 >= (block.tl().y))) {//Rect���G��Ă��Ȃ���y�オ600�ʓ��łȂ���y�オ600�ȉ��łȂ�
				block.pos.y = 0;
			}

			if (600 > (block.bl().y)) {//Rect���܂܂�Ă��遨y������ʓ���y����600��菬

				sub_block.pos.y = 0 - block.h - vy;//��ɃZ�b�g
				if (Ball->ballbody.intersects(block.rotated(rad))) {

					hitting();
				}
				

			}

			if (!(600 > (block.bl().y))) {//Rect���܂܂�Ă��Ȃ���y������ʊO��y����600��菬�łȂ�

				sub_block.pos += {vx, vy};


				if (Ball->ballbody.intersects(sub_block.rotated(rad))) {
					hitting();
				}
				

			}


		}
		//
		
		


		//�ҏW���݂̂ł��鏈��
		if (getID() == 1) 
		{


			//�}�`��I������
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


			//�}�`��͂�
			if (block.leftClicked() && !Ball->ballbody.intersects(Cursor::PosF()) && state == SelectState::d_select)
			{
				grabbed = true;
			}
			else if (MouseL.up()) 
			{
				grabbed = false;
			}
			else if (grabbed && state == SelectState::d_select)
			{
				block.pos += Cursor::DeltaF();
				sub_block = block;
			}

			//�}�`��hit������������
			if (gethit()) 
			{
				if (!(Ball->ballbody.intersects(block.rotated(rad)))&& !(Ball->ballbody.intersects(sub_block.rotated(rad)) && sub_block.intersects(Rect(0, 0, 800, 600))))
				{
					hitreset();
				}
			}

			//�폜��Ԃɂ���
			if (state == SelectState::d_select) 
			{
				if (MouseR.down()|| KeyD.down()) kill();
				
				if (MouseL.up() && !Rect(0,0,800,600).intersects(block)) kill();
			}
			if ((int)block.h == 0 && (int)block.w == 0) kill();

		}

		
	}

	void draw()const {

		//�Փˏ󋵂ɂ���ĕ`�悷��F��ύX

		if (gethit())
		{
			block.rotated(rad).draw(Palette::Red);//�Փˁ���
			//sub_block.rotated(rad).draw(Palette::Red);
		}
		else {
			block.rotated(rad).draw(Palette::White);
			//sub_block.rotated(rad).draw(Palette::White);//��Փˁ���
		}

		//���[�v�ړ��̂��߂̕`��

		if ((!(800 > (block.tr().x)) && vx > 0) || (!(0 < (block.tl().x)) && vx < 0) || (!(0 < block.tl().y) && vy < 0) || (!(600 > block.bl().y) && vy > 0)) {//�܂܂�ĂȂ��Ƃ��̂�

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



		//�ҏW���݂̂̏���
		if (getID() == 1)
		{
			//�I������Ă���
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
//		//�{�[���Ƃ̏Փ˔���(���S�ɕ�񂾎��ɃS�[���Ƃ���)
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


class Wire : public IObject{


public :

	//�K�v�̂Ȃ���

	//�n�_�E�I�_
	Vec2 pos1, pos2;

	double width;
	
	Line line;

	Wire(Vec2 _pos1, Vec2 _pos2,Ball_kun* _Ball) :
		pos1(_pos1),
		pos2(_pos2) ,
		IObject(_Ball)
	{
		//�ҏW���ǉ��͎����I��ID"1"��U��
		setID(1);
		line = Line(pos1, pos2);
	}

	Wire(Vec2 _pos1, Vec2 _pos2, Ball_kun* _Ball,int _option) :
		pos1(_pos1),
		pos2(_pos2),
		IObject(_Ball)
	{
		//�Q�[����������ID"0"��U��
		setID(_option);
		line = Line(pos1, pos2);
	}

	//�v�f�P�̂̏����͂�����

	void update() override
	{
		//�Փ˔���A�I�𔻒�Ȃ�
		if (Ball->ballbody.intersects(line)) 
		{
			hitting();
		}

		//�ړ��Ƃ�(Line�͂��Ȃ�)


		//�ҏW���݂̂̏���
		if (getID() == 1) 
		{


			//�}�`��I������
			if (line.boundingRect().leftClicked() && !(Rect(800, 0, 400, 700).intersects(Cursor::Pos()) || Rect(0, 600, 1200, 100).intersects(Cursor::Pos())))
			{
				
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


			//�}�`��͂�
			if (line.boundingRect().leftClicked() && !Ball->ballbody.intersects(Cursor::PosF()) && state == SelectState::d_select)
			{
				grabbed = true;
			}
			else if (MouseL.up())
			{
				grabbed = false;
			}
			else if (grabbed && state == SelectState::d_select)
			{

				pos1+= Cursor::DeltaF();
				pos2+= Cursor::DeltaF();
				line.begin += Cursor::DeltaF();
				line.end += Cursor::DeltaF();				
			}

			//�}�`��hit������������
			if (gethit())
			{
				if (!Ball->ballbody.intersects(line))
				{
					hitreset();
				}
			}

			//�폜��Ԃɂ���
			if (state == SelectState::d_select)
			{
				if (MouseR.down() || KeyD.down()) kill();

				if (MouseL.up() && !Rect(0, 0, 800, 600).intersects(line)) kill();
			}
			//if (line.length()<=2) kill();



		}

	}

	void draw() const
	{
		//����ɂ���ĐF��ς��ĕ`�悷��

		if (gethit()) 
		{
			line.draw(Palette::Red);
		}
		else line.draw(Palette::White);


		//�ҏW���̏���
		if (getID() == 1) 
		{


			//�I����Ԃ̕`��

			if (state == SelectState::select)
			{
				//Rect�ɕϊ����Ęg�̕`��
				line.boundingRect().drawFrame(0, 2, Palette::Aqua);//���A�O
			}
			else if (state == SelectState::d_select) {
				line.boundingRect().drawFrame(0, 2, Palette::Orange);

			}
		}


	}



};


class ObjectManager {

public :
	std::vector<std::shared_ptr<IObject>> objects;

	std::shared_ptr<Block> selectedBlock ;

	std::vector<std::shared_ptr<Block>> blocks;

	std::shared_ptr<Wire> selectedWire;

	std::vector<std::shared_ptr<Wire>> wires;





	//EditGUI* editgutptr;

	//ObjectManager(EditGUI* _editgutptr) :editgutptr(_editgutptr) {};

	ObjectManager();

	void add(const std::shared_ptr<Block>& ptr);
	
	void blockadd(const std::shared_ptr<Block>& ptr);

	void wireadd(const std::shared_ptr<Wire>& ptr);

	
	bool selectflag= false;
	
	bool update();
	void draw()const;

};