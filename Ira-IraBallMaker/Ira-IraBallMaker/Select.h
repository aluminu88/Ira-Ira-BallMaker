#pragma once

/*SelectUI�Ɋ撣���Ă��炤*/


#include "manager.h"
#include "selectUI.h"


class Select : public MyApp::Scene
{
public:

	
	SelectUI selectUI=0;//���SelectUI�𐶐�

	Select(const InitData& init)
		: IScene(init)
	{
		Window::Resize(800, 600);

		//mode�ɍ��킹�ă_�~�[�Ɠ���ւ���
		selectUI = SelectUI(getData().mode);


		//selectUI�ɑJ�ڂ̊֐���^����(���A�I�������X�e�[�WID���󂯎���悤�ɂ���)
		selectUI.changescene = [&](int ID, String stagename) { if (getData().mode == 0)changeScene(SceneName::Game); else changeScene(SceneName::Making); getData().stagenum = ID; getData().filepath = stagename; };
		
	}


	void update()override
	{
		selectUI.update();
		
	}

	void draw()const override
	{
		if(getData().mode == 0) Window::ClientRect().draw(Palette::Midnightblue);
		//else if(getData().mode = 1) Window::ClientRect().draw(Palette::Royalblue);
		else if (getData().mode == 1) Window::ClientRect().draw(Palette::Navy);
		

		selectUI.draw();

	}


};