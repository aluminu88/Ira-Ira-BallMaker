#pragma once



#include<Siv3D.hpp>
#include "Ball_Kun.h"

class Goal 
{

public :

	RectF goalrect = RectF(70, 70);
	Vec2 pos;
	Ball_kun* ballptr;

	Goal(Ball_kun* _ball,Vec2 _pos) :ballptr(_ball),pos(_pos)
	{
		goalrect.setPos(pos);
	};

	bool goaled = false;

	bool update()
	{
		//ボールとの衝突判定(完全に包んだ時にゴールとする)
		if (goalrect.contains(ballptr->ballbody))
		{
			goaled = true;
			return goaled;
		}

		return false;
	}

	void draw()const
	{
		//ゴール
		if (goalrect.contains(ballptr->ballbody)) 
		{
			goalrect.draw(Palette::Limegreen).drawFrame(2,1,Palette::Lime);
		}
		//ゴールしてない
		else 
		{
			goalrect.draw(Palette::Limegreen);
		}
	}
};