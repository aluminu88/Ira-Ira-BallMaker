#pragma once
//タイトル画面に置きたい汎用型クラス






#include<Siv3D.hpp>

class TitleMenuTool {

public :

	RectF RangeRect;
	RectF TitleRange;
	RectF MenuRange;

	RectF ItemRange;

	//項目数
	int gyou=0;


	std::vector<String> items;
	RectF rects[100];

	String titlesentence = U"ここにタイトル" ;

	Font titlefont{ 50 }, menufont{30};

	Vec2 pos;

	int num = 0;


	TitleMenuTool(int _gyou)
	{
		gyou = _gyou;
		pos = Window::Center();
		RangeRect = RectF(4*Window::Width()/5,5*Window::Height()/6);//大きさ
		TitleRange = RectF(5 * RangeRect.w / 6, RangeRect.h / 3);//大きさ
		MenuRange = RectF(RangeRect.w / 2, RangeRect.h / 2);


		RangeRect.setCenter(pos);
		TitleRange.setCenter(RangeRect.center() - Vec2{ 0, RangeRect.center().y / 2 });
		
		MenuRange.setCenter(RangeRect.center() + Vec2{ 0, RangeRect.center().y / 3 });

		for(int i=0;i<gyou;i++)
		{
			rects[i] = (RectF(MenuRange.pos.x, MenuRange.pos.y + i * 40,MenuRange.w,40));
		}



	};

	TitleMenuTool(Vec2 _pos) :
		pos(_pos)
	{};


	void update() 
	{
		for (int i = 0; i < gyou; i++)
		{
			if (rects[i].intersects(Cursor::PosF())) 
			{
				if (MouseL.down())num =  i;
			}
		}
	}

	void draw() const
	{
		RangeRect.drawFrame();
		TitleRange.drawFrame();
		titlefont(titlesentence).drawAt(TitleRange.center());
		MenuRange.drawFrame();

		
		for (int i = 0; i < gyou; i++)
		{
			if (rects[i].intersects(Cursor::PosF()))
			{
				rects[i].draw(Palette::Yellow);
				menufont(items[i]).drawAt(rects[i].center(),Palette::Red);
			}
			else {
				rects[i].draw(Palette::Navy);
			    menufont(items[i]).drawAt(rects[i].center(),Palette::White);
			}
		}


	}




};