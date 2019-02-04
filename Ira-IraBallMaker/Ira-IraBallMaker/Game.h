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

	//�N���A�^�C���L�^�p�^�C�}�[
	Stopwatch timer;

	Font timefont{ 10 };

	//���삷��{�[��
	Ball_kun ballkun{ {250,250} };

	//�S�[��
	Goal goal{ &ballkun,Vec2(400,400) };


	//��̃I�u�W�F�N�g�}�l�[�W���[��錾(�f�[�^�ǂݍ��݂̉ߒ��ő��)
	ObjectManager objectmanager = {};


	//�f�[�^�ǂݏo���p
	DataManager datamanader {&objectmanager, &goal };

	Game(const InitData& init)
		: IScene(init)
	{
		Window::Resize(800, 600);
		
		//stagedata�ɍ��킹�ăf�[�^�̓ǂݎ��
		
		datamanader.stagereadV2(getData().filepath,ballkun,getData().mode);

		newrecord = false;
		
		//�S�[���̈ʒu���f�[�^�ʂ�ɏC��
		//Block���f�[�^�ʂ�ɔz�u


		//�e�X�g�p(�u���b�N�̔z�u)
		//objectmanager.add(std::make_shared<Block>(RectF(30, 30, 40, 100), 0, 0, 0, 0,&ballkun));
		//objectmanager.add(std::make_shared<Block>(RectF(130, 30, 40, 100), Math::Pi / 4, 0, 0, 0, &ballkun));
		//objectmanager.add(std::make_shared<Block>(RectF(30, 130, 40, 100), 0, Math::Pi / 4, 0, 0, &ballkun));
		//objectmanager.add(std::make_shared<Block>(RectF(30, 30, 40, 100), 0, 0, 10, 0, &ballkun));
		//objectmanager.add(std::make_shared<Block>(RectF(100, 100, 40, 100), 0, 0, 0, 5, &ballkun));
		//objectmanager.add(std::make_shared<Block>(RectF(150, 150, 40, 100), 0, 0, 5, 5, &ballkun));
		
		//ballkun�̈ʒu���f�[�^�ʂ�ɏC��
		ballkun.pos = goal.startpos;
		ballkun.ballbody.setPos(goal.startpos);
		

		//�^�C�}�[�J�n

		if (timer.isRunning())timer.restart();
		else timer.start();
	}


	void update()override
	{

		//�߂�
		if (Key0.down())changeScene(SceneName::Select);

		//if(win) ballkun.
		

		//����/���s�p�|�[�Y
		if (win || lose) {

			//�^�C�}�[��~
			timer.pause();

			if (win) {
				ballkun.facechange("WIN");
				if(datamanader.cleardata(getData().stagenum,getData().filepath,timer.s()))newrecord = true;
				//�^�C�}�[�̃^�C������ꂽ�肷��
			}
			if(lose)ballkun.facechange("LOSE");

			if (MouseL.down())changeScene(SceneName::Game);//�������
			if (MouseR.down())changeScene(SceneName::Select);//�߂�
			return;
		}		

		

		//�|�[�Y(����)
		if (pause) {

			if (KeyP.down())
			{
				timer.start();
				pause = false;
			}
			if (MouseR.down())changeScene(SceneName::Select);//�߂�
			return;
		}

		//�|�[�Y����
		if (!pause && KeyP.down() && lose == false && win == false)
		{
			timer.pause();
			pause = true;
		}


		//�{�[���̈ʒu�i��j�X�V
		ballkun.update();

		//�S�[���ɒ������珟��
		win = goal.update();
		
		//�I�u�W�F�N�g�ƂԂ������畉��
		lose = objectmanager.update();

		//�ҏW��ʂ���o���畉��
		if (!Rect(0,0,800, 600).intersects(ballkun.ballbody))lose = true;

		if (KeyZ.down())
		{
			changeScene(SceneName::Title);
		}
	}

	void draw()const override
	{
		
		Window::ClientRect().draw(Palette::Black);

		//�S�[���̓I�u�W�F�N�g�ɉB��A�{�[�����őO��

		goal.draw();
		objectmanager.draw();
		ballkun.draw();


		//�őO���Q

		//�e�L�X�g�o�͕�
		if(pause) getData().font(U"�|�[�Y\n\n��蒼��:���N���b�N\n�߂�F�E�N���b�N").drawAt(Window::Center(), Palette::Aqua);
		else if (win) {
			if(newrecord)getData().font(U"�X�e�[�W�N���A�I�I\n�V�L�^�I�I\n", timer.s(), U" �b�@�@�@\n�������:���N���b�N\n�߂�:�E�N���b�N").drawAt(Window::Center(), Palette::Aqua);
			else getData().font(U"�X�e�[�W�N���A�I�I\n�@�@�@", timer.s(), U" �b�@�@�@\n�������:���N���b�N\n�߂�:�E�N���b�N").drawAt(Window::Center(), Palette::Aqua);
		}
		else if (lose) {
			if(!Rect(0,0,800,600).intersects(ballkun.ballbody)) getData().font(U"�R�[�X�A�E�g�c\n\n�������:���N���b�N\n�߂�:�E�N���b�N").drawAt(Window::Center(),Palette::Aqua);
			else getData().font(U"�N���A���s�c\n\n�������:���N���b�N\n�߂�:�E�N���b�N").drawAt(Window::Center(), Palette::Aqua);
		}

		//�^�C�}�[
		timefont(timer.s()).draw();
		
	}


};