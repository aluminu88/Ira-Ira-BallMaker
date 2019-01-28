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
		//�{�[���Ƃ̏Փ˔���(���S�ɕ�񂾎��ɃS�[���Ƃ���)
		if (goalrect.contains(ballptr->ballbody))
		{
			goaled = true;
			return goaled;
		}

		return false;
	}

	void draw()const
	{
		//�S�[��
		if (goalrect.contains(ballptr->ballbody)) 
		{
			goalrect.draw(Palette::Limegreen).drawFrame(2,1,Palette::Lime);
		}
		//�S�[�����ĂȂ�
		else 
		{
			goalrect.draw(Palette::Limegreen);
		}
	}
};