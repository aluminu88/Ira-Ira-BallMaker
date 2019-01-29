#pragma once
//CSV��ǂݍ���ŁA�f�[�^�ʂ�ɃI�u�W�F�N�g��z�u������

//�Ǘ��pCSV��ǂݍ���ŁA�X�e�[�W���A�X�N���[���V���b�g�A������SelectUI�ɕ\��
//�X�e�[�W�f�[�^CSV��ǂݍ���ŁAObject��Ball�AGoal��z�u
//

#include<Siv3D.hpp>
#include"IObject.h"
#include "Goal.h"
#include "EditGUI.h"

class DataManager {

public:

	CSVData csvdata;

	ObjectManager* objectmanagerptr;
	Goal* goalptr;
	EditGUI* editguiptr;


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
	void stagesave()
	{
		//�t�@�C�����֌W��������

		//�X�N���[���V���b�g���Ƃ�StagesData/Stage01/ScreenShot.png
		String screenshotpath = U"StagesData/" + editguiptr->stagename.text + U"/ScreenShot.png";

		ScreenCapture::SaveCurrentFrame(screenshotpath);



		//�Ǘ��p�t�@�C�� "StagesData/StageData.csv
		csvdata.load(U"StagesData/StagesData.csv");
		csvdata.write(U"�X�e�[�W���i�p�X�j",U"�X�N���[���V���b�g�i�p�X�j",U"�N���A��",U"�N���A�^�C��");
		csvdata.newLine();
		csvdata.write(editguiptr->stagename,screenshotpath);
		

		editguiptr->saving = false;

		//�V�f�[�^�p�ꎞ�t�@�C��


		//Block�ۑ� "StagesData/Stage01/BlockData.csv"
		csvdata.load(U"StagesData/Stage01/BlockData.csv");
		csvdata.write(U"x���W", L"y���W", L"��", L"����", L"rad", L"radplus", L"vx", L"vy");//8����)
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

		//Line
		//csvdata.load(U"LineData.csv");
		
		//Goal�ƃX�^�[�g�� "StagesData/Stage01/Utility.csv"

		csvdata.load(U"StagesData/Stage01/Utility.csv");
		csvdata.write(U"Start.x",U"Start.y",U"Goal.x",U"Goal,y");
		csvdata.newLine();
		
		//�v�f�̋L�^
		csvdata.write(goalptr->startpos.x, goalptr->startpos.y, goalptr->goalrect.pos.x, goalptr->goalrect.pos.y);
		csvdata.newLine();
		//


		//�N���[�Y���Ȃ��Ă����́H

		//�V�����t�@�C�����쐬���Ĉڂ�
		//
		//FileSystem::Copy(U"NewSavedata.csv", U"savedata_copy.csv", CopyOption::Overwrite_if_Exists);;
		
	}

	


};