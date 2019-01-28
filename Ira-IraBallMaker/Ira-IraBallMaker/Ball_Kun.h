#pragma once
#include<Siv3D.hpp>
#include<string>
#include<map>

//マウスで操作する
//状況によって変化する表情
//
//

class Ball_kun {

public:

	Ball_kun(const Vec2 _pos);

	Vec2 pos,defaultpos;
	bool grabbed = false;

	Circle ballbody;
	Font facefont{ 20 };


	std::map<std::string, String> facepattern;
	String ballface;


	void update();
	void face();
	void facechange(std::string f);
	void reset();

	void draw()const;




};