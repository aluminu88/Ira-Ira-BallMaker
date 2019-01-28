#include "Ball_Kun.h"

Ball_kun::Ball_kun(const Vec2 _pos):
	pos(_pos)
{
	ballbody.setPos(pos);
	ballbody.r = 30;

	facepattern["Grabbed"] = U"・o・";
	facepattern["Default"] = U"・-・";
	//facepattern["Mouth"] = U"・ロ・";
	//facepattern["Dengeous"] = U"゜ロ゜";
	facepattern["WIN"] = U"・∀・";
	facepattern["LOSE"] = U"T  ^ T";
	
	defaultpos = pos;

	ballface = facepattern["Normal2"];

}

void Ball_kun::update()
{
	if (ballbody.leftClicked()) {

		grabbed = true;

	}
	else if (MouseL.up()) {

		grabbed = false;


	}
	else if (grabbed) {

		pos += Cursor::DeltaF();
		ballbody.setPos(pos);

	}

	face();

	

}

void Ball_kun::face()
{
	if (!(ballface == facepattern["WIN"] || ballface == facepattern["LOSE"])) {
		if (grabbed) ballface = facepattern["Default"];
		else ballface = facepattern["Grabbed"]; 
	}
	
}

void Ball_kun::facechange(std::string f)
{
	ballface = facepattern[f];
}

void Ball_kun::reset()
{
	pos = defaultpos;	
}

void Ball_kun::draw() const
{
	ballbody.draw(Palette::Yellow);
	facefont(ballface).drawAt(pos, Palette::Black);
}
