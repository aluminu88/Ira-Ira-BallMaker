/*�I����ʗp��UI�@�\*/

/*
�Ǘ��pCSV����A�X�e�[�W���A�T���l�C���摜��ǂݎ��
�e���ڂ�ID��U��
�p�ӂ���Rect�ɕK�v�ȏ���\�����i�\��t���j��B

Rect(�m�[�h)�͌Œ�A�f�[�^��J�ڂ����č��ڂ𑀍삵�Ă���悤�Ɍ�����
�I�����ꂽ���ڂ�ID�����L�f�[�^�Ɋi�[�AGame/Making�ւȂ�

*/

#pragma once
#include <Siv3D.hpp>
#include <vector>
#include <algorithm>



class SelectUI {

private:


	//�����\���p
	Font font20{ 20 };
	Font font40{ 40 };

	//�X�e�[�W���̂�\������m�[�h
	Rect r1{ 25,15,300,80 }, r2{ 50,120,300,80 }, r3{ 50,400,300,80 }, r4{ 25,505,300,80 };
	Rect R{ 30,225,400,150 };

	Rect nodes[5] = { r1,r2,R,r3,r4 };


	//�X�e�[�W�T���l�C���摜
	Rect preview_node{ 450,30,320,240 };
	Rect preview2_node{ 450,30,250,250 };

	//OK�{�^��
	Rect OK_node{ 400,500,340,90 };

	//��Փx����\������
	Rect detail_node{ 470, 310, 300, 50 };


	//���j���[�𓮂������߂̃{�^��
	Triangle up_button{ 200,5,230,45,170,45 }, down_button{ 200,595,170,555,230,555 };


	//�\��t��������󂯎��ꏊ



	//�e���ڂ��i�[����\����
	struct SelectNodeData 
	{
	public :

		int ID;
		String stagename;
		Texture thumbnail;
		String clearstate;
		int cleartime;

		SelectNodeData(int _ID, String _stagename, Texture _thumbnail,String _clearstate,int _cleartime):
			ID(_ID),
			stagename(_stagename),
			thumbnail(_thumbnail),
			clearstate(_clearstate),
			cleartime(_cleartime)
		{}	

		SelectNodeData(int _ID, String _stagename, Texture _thumbnail) :
			ID(_ID),
			stagename(_stagename),
			thumbnail(_thumbnail)
		{}

	};



	Texture DummyTexture{ U"screenshot/Dummy.png" };

	//�e���ڂ��i�[���Ă���z��
	std::vector<SelectNodeData> stagenodedata;

	CSVData readcsv;
	

	//���̃Z�b�g�̂��߂̊֐�

	enum class selectmode {
		Maiking,
		Game,
		Sending
	};
	
	selectmode mode;

	void set_selectUI()
	{
		//�Ǘ��pCSV���Ă�Ńt�@�C��������(for)�񂵁A�摜�A���O�����o����ID��U��(Making�Ȃ�Ō�ɐV�K�쐬���ڂ�t����)

		readcsv.load(U"StagesData/StagesData.csv");


		for (int i = 1; i < (int)readcsv.rows(); i++) //0�s�ڈȊO�̗v�f��������
		{
			//���ڈ����ID��U��Ȃ���A�X�N���[���V���b�g���e�N�X�`���ϊ����m�[�h�̃f�[�^�Ƃ��Ċi�[����
			stagenodedata.emplace_back(i, readcsv.get<String>(i, 0), Texture{ readcsv.get<String>(i,1) },readcsv.get<String>(i,2),readcsv.get<int>(i,3));

		}

		if (mode == selectmode::Maiking)stagenodedata.emplace_back(5, U"�V�K�쐬", DummyTexture,U"No", 9999);



		//�e�X�g�p
		/*stagenodedata.emplace_back(1, U"�e�X�g1", DummyTexture);
		stagenodedata.emplace_back(2, U"�e�X�g2", DummyTexture);
		stagenodedata.emplace_back(3, U"�e�X�g3", DummyTexture);
		stagenodedata.emplace_back(4, U"�e�X�g4", DummyTexture);
		stagenodedata.emplace_back(5, U"�e�X�g5", DummyTexture);
		stagenodedata.emplace_back(6, U"�e�X�g6", DummyTexture);
		stagenodedata.emplace_back(7, U"�e�X�g7", DummyTexture);
		stagenodedata.emplace_back(8, U"�e�X�g8", DummyTexture);
		stagenodedata.emplace_back(9, U"�e�X�g9", DummyTexture);
		stagenodedata.emplace_back(10, U"�e�X�g10", DummyTexture);*/





	}



public:

	//�V�[���J�ڗp�̊֐������炢�󂯂�
	std::function<void(int,String)> changescene;




	//�R���X�g���N�^
	SelectUI(int _mode)
	{
		if (_mode == 0)mode = selectmode::Game;
		else if (_mode == 1)mode = selectmode::Maiking;
		else if (_mode == 2)mode = selectmode::Sending;
		//�������ɏ�����
		set_selectUI();
	}

	void draw()const
	{

		//�X�e�[�W�m�[�h�̕\��
		for (Rect node : nodes) {

			node.draw();
		}

		//�e�L�X�g�̓\��t��
		auto iter = stagenodedata.begin();
		font40(iter->stagename).drawAt(nodes[2].center(), Palette::Black);
		font20((iter + 1)->stagename).drawAt(nodes[3].center(), Palette::Black);
		font20((iter + 2)->stagename).drawAt(nodes[4].center(), Palette::Black);
		iter = stagenodedata.end();
		font20((iter - 2)->stagename).drawAt(nodes[0].center(), Palette::Black);
		font20((iter - 1)->stagename).drawAt(nodes[1].center(), Palette::Black);

		//�T���l�C���m�[�h�̕\���E�\��t��

		preview_node(stagenodedata.begin()->thumbnail(0, 0, 800, 600)).draw().drawFrame(1, Palette::Aqua);

		//
		String detailtext;

		//�ڍ׃m�[�h�̕\��
		if (stagenodedata.begin()->clearstate == U"Yes") detailtext = U"Cleard!!";
		else detailtext = U"NO Clear";
		

		detail_node.draw();

		if(stagenodedata.begin()->cleartime != 9999)font20(detailtext, U"�@�@�@Time:", stagenodedata.begin()->cleartime, U"�b").drawAt(detail_node.center(),Palette::Black);
		else font20(detailtext, U"�@�@�@Time:", U"---�b").drawAt(detail_node.center(), Palette::Black);


		//OK�m�[�h�̕\��

		if (OK_node.mouseOver()) {

			if (OK_node.leftClicked()) {
				OK_node.draw(Palette::Mistyrose);
			}
			else {
				OK_node.draw(Palette::Red).drawFrame(0, 3, Palette::Mistyrose);
				font40(U"OK").drawAt(OK_node.center());
			}

		}
		else { OK_node.draw(Palette::Red); font40(U"OK").drawAt(OK_node.center()); }


		//


		//�{�^���m�[�h�̕\��


		if (up_button.mouseOver()) {

			if (up_button.leftClicked()) {
				up_button.draw(Palette::Lightgreen);
			}
			else { up_button.draw(Palette::Green).drawFrame(0, 3, Palette::Lightgreen); }

		}
		else { up_button.draw(Palette::Green); }


		if (down_button.mouseOver()) {

			if (down_button.leftClicked()) {
				down_button.draw(Palette::Lightgreen);
			}
			else { down_button.draw(Palette::Green).drawFrame(0, 3, Palette::Lightgreen); }

		}
		else { down_button.draw(Palette::Green); }

		//


	}


	void update()
	{

		//�{�^���ɑ΂��鏈��

		if (KeyUp.down() || up_button.leftClicked()) {

			auto iter = stagenodedata.end() - 1;			
			for (size_t i = 1; i < stagenodedata.size(); i++) {
				std::swap(*iter, *(iter - 1));
				iter--;
			}


		}


		if (KeyDown.down() || down_button.leftClicked()) {

			auto iter = stagenodedata.begin();
			for (size_t i = 1; i < stagenodedata.size(); i++) {
				std::swap(*iter, *(iter + 1));
				iter++;

			}
		}


		//


		if (OK_node.leftClicked()) {

			//�󂯎�����J�ڊ֐��ɑI�����ꂽID���悹��
			changescene(stagenodedata.begin()->ID, stagenodedata.begin()->stagename);//stagenodedata.begin()->stagename

		}




	}





};