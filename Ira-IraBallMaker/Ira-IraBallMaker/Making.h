#pragma once
#include "manager.h"
#include "EditGUI.h"


class Making : public MyApp::Scene
{
public:

	//CSVData csver;

	bool pause = false;

	//�{�[��
	Ball_kun ballkun{ {250,250} };
	
	//�S�[��
	Goal goal{ &ballkun , Vec2(400,400) };

	//��̃I�u�W�F�N�g�}�l�[�W���[��錾
	ObjectManager objectmanager = {} ;

	//EditGUI���{�[���ƃI�u�W�F�N�g������
	EditGUI editgui{ &ballkun,&objectmanager ,&goal };


	DataManager datamanager{ &objectmanager, &goal };


	Making(const InitData& init)
		: IScene(init)
	{
		Window::Resize(1200, 700);

		//stagedata�ɍ��킹�ăf�[�^�̓ǂݎ��
		//ObjectManager�̔z���Object����

		datamanager.setEditGUptr(&editgui);

		datamanager.stageread(getData().filepath, ballkun);


		//�e�X�g�p
		//objectmanager.add(std::make_shared<Block>(RectF(30, 30, 40, 100), 0, 0, 0, 0, &ballkun));
		//objectmanager.add(std::make_shared<Block>(RectF(130, 30, 40, 100), Math::Pi / 4, 0, 0, 0, &ballkun));
		//objectmanager.add(std::make_shared<Block>(RectF(30, 130, 40, 100), 0, Math::Pi / 4, 0, 0, &ballkun));
		//objectmanager.add(std::make_shared<Block>(RectF(30, 30, 40, 100), 0, 0, 10, 0, &ballkun));
		//objectmanager.add(std::make_shared<Block>(RectF(100, 100, 40, 100), 0, 0, 0, 5, &ballkun));
		//objectmanager.add(std::make_shared<Block>(RectF(150, 150, 40, 100), 0, 0, 5, 5, &ballkun));


		//ballkun�̈ʒu���f�[�^�ʂ�ɏC��

		//goal�̈ʒu���f�[�^�ʂ�ɏC��


	}


	void update()override
	{

		//�G�f�B�^�̓|�[�Y���ł��g�p�\
		editgui.update();
		if (editgui.saving) 
		{
			datamanager.stagesave(getData().stagenum);
		}

		//�߂�
		if (Key0.down())changeScene(SceneName::Select);

	
		//�|�[�Y(����)
		if (pause) {
			if (KeyP.down())pause = false;
			if (MouseR.down())changeScene(SceneName::Select);//�߂�
			return;
		}

		//�|�[�Y����
		if (!pause && KeyP.down())pause = true;


		//�{�[���̈ʒu�i��j�X�V
		ballkun.update();


		//�ҏW��ʂ���o���畜�A����
		if (!Rect(0, 0, 800, 600).intersects(ballkun.ballbody))ballkun.reset();

		//�S�[����I�u�W�F�N�g�ƐG�ꂽ����ƌ����ē��ɉ������Ȃ�
		
		goal.update();
		objectmanager.update();

		if (KeyZ.down())
		{
			changeScene(SceneName::Title);
		}





	}

	void draw()const override
	{

		Window::ClientRect().draw(Palette::Black);

		
		//�S�[���̓I�u�W�F�N�g�ɉB��A�{�[�����őO��
		editgui.drawstart();

		goal.draw();
		objectmanager.draw();
		ballkun.draw();


		/*�O���Q*/

		//�ҏW��ʂ̘g�g��
		Rect(800, 0, 400, 700).draw(Palette::Gray);
		Rect(0, 600, 1200, 100).draw(Palette::Gray);

		//�o�͕�
		if (pause) getData().font(U"�|�[�Y\n�߂�F�E�N���b�N").drawAt(0, 600, Palette::Black);

		//GUI(�őO��)
		editgui.draw();

	}


};