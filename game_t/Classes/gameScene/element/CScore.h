#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"


USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

class CScore : public cocos2d::Node
{
private:
	static bool first;
	Label *No[9];
	void upload(int);
	void update();
public:
	~CScore();
	CScore();
	int  score=0, level=1;
	
	void setScore(int);
	// implement the "static create()" method manually
	CREATE_FUNC(CScore);
};

