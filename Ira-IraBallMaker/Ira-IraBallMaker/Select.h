#pragma once

/*SelectUIに頑張ってもらう*/


#include "manager.h"
#include "selectUI.h"


class Select : public MyApp::Scene
{
public:

	
	SelectUI selectUI=0;//空のSelectUIを生成

	Select(const InitData& init)
		: IScene(init)
	{
		Window::Resize(800, 600);

		//modeに合わせてダミーと入れ替える
		selectUI = SelectUI(getData().mode);


		//selectUIに遷移の関数を与える(かつ、選択したステージIDを受け取れるようにする)
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