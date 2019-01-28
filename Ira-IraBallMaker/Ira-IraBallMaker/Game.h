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

	//��̃I�u�W�F�N�g�}�l�[�W���[��錾
	ObjectManager objectmanager = {};

	Game(const InitData& init)
		: IScene(init)
	{
		Window::Resize(800, 600);
		
		//stagedata�ɍ��킹�ăf�[�^�̓ǂݎ��
		



		//�e�X�g�p(�u���b�N�̔z�u)
		objectmanager.add(std::make_shared<Block>(RectF(30, 30, 40, 100), 0, 0, 0, 0,&ballkun));
		objectmanager.add(std::make_shared<Block>(RectF(130, 30, 40, 100), Math::Pi / 4, 0, 0, 0, &ballkun));
		objectmanager.add(std::make_shared<Block>(RectF(30, 130, 40, 100), 0, Math::Pi / 4, 0, 0, &ballkun));
		objectmanager.add(std::make_shared<Block>(RectF(30, 30, 40, 100), 0, 0, 10, 0, &ballkun));
		objectmanager.add(std::make_shared<Block>(RectF(100, 100, 40, 100), 0, 0, 0, 5, &ballkun));
		//objectmanager.add(std::make_shared<Block>(RectF(150, 150, 40, 100), 0, 0, 5, 5, &ballkun));


		//ballkun�̈ʒu���f�[�^�ʂ�ɏC��


		//�S�[���̈ʒu���f�[�^�ʂ�ɏC��
		


	}


	void update()override
	{

		//�߂�
		if (Key0.down())changeScene(SceneName::Select);

		//if(win) ballkun.


		//����/���s�p�|�[�Y
		if (win || lose) {

			if (win)ballkun.facechange("WIN");
			if(lose)ballkun.facechange("LOSE");

			if (MouseL.down())changeScene(SceneName::Game);//�������
			if (MouseR.down())changeScene(SceneName::Select);//�߂�
			return;
		}		

		

		//�|�[�Y(����/���s�|�[�Y�̌�ɂ����B)
		if (pause) {
			if (KeyP.down())pause = false;
			if (MouseR.down())changeScene(SceneName::Select);//�߂�
			return;
		}

		//�|�[�Y�Ȃ�Ή�����
		if (!pause && KeyP.down() && lose == false && win == false)pause = true;



		ballkun.update();
		//�ҏW��ʂ���o����܂�

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

		if(pause) getData().font(U"�|�[�Y\n\n��蒼��:���N���b�N\n�߂�F�E�N���b�N").drawAt(Window::Center());
		else if(win)  getData().font(U"�X�e�[�W�N���A�I�I\n\n�������:���N���b�N\n�߂�:�E�N���b�N").drawAt(Window::Center());
		else if (lose) {
			if(!Rect(0,0,800,600).intersects(ballkun.ballbody)) getData().font(U"�R�[�X�A�E�g�c\n\n�������:���N���b�N\n�߂�:�E�N���b�N").drawAt(Window::Center());
			else getData().font(U"�N���A���s�c\n\n�������:���N���b�N\n�߂�:�E�N���b�N").drawAt(Window::Center());
		}
		objectmanager.draw();
		ballkun.draw();
	}


};