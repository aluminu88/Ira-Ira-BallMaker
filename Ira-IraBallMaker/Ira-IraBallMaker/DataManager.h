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

		//�����t�@�C�����ꎞ�I�ɊJ���A�v�f���i�[����
		csvdata.load(U"StagesData/StagesData.csv");
		for (size_t i = 1; i < csvdata.rows() ; i++) 
		{
			stagesdatalist.emplace_back(i, csvdata.get<String>(i, 0), csvdata.get<String>(i, 1), csvdata.get<String>(i, 2), csvdata.get<int>(i, 3));
		}


		if (ID == (int)csvdata.rows()) {
			//�V�K�쐬���ɏ㏑���ł���悤�ɕێ�
			stagesdatalist.emplace_back(csvdata.rows(), U"�V�K�쐬", U"None", U"None", 9999);

		}

		//�ۑ�����StageDataList�̒��Ńf�[�^�̒u���������
		
		for (auto&& data : stagesdatalist) 
		{
			if(data.ID == ID)data = StagesDataList(ID, editguiptr->stagename.text, screenshotpath,U"No",9999);//�ҏW�ۑ��̓N���A������V

			
		}

		//stagesdatalist[ID] = StagesDataList(ID, editguiptr->stagename.text, screenshotpath);
		
		//�u������������꒼��

		csvdata.load(U"StagesData/NewStagesData.csv");
		csvdata.write(U"�X�e�[�W��", U"�X�N���[���V���b�g�i�p�X�j", U"�N���A��", U"�N���A�^�C��");
		csvdata.newLine();
		
		for (auto&& data : stagesdatalist) 
		{
			csvdata.write(data.stagename, data.screenpath, data.clearstate, data.time);
			csvdata.newLine();
		}
		

		csvdata.save(U"StagesData/NewStagesData.csv");

		//�V������蒼�����t�@�C����{�f�[�^�ɃR�s�[������
		FileSystem::Copy(U"StagesData/NewStagesData.csv", U"StagesData/StagesData.csv", CopyOption::Overwrite_if_Exists);

		//�ꎞ�t�@�C���͍폜����
		FileSystem::Remove(U"StagesData/NewStagesData.csv");

		csvdata.clear();

		//�N���A�f�[�^

		//csvdata.load(directoryname + U"/ClearData.csv");
		//csvdata.save(directoryname + U"/ClearData.csv");

		//csvdata.load(directoryname + U"/NewClearData.csv");
		//csvdata.write(U"�N���A��", U"�N���A�^�C��");
		//csvdata.newLine();
		//csvdata.write(U"No", U"9999");//�V�K�ۑ��̓N���A�f�[�^��������
		//csvdata.save(directoryname + U"NewClearData.csv");

		//�V������蒼�����t�@�C����{�f�[�^�ɃR�s�[������
		//FileSystem::Copy(directoryname + U"/NewClearData.csv", directoryname + U"/ClearData.csv", CopyOption::Overwrite_if_Exists);

		//�ꎞ�t�@�C���͍폜����
		//FileSystem::Remove(directoryname + U"/NewClearData.csv");
		
		//

		//Block�ۑ� "StagesData/Stage01/BlockData.csv"
		

		csvdata.load(directoryname + U"/BlockData.csv");
		csvdata.save(directoryname + U"/BlockData.csv");
		csvdata.clear();

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
				csvdata.write((int)block->block.w);
				csvdata.write((int)block->block.h);
				csvdata.write(block->rad);
				csvdata.write(block->radplus);
				csvdata.write((int)block->vx);
				csvdata.write((int)block->vy);
				csvdata.newLine();
			}
		}
		else csvdata.write(U"None");

		csvdata.save(directoryname + U"/NewBlockData.csv");
		
		//�V������蒼�����t�@�C����{�f�[�^�ɃR�s�[������
		FileSystem::Copy(directoryname + U"/NewBlockData.csv", directoryname + U"/BlockData.csv", CopyOption::Overwrite_if_Exists);

		//�ꎞ�t�@�C���͍폜����
		FileSystem::Remove(directoryname + U"/NewBlockData.csv");

		csvdata.clear();
		
		
		//Line
		//csvdata.load(U"LineData.csv");
		
		//Goal�ƃX�^�[�g�� "StagesData/Stage01/Utility.csv"
		//csvdata.load(directoryname + U"/UtilityData.csv");
		//csvdata.save(directoryname + U"/UtilityData.csv");
		//csvdata.clear();

		csvdata.load(directoryname + U"/NewUtilityData.csv");

		

		csvdata.write(U"Start.x",U"Start.y",U"Goal.x",U"Goal,y");
		csvdata.newLine();
		
		//�v�f�̋L�^
		csvdata.write(goalptr->startpos.x, goalptr->startpos.y, goalptr->goalrect.pos.x, goalptr->goalrect.pos.y);
		csvdata.newLine();
		//

		csvdata.save(directoryname + U"/UtilityData.csv");

		//�V������蒼�����t�@�C����{�f�[�^�ɃR�s�[������
		FileSystem::Copy(directoryname + U"/NewUtilityData.csv", directoryname + U"/UtilityData.csv", CopyOption::Overwrite_if_Exists);

		//�ꎞ�t�@�C���͍폜����
		FileSystem::Remove(directoryname+ U"/NewUtilityData.csv");
		
		csvdata.clear();

		editguiptr->saving = false;

		//�N���[�Y�ł͂Ȃ��A.save()�����̖�ڂ����Ă���炵��
		
	}

	void stageread(String stagename,Ball_kun& ballkun,int option) 
	{
		if (stagename == U"�V�K�쐬") return;
	
		//�S�[����X�^�[�g�n�_

		csvdata.load(U"StagesData/" + stagename + U"/UtilityData.csv");

		goalptr->startpos = Vec2(csvdata.get<double>(1, 0), csvdata.get<double>(1, 1));
		goalptr->goalrect.pos = Vec2(csvdata.get<double>(1,2),csvdata.get<double>(1,3));

		//Block

		csvdata.load(U"StagesData/" + stagename + U"/BlockData.csv");

		//Block�̏�����
		objectmanagerptr->blocks = {};
		
		//
		if (csvdata.get<String>(1, 1) != U"None") {

			for (size_t i = 1; i < csvdata.rows(); i++)
			{
				objectmanagerptr->blockadd(std::make_shared<Block>(RectF(Vec2(csvdata.get<double>(i, 0), csvdata.get<double>(i, 1)), csvdata.get<int>(i, 2), csvdata.get<int>(i, 3)), csvdata.get<double>(i, 4), csvdata.get<double>(i, 5), csvdata.get<int>(i, 6), csvdata.get<int>(i, 7), &ballkun, option));
			}

		}


	}

	bool cleardata(int ID,String filepath,int time) 
	{
		stagesdatalist = {};
		bool newrecord = false;

		//�Ǘ��p�t�@�C�� "StagesData/StageData.csv

		//����U��ꂽID�̍s�ɋL�q����񂾂Ǝv���������͂����Ȃ��̂őS����������

		//�O�̓��e���R�s�[

		//�����t�@�C�����ꎞ�I�ɊJ���A�v�f���i�[����
		csvdata.load(U"StagesData/StagesData.csv");
		for (size_t i = 1; i < csvdata.rows(); i++)
		{
			stagesdatalist.emplace_back(i, csvdata.get<String>(i, 0), csvdata.get<String>(i, 1), csvdata.get<String>(i, 2), csvdata.get<int>(i, 3));
		}



		//�ۑ�����StageDataList�̒��őΉ�����ID�Ƀf�[�^�̒u���������

		for (auto&& data : stagesdatalist)
		{
			if (data.ID == ID)
			{
				if (data.time > time) {
					data = StagesDataList(ID, filepath, U"StagesData/" + filepath + U"/ScreenShot.png", U"Yes", time);
					newrecord = true;
				}
			}
		}

		//stagesdatalist[ID] = StagesDataList(ID, editguiptr->stagename.text, screenshotpath);

		//�u������������꒼��

		csvdata.load(U"StagesData/NewStagesData.csv");
		csvdata.write(U"�X�e�[�W��", U"�X�N���[���V���b�g�i�p�X�j", U"�N���A��", U"�N���A�^�C��");
		csvdata.newLine();

		for (auto&& data : stagesdatalist)
		{
			csvdata.write(data.stagename, data.screenpath, data.clearstate, data.time);
			csvdata.newLine();
		}


		csvdata.save(U"StagesData/NewStagesData.csv");

		//�V������蒼�����t�@�C����{�f�[�^�ɃR�s�[������
		FileSystem::Copy(U"StagesData/NewStagesData.csv", U"StagesData/StagesData.csv", CopyOption::Overwrite_if_Exists);

		//�ꎞ�t�@�C���͍폜����
		FileSystem::Remove(U"StagesData/NewStagesData.csv");

		csvdata.clear();

		return newrecord;
		
	}


	//�t�@�C����ɂ����o�[�W����
	void stagesaveV2(int ID) 
	{
		//�t�H���_�p�X�̏���(�ݒ肵���X�e�[�W����ǂݎ���ăt�@�C���p�X�����)

		String directoryname = U"StagesData/" + editguiptr->stagename.text;

		String screenshotpath = U"StagesData/" + editguiptr->stagename.text + U"/ScreenShot.png";

		//�X�N���[���V���b�g���Ƃ�StagesData/Stage01/ScreenShot.png
		ScreenCapture::SaveCurrentFrame(screenshotpath);


		//�Ǘ��pCSV�̂Ȃ��悤���ʂ���̍\����
		stagesdatalist = {};

		//�Ǘ��p�t�@�C�� "StagesData/StageData.csv

		//����U��ꂽID�̍s�ɋL�q����񂾂Ǝv���������͂����Ȃ��̂őS����������

		//�O�̓��e���R�s�[

		//�����t�@�C�����ꎞ�I�ɊJ���A�v�f���i�[����
		csvdata.load(U"StagesData/StagesData.csv");
		for (size_t i = 1; i < csvdata.rows(); i++)
		{
			stagesdatalist.emplace_back(i, csvdata.get<String>(i, 0), csvdata.get<String>(i, 1), csvdata.get<String>(i, 2), csvdata.get<int>(i, 3));
		}


		if (ID == (int)csvdata.rows()) {
			//�V�K�쐬���ɏ㏑���ł���悤�ɕێ�
			stagesdatalist.emplace_back(csvdata.rows(), U"�V�K�쐬", U"None", U"None", 9999);

		}

		//�ۑ�����StageDataList�̒��Ńf�[�^�̒u���������

		for (auto&& data : stagesdatalist)
		{
			if (data.ID == ID)data = StagesDataList(ID, editguiptr->stagename.text, screenshotpath, U"No", 9999);//�ҏW�ۑ��̓N���A������V


		}

		//stagesdatalist[ID] = StagesDataList(ID, editguiptr->stagename.text, screenshotpath);

		//�u������������꒼��

		csvdata.load(U"StagesData/NewStagesData.csv");
		csvdata.write(U"�X�e�[�W��", U"�X�N���[���V���b�g�i�p�X�j", U"�N���A��", U"�N���A�^�C��");
		csvdata.newLine();

		for (auto&& data : stagesdatalist)
		{
			csvdata.write(data.stagename, data.screenpath, data.clearstate, data.time);
			csvdata.newLine();
		}


		csvdata.save(U"StagesData/NewStagesData.csv");

		//�V������蒼�����t�@�C����{�f�[�^�ɃR�s�[������
		FileSystem::Copy(U"StagesData/NewStagesData.csv", U"StagesData/StagesData.csv", CopyOption::Overwrite_if_Exists);

		//�ꎞ�t�@�C���͍폜����
		FileSystem::Remove(U"StagesData/NewStagesData.csv");

		csvdata.clear();

		//�S�[���A�u���b�N���̃f�[�^

		csvdata.load(directoryname + U"/ObjectsData.csv");
		csvdata.save(directoryname + U"/ObjectsData.csv");

		csvdata.load(directoryname + U"/NewObjectsData.csv");

		//�X�^�[�g�n�_�A�S�[���n�_�̍��W�i0�s�ځj
		csvdata.write(U"Start.x", U"Start.y", U"Goal.x", U"Goal,y");
		csvdata.newLine();
		//�L�^�i1�s�ځj
		csvdata.write(goalptr->startpos.x, goalptr->startpos.y, goalptr->goalrect.pos.x, goalptr->goalrect.pos.y);
		csvdata.newLine();

		
		if (!objectmanagerptr->blocks.empty())
		{
			//Block�̗v�f���i2�s�ځj
			csvdata.write(U"Block", objectmanagerptr->blocks.size(), U"��");
			csvdata.newLine();

			//Block�̗v�f���ځi3�s�ځj
			csvdata.write(U"x���W", U"y���W", U"��", U"����", U"rad", U"radpUus", U"vx", U"vy");//8����)
			csvdata.newLine();

			//�v�f�̋L�^�i3�s�ڈȍ~�j
			for (auto&& block : objectmanagerptr->blocks)
			{
				csvdata.write(block->block.pos.x);
				csvdata.write(block->block.pos.y);
				csvdata.write((int)block->block.w);
				csvdata.write((int)block->block.h);
				csvdata.write(block->rad);
				csvdata.write(block->radplus);
				csvdata.write((int)block->vx);
				csvdata.write((int)block->vy);
				csvdata.newLine();
			}
		}
		else 
		{
			//2�s��
			csvdata.write(U"Block", 0, U"��");
			csvdata.newLine();
			csvdata.write(U"x���W", U"y���W", U"��", U"����", U"rad", U"radpUus", U"vx", U"vy");//8����)
			csvdata.newLine();
		}



		//Line�̗v�f��(3+Block�v�f��or1)
		if (!objectmanagerptr->wires.empty()) 
		{
			//Wire�̗v�f���i�s�ځj
			csvdata.write(U"Wire", objectmanagerptr->wires.size(), U"��");
			csvdata.newLine();
			//Wire�̗v�f���ځi�s�ځj
			csvdata.write(U"�n�_.x", U"�n�_.y", U"�I�_.x", U"�I�_.y");//4����
			csvdata.newLine();

			for (auto&& wire : objectmanagerptr->wires) 
			{
				csvdata.write(wire->pos1.x);
				csvdata.write(wire->pos1.y);
				csvdata.write(wire->pos2.x);
				csvdata.write(wire->pos2.y);
				csvdata.newLine();
			}


		}
		else
		{
			csvdata.write(U"Wire", 0, U"��");
			csvdata.newLine();
			csvdata.write(U"�n�_.x", U"�n�_.y", U"�I�_.x", U"�I�_.y");//4����
			csvdata.newLine();
		}


		//�t�@�C���{�L�^

		csvdata.save(directoryname + U"/NewObjectsData.csv");

		//�V������蒼�����t�@�C����{�f�[�^�ɃR�s�[������
		FileSystem::Copy(directoryname + U"/NewObjectsData.csv", directoryname + U"/ObjectsData.csv", CopyOption::Overwrite_if_Exists);

		//�ꎞ�t�@�C���͍폜����
		FileSystem::Remove(directoryname + U"/NewObjectsData.csv");

		csvdata.clear();

		editguiptr->saving = false;

		
	}

	//�t�@�C����ɂ����o�[�W�����A
	void stagereadV2(String stagename, Ball_kun& ballkun, int option) 
	{
		if (stagename == U"�V�K�쐬") return;

		//�S�[����X�^�[�g�n�_

		csvdata.load(U"StagesData/" + stagename + U"/ObjectsData.csv");

		goalptr->startpos = Vec2(csvdata.get<double>(1, 0), csvdata.get<double>(1, 1));
		goalptr->goalrect.pos = Vec2(csvdata.get<double>(1, 2), csvdata.get<double>(1, 3));

		int count = 2;

		//Block

		//Block�̏�����
		objectmanagerptr->blocks = {};
		

		int blockcount = csvdata.get<int>(2, 1);

		//
		if (blockcount != 0) {

			for (int i = count+2; i < count+2+blockcount; i++)
			{
				objectmanagerptr->blockadd(std::make_shared<Block>(RectF(Vec2(csvdata.get<double>(i, 0), csvdata.get<double>(i, 1)), csvdata.get<int>(i, 2), csvdata.get<int>(i, 3)), csvdata.get<double>(i, 4), csvdata.get<double>(i, 5), csvdata.get<int>(i, 6), csvdata.get<int>(i, 7), &ballkun, option));
			}

		}

		count = count + 2 + blockcount;


		//Wire

		//Wire�̏�����
		objectmanagerptr->wires = {};
		int linecount = csvdata.get<int>(count, 1);
		//
		if (linecount != 0) 
		{
			for (int i = count + 2; i < count + 2 + linecount; i++) {
				objectmanagerptr->wireadd(std::make_shared<Wire>( Vec2(csvdata.get<double>(i, 0), csvdata.get<double>(i, 1)),  Vec2(csvdata.get<double>(i, 2), csvdata.get<double>(i, 3)) , &ballkun, option)  );
			}
		}

		count = count + 2 + linecount;


		//���̐}�`

	}
};