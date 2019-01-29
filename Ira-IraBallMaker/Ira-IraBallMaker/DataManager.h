#pragma once
//CSV��ǂݍ���ŁA�f�[�^�ʂ�ɃI�u�W�F�N�g��z�u������

//�Ǘ��pCSV��ǂݍ���ŁA�X�e�[�W���A�X�N���[���V���b�g�A������SelectUI�ɕ\��
//�X�e�[�W�f�[�^CSV��ǂݍ���ŁAObject��Ball�AGoal��z�u
//

#include<Siv3D.hpp>
#include"IObject.h"
#include "Goal.h"
#include "EditGUI.h"
#include "Ball_Kun.h"

class DataManager {

public:

	CSVData csvdata;

	ObjectManager* objectmanagerptr;
	Goal* goalptr;
	EditGUI* editguiptr;

	struct StagesDataList
	{
	public:

		int ID;
		String stagename;
		String screenpath;
		String clearstate;
		int time;

		StagesDataList(int _ID, String _stagename, String _screenpath,String _clearstate,int _time) :
			ID(_ID),
			stagename(_stagename),
			screenpath(_screenpath),
			clearstate(_clearstate),
			time(_time)
		{}

	};

	std::vector<StagesDataList> stagesdatalist;


	DataManager(ObjectManager* _optr,Goal* _gptr):
		objectmanagerptr(_optr),
		goalptr(_gptr)
	{

	}

	void setEditGUptr(EditGUI* _eptr) 
	{
		editguiptr = _eptr;
	}

	

	//GUI�̃X�e�[�W�ۑ����ɌĂ΂��
	void stagesave(int ID)
	{
		

		//�t�H���_�p�X�̏���(�ݒ肵���X�e�[�W����ǂݎ���ăt�@�C���p�X�����)

		String directoryname = U"StagesData/" + editguiptr->stagename.text;

		String screenshotpath = U"StagesData/" + editguiptr->stagename.text + U"/ScreenShot.png";

		//�X�N���[���V���b�g���Ƃ�StagesData/Stage01/ScreenShot.png
		ScreenCapture::SaveCurrentFrame(screenshotpath);



		stagesdatalist = {};

		//�Ǘ��p�t�@�C�� "StagesData/StageData.csv

		//����U��ꂽID�̍s�ɋL�q����񂾂Ǝv���������͂����Ȃ��̂őS����������

		//�O�̓��e���R�s�[

		//�V�����t�@�C�����ꎞ�I�ɊJ��
		csvdata.load(U"StagesData/StagesData.csv");
		for (size_t i = 1; i < csvdata.columns(1) ; i++) 
		{
			stagesdatalist.emplace_back(i, csvdata.get<String>(i, 0), csvdata.get<String>(i, 1), csvdata.get<String>(i, 2), csvdata.get<int>(i, 3));
		}

		//�ۑ�����StageDataList�̒��Ńf�[�^�̒u���������
		
		for (auto&& data : stagesdatalist) 
		{
			if(data.ID == ID)data = StagesDataList(ID, editguiptr->stagename.text, screenshotpath,U"No",9999);//�V�K�ۑ��̓N���A������V
		}

		//stagesdatalist[ID] = StagesDataList(ID, editguiptr->stagename.text, screenshotpath);
		
		//�u������������꒼��

		csvdata.load(U"StagesData/NewStagesData.csv");
		csvdata.write(U"�X�e�[�W��", U"�X�N���[���V���b�g�i�p�X�j", U"�N���A��", U"�N���A�^�C��");
		csvdata.newLine();
		
		for (auto&& data : stagesdatalist) 
		{
			csvdata.write(data.stagename, data.screenpath, data.clearstate, data.time);
		}
		

		csvdata.save(U"StagesData/NewStagesData.csv");

		//�V������蒼�����t�@�C����{�f�[�^�ɃR�s�[������
		FileSystem::Copy(U"StagesData/NewStagesData.csv", U"StagesData/StagesData.csv", CopyOption::Overwrite_if_Exists);

		//�ꎞ�t�@�C���͍폜����
		FileSystem::Remove(U"StagesData/NewStagesData.csv");

		//

		


		//Block�ۑ� "StagesData/Stage01/BlockData.csv"
		csvdata.load(directoryname + U"/NewBlockData.csv");
		csvdata.write(U"x���W", U"y���W", U"��", U"����", U"rad", U"radpUus", U"vx", U"vy");//8����)
		csvdata.newLine();

		//�v�f�̋L�^
		if (!objectmanagerptr->blocks.empty()) 
		{
			for (auto&& block : objectmanagerptr->blocks) 
			{
				csvdata.write(block->block.pos.x);
				csvdata.write(block->block.pos.y);
				csvdata.write(block->block.h);
				csvdata.write(block->block.w);
				csvdata.write(block->rad);
				csvdata.write(block->radplus);
				csvdata.write(block->vx);
				csvdata.write(block->vy);
				csvdata.newLine();
			}
		}
		else csvdata.write(U"None");

		csvdata.save(directoryname + U"/NewBlockData.csv");
		
		//�V������蒼�����t�@�C����{�f�[�^�ɃR�s�[������
		FileSystem::Copy(U"StagesData/NewBlockData.csv", U"StagesData/BlockData.csv", CopyOption::Overwrite_if_Exists);

		//�ꎞ�t�@�C���͍폜����
		FileSystem::Remove(U"StagesData/NewBlockData.csv");


		//Line
		//csvdata.load(U"LineData.csv");
		
		//Goal�ƃX�^�[�g�� "StagesData/Stage01/Utility.csv"

		csvdata.load(directoryname + U"/NewUtilityData.csv");
		csvdata.write(U"Start.x",U"Start.y",U"Goal.x",U"Goal,y");
		csvdata.newLine();
		
		//�v�f�̋L�^
		csvdata.write(goalptr->startpos.x, goalptr->startpos.y, goalptr->goalrect.pos.x, goalptr->goalrect.pos.y);
		csvdata.newLine();
		//

		csvdata.save(directoryname + U"/NewUtilityData.csv");

		//�V������蒼�����t�@�C����{�f�[�^�ɃR�s�[������
		FileSystem::Copy(U"StagesData/NewUtilityData.csv", U"StagesData/UtilityData.csv", CopyOption::Overwrite_if_Exists);

		//�ꎞ�t�@�C���͍폜����
		FileSystem::Remove(U"StagesData/NewUtilityData.csv");

		editguiptr->saving = false;
		//�N���[�Y�ł͂Ȃ��A.save()�����̖�ڂ����Ă���炵��
		
	}

	void stageread(String stagename,Ball_kun ballkun) 
	{
	
		//�S�[����X�^�[�g�n�_

		csvdata.load(U"StagesData/" + stagename + U"/UtilityData.csv");

		goalptr->startpos = Vec2(csvdata.get<double>(1, 0), csvdata.get<double>(1, 1));
		goalptr->goalrect.pos = Vec2(csvdata.get<double>(1,2),csvdata.get<double>(1,3));

		//Block

		csvdata.load(U"StagesData/" + stagename + U"/BlockData.csv");

		//Block�̏�����
		objectmanagerptr->blocks = {};

		//

		for (size_t i = 0; i < csvdata.columns(1); i++) 
		{
			objectmanagerptr->blockadd(std::make_shared<Block>(RectF(Vec2(csvdata.get<double>(i, 0), csvdata.get<double>(i, 1)), csvdata.get<int>(i, 2), csvdata.get<int>(i, 3)), csvdata.get<int>(i, 4), csvdata.get<int>(i, 5), csvdata.get<int>(i, 6), csvdata.get<int>(i, 7),&ballkun ));
		}




	}

	


};