#pragma once
# include <Siv3D.hpp> // OpenSiv3D v0.3.1
#include<HamFramework.hpp>
#include "Ball_kun.h"
#include"Goal.h"
#include "IObject.h"
#include"DataManager.h"

enum class SceneName
{
	Title,
	Select,
	Game,
	Making,
	Result
};

//全てのシーンからアクセスできる

struct CommonData
{
	int ini_num;
	Font font{ 50 };
	
	int mode;
	int stagenum;
	String filepath;
	
};

using MyApp = SceneManager<SceneName, CommonData>;