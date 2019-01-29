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



	/*�Ǘ��p*/

	mutable TextEditState stagename{ U"�X�e�[�W��" };

	Font datafont{ 20 }, itemfont{15};

	//

	mutable bool saving = false;

	/*Goal�p*/

	bool goalgrabbed = false;

	/*�{�[���̃X�^�[�g�n�_*/
	Circle startcircle = Circle{Vec2(250,250),30.0};

	/*Block�p*/

	//GUI�p�ϐ�
	mutable double block_w = 0.0, block_h = 0.0, block_r=0.0,block_rp=0.0,block_vx=0.0,block_vy=0.0;
	mutable bool c_vx = true, c_vy = false,c_additon = false,c_editoradd = true;

	//GUI�p�E�B���h�E
	RectF BlockGUIBox = RectF(2000, 250, 400, 450);//{800,250}����ʒu

	RectF BlockGUIheader = RectF(2000, 250, 400, 30);

	bool BlockGUIgrabbed = false;

	//�}�`�ǉ��p
	RectF  stampRect;
	std::shared_ptr<Block> checkBlock = 0;
	

	/*�R���X�g���N�^*/

	EditGUI(Ball_kun* _ballkunptr,ObjectManager* _objectmanagerptr,Goal* _goalptr) :
		objectmanagerptr(_objectmanagerptr),
		ballkunptr(_ballkunptr),
		goalptr(_goalptr)
	{}
	

	/*���W�I�{�^���p*/

	//�J�[�\�������Ǐ],�����^�ԁA�����Ȃ�����

	const Array<String> blockaddoptions =
	{
		U"Cursor", U"Bring",U"Invisible"
	};

	mutable size_t blockaddIndex = 0;


	//�}�`��ҏW���邩�A�}�`��ǉ����邩

	const Array<String> editoptions =
	{
		U"Edit", U"Add"
	};

	mutable size_t  editoraddIndex = 0;


	//�W�J����GUI�E�B���h�E�̎��

	const Array<String> objectoptions =
	{
		U"None",U"Block",U"Line"
	};
	
	mutable size_t objectIndex = 0;
	


	void update() 
	{
		
		/*None�p�̍���*/

		//Goal

		if (objectoptions[objectIndex] == U"None") {
			c_editoradd = false;
			BlockGUIBox.x = 2000;//�\�����Ȃ�

			//goal�������^�ׂ�
			if (goalptr->goalrect.leftClicked()) {
				goalgrabbed = true;
			}
			else if (MouseL.up()) {
				goalgrabbed = false;
			}
			else if (goalgrabbed) {
				goalptr->goalrect.pos += Cursor::DeltaF();
			}

			//��ʓ��Ɋ��S�ɓ����Ă��Ȃ��ꍇ�ʒu�����Z�b�g����
			if(!Rect(0,0,800,600).contains(goalptr->goalrect)) goalptr->goalrect.setPos(400, 400);

			//�}�E�X�E�N���b�N�ŃX�^�[�g�n�_��ݒ�
			if (Rect(0, 0, 800, 600).intersects(Cursor::Pos()) && MouseR.down()) 
			{
				startcircle.setPos(Cursor::Pos());
				goalptr->startpos = Cursor::Pos();
			}

			

		}else c_editoradd = true;

		


		/*Block�p�̍���*/

		BlockGUIheader.pos = BlockGUIBox.pos;

		stampRect = RectF(Cursor::Pos(), block_w, block_h);

		//Block�ҏW�@�\

		if (objectoptions[objectIndex] == U"Block")
		{

			//�����������Ȃ�R�����g�A�E�g���Ƃ�

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


			//BlockGUI��\��
			BlockGUIBox.x = 800;

			//Add�@�\
			if (editoptions[editoraddIndex] == U"Add")
			{
				c_additon = true;

				if (MouseR.down() && stampRect.w > 0 && stampRect.w > 0)
				{
					objectmanagerptr->add(std::make_shared<Block>(RectF(stampRect), block_r, block_rp, block_vx, block_vy, ballkunptr));
				}
			}
			//Edit�@�\
			else if (editoptions[editoraddIndex] == U"Edit")
			{
				//�����I��Invisible���Aaddoption���A�N�e�B�u
				blockaddIndex = 2;
				c_additon = false;

				//�I�������}�`�̒l���n�C���C�g���A�ȍ~GUI����ύX���\

				if (!objectmanagerptr->selectedBlock == NULL) {



					if (objectmanagerptr->selectedBlock != checkBlock) {//�قȂ�=�ύX�����m
						//���񂾂�����ւ��邾���ɂ�����

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
						//�펞���f�\
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

		//�X���C�_�[
		itemfont(U"width:").draw(BlockGUIBox.pos + Vec2(2, 40), Palette::Black);
		if (SimpleGUI::Button(U"-", BlockGUIBox.pos + Vec2(65, 40), 20))
		{
			block_w--;
		}
		SimpleGUI::Slider(block_w, 0, 500, BlockGUIBox.pos + Vec2(90, 40), 200);//��
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
		SimpleGUI::Slider(block_h, 0, 500, BlockGUIBox.pos + Vec2(90, 80), 200);//����
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
		SimpleGUI::Slider(block_r, -360, 360, BlockGUIBox.pos + Vec2(90, 120), 200);//�p�x
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
		SimpleGUI::Slider(block_rp, -360_deg, 360_deg, BlockGUIBox.pos + Vec2(90, 160), 200);//�p���x
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
		SimpleGUI::Slider(block_vx, -10, 10, BlockGUIBox.pos + Vec2(90, 200), 200, c_vx);//x���x
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
		SimpleGUI::Slider(block_vy, -10, 10, BlockGUIBox.pos + Vec2(90, 240), 200, c_vy);//x���x
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
		//�X�e�[�W�����͗p
		SimpleGUI::TextBox(stagename, Vec2(890, 10), 200, 10);



		//�ۑ��{�^��
		if (SimpleGUI::Button(U"�ۑ�", Vec2(1110, 10), 50))
		{
			

			saving = true;
			//�t�@�C���w��
			//�X�N���[���V���b�g���Ƃ�(GUI�������Ȃ�����H)
			//�X�e�[�W���ƃI�u�W�F�N�g�f�[�^,�X�N�V���̕ۑ�
		}

		itemfont(U"Edit or Add:").draw(802, 60, Palette::Black);
		SimpleGUI::RadioButtons(editoraddIndex, editoptions, Vec2(800, 90), 80,c_editoradd);

		itemfont(U"Object:").draw(902, 60, Palette::Black);
		SimpleGUI::RadioButtons(objectIndex, objectoptions, Vec2(900, 90), 100);

	}

	void drawstart()const 
	{
		//�`�揇���l�����ĕ���
		startcircle.draw(Palette::Whitesmoke);
	}


	void draw()const 
	{

		//����



		//GUI�E�B���h�E�̕`��
		BlockGUIBox.draw(Palette::Silver);
		BlockGUIheader.draw(Palette::White);
		datafont(U"BlockGUI").drawAt(BlockGUIheader.center(),Palette::Black);


		//�}�E�X���W�̕\��
		datafont(Cursor::Pos()).draw(800,200);

		//GUI

		CommonGUIsystem();
		BlockGUIsystem();


		//������@�̐���

		//��{�I�Ȑ���
		String explain =
			U"�����ł͂��炢��{�[���̃Q�[�����쐬�ł��܂��B�N���b�N�Ń{�[�����^��ŃV�~�����[�g�ł��܂��B\nObject�I�v�V������I�����ĕҏW����I�u�W�F�N�g�̎�ނ�ς����܂��B\n";

		if (objectoptions[objectIndex] == U"None") 
		{
			explain += U"None����\n�ΐF�̃S�[�������N���b�N�œ������ĉ^�ׂ܂�\n�E�N���b�N����ƃ{�[���̃X�^�[�g�n�_��ݒ�ł��܂��B";

		}
		else if(objectoptions[objectIndex] == U"Block")
		{
			explain += U"Block����\n�u���b�N�̒ǉ���ҏW���ł��܂��B�u���b�N�����N���b�N��1�񂵂��i���F�g�j��ɂ�����x���N���b�N�i�I�����W�g�j�ŉ^�Ԃ��Ƃ��ł��܂�\n";
			explain += U"�e���ڂ́Cheight=�����Cwidth=���Crad=��]�Cradplus=�p���x�i�w�肷��Ƃ��̑��x�ŉ�])�Cvx=���ړ����x�Cvy=�c�ړ����x(�w�肷��Ƃ��̑��x�ňړ�)�ł��B";
			explain += U"vx��vy�͓����ɐݒ肷�邱�Ƃ͂ł��܂���B\n";

		}

		if (editoptions[editoraddIndex] == U"Add") 
		{
			explain += U"Add���[�h\nAdd���[�h�ł͉E�N���b�N�Ő}�`�̒ǉ����ł��܂��BGUI�Őݒ肵���v�f�̃I�u�W�F�N�g����������܂��B���ɂ���u���b�N��I������Ɨv�f���R�s�[�ł���̂ŃI�X�X���ł��B\n";
		}
		else if (editoptions[editoraddIndex] == U"Edit")
		{
			explain += U"Edit���[�h\nEdit���[�h�ł͊��ɂ���I�u�W�F�N�g�̗v�f��GUI����ύX�ł��܂��B�܂��A���I�������I�u�W�F�N�g���E�N���b�N�ō폜�ł��܂��B\n";
		}

		itemfont(explain).draw(10,610);





		
	}


};