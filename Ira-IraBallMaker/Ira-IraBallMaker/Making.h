#pragma once
#include "manager.h"
#include "EditGUI.h"


class Making : public MyApp::Scene
{
public:

	//CSVData csver;

	bool pause = false;

	Ball_kun ballkun{ {250,250} };


	//��̃I�u�W�F�N�g�}�l�[�W���[��錾
	ObjectManager objectmanager = {} ;

	//EditGUI���{�[���ƃI�u�W�F�N�g������
	EditGUI editgui{ &ballkun,&objectmanager };


	Making(const InitData& init)
		: IScene(init)
	{
		Window::Resize(1200, 700);

		//stagedata�ɍ��킹�ăf�[�^�̓ǂݎ��
		//ObjectManager�̔z���Object����

		//�e�X�g�p
		objectmanager.add(std::make_shared<Block>(RectF(30, 30, 40, 100), 0, 0, 0, 0, &ballkun));
		objectmanager.add(std::make_shared<Block>(RectF(130, 30, 40, 100), Math::Pi / 4, 0, 0, 0, &ballkun));
		objectmanager.add(std::make_shared<Block>(RectF(30, 130, 40, 100), 0, Math::Pi / 4, 0, 0, &ballkun));
		objectmanager.add(std::make_shared<Block>(RectF(30, 30, 40, 100), 0, 0, 10, 0, &ballkun));
		objectmanager.add(std::make_shared<Block>(RectF(100, 100, 40, 100), 0, 0, 0, 5, &ballkun));
		//objectmanager.add(std::make_shared<Block>(RectF(150, 150, 40, 100), 0, 0, 5, 5, &ballkun));


		//ballkun�̈ʒu���f�[�^�ʂ�ɏC��



	}


	void update()override
	{


		editgui.update();

		//�߂�
		if (Key0.down())changeScene(SceneName::Select);

	
		//�|�[�Y(����/���s�|�[�Y�̌�ɂ����B)
		if (pause) {
			if (KeyP.down())pause = false;
			if (MouseR.down())changeScene(SceneName::Select);//�߂�
			return;
		}

		//�|�[�Y�Ȃ�Ή�����
		if (!pause && KeyP.down())pause = true;



		ballkun.update();

		//�ҏW��ʂ���o���畜�A����
		if (!Rect(0,0,800, 600).intersects(ballkun.ballbody))ballkun.reset();
		
		objectmanager.update();

		if (KeyZ.down())
		{
			changeScene(SceneName::Result);
		}





	}

	void draw()const override
	{

		Window::ClientRect().draw(Palette::Black);

		if (pause) getData().font(U"�|�[�Y\n\n�߂�F�E�N���b�N").drawAt(Window::Center());


		objectmanager.draw();
		ballkun.draw();


		//�ҏW��ʂ̘g�g��
		Rect(800, 0, 400, 700).draw(Palette::Gray);
		Rect(0, 600, 1200, 100).draw(Palette::Gray);

		editgui.draw();

	}


};